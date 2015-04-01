#include "MarchingCubesScene.h"

extern void sendFeedback(AnsiString );

static const unsigned char pixelChange    = 1;
static const float         rotationChange = 0.4;
static int                 oldPixelsX;
static int                 oldPixelsY;

static GLint               pressedMouseButton;


static void setMarchingCubesScene(unsigned char*);
static void handleReshape(int, int);
static void handleReshapeForNewImageSet(void);
static void handleDisplay();
static void handleMouse(GLint, GLint, int, int);
static void handleMouseMotion(int, int);


MarchingCubesScene::MarchingCubesScene()
{
  totalObjects          = 0;
  totalClippingVolumes  = 0;
  totalTexturedSurfaces = 0;

  imageSet = NULL;

  voxelWidth  = 0;
  voxelHeight = 0;
  voxelDepth  = 0;

  imageSetWidth  = 0;
  imageSetHeight = 0;
  imageSetDepth  = 0;

  imageSetWidthWorldSpace  = 0;
  imageSetHeightWorldSpace = 0;
  imageSetDepthWorldSpace  = 0;

  lightSource = new LightSource(0, 0, 1, 150);

  for (int i = 0; i<MAX_OBJECT_NUMBER; i++)
    objectsList[i] = NULL;
  selectedObject          = NULL;

  for (int i = 0; i<MAX_CLIPPING_VOLUME_NUMBER; i++)
    clippingVolumesList[i] = NULL;
  selectedClippingVolume  = NULL;

  for (int i = 0; i<MAX_TEXTURED_SURFACE_NUMBER; i++)
    texturedSurfacesList[i] = NULL;
  selectedTexturedSurface = NULL;

  setMarchingCubesScene((unsigned char*) this);

  objectQualityState = OBJECT_QUALITY_HIGH;
  sceneState         = STATE_NORMAL;

  sceneEdgeLength  = 1.0;

  rotationX = 0;
  rotationY = 0;
  rotationZ = 0;
}


void MarchingCubesScene::setImageSet(CAnalyze* analyzeImage)
{
  for (int i = 0; i<totalObjects; i++)
    delete objectsList[i];
  totalObjects = 0;

  for (int i = 0; i<totalClippingVolumes; i++)
    delete clippingVolumesList[i];
  totalClippingVolumes = 0;

  for (int i = 0; i<MAX_TEXTURED_SURFACE_NUMBER; i++)
    delete texturedSurfacesList[i];
  totalTexturedSurfaces = 0;

  imageSet  = analyzeImage;

  voxelWidth  = imageSet->getWorldSpace().x;
  voxelHeight = imageSet->getWorldSpace().y;
  voxelDepth  = imageSet->getWorldSpace().z;

  imageSetWidth  = imageSet->getWidth();
  imageSetHeight = imageSet->getHeight();
  imageSetDepth  = imageSet->getSliceCount();

  imageSetWidthWorldSpace  = voxelWidth  * imageSetWidth;
  imageSetHeightWorldSpace = voxelHeight * imageSetHeight;
  imageSetDepthWorldSpace  = voxelDepth  * imageSetDepth;

  sceneEdgeLength  = sqrt(   imageSetWidthWorldSpace  * imageSetWidthWorldSpace
                           + imageSetHeightWorldSpace * imageSetHeightWorldSpace
                           + imageSetDepthWorldSpace  * imageSetDepthWorldSpace
                         );

  selectedObject          = NULL;
  selectedClippingVolume  = NULL;
  selectedTexturedSurface = NULL;
}


void MarchingCubesScene::initializeMarchingCubesScene()
{
  char **argv = new char*[1];
  argv[0] = "Visualize -- Reconstructed objects";
  int argc = 1;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(400,0);
  glutCreateWindow(argv[0]);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  glFrontFace(GL_CCW);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  rotationX = 0.0f;
  rotationY = 0.0f;
  rotationZ = 0.0f;

  oldPixelsX = 0;
  oldPixelsY = 0;

  glutDisplayFunc(handleDisplay);
  glutReshapeFunc(handleReshape);
  glutMouseFunc(handleMouse);
  glutMotionFunc(handleMouseMotion);

  glutPostRedisplay();

  glutMainLoop();
}

MarchingCubesScene::~MarchingCubesScene()
{
  int i;

  delete lightSource;

  for (i = 0; i < totalObjects; i++)
    delete objectsList[i];

  for (i = 0; i < totalClippingVolumes; i++)
    delete clippingVolumesList[i];

  for (i = 0; i < totalTexturedSurfaces; i++)
    delete texturedSurfacesList[i];

}




void MarchingCubesScene::generateLists()
{
    static float triVoxelWidth, triVoxelDepth, triVoxelHeight, v1, v2, v3;

    sendFeedback("Generating lists for objects...");

    triVoxelWidth  = 3 * voxelWidth;
    triVoxelHeight = 3 * voxelHeight;
    triVoxelDepth  = 3 * voxelDepth;

    for (unsigned short objectQualityStateIndex = OBJECT_QUALITY_HIGH; objectQualityStateIndex <=  OBJECT_QUALITY_LOW; objectQualityStateIndex++)
      for (unsigned short objectIndex = 0; objectIndex < totalObjects; objectIndex++)
        if (objectsList[objectIndex]->getListID(objectQualityStateIndex)>0)
          glDeleteLists(objectsList[objectIndex]->getListID(objectQualityStateIndex),1);

    if (totalClippingVolumes == 0)
    {
      for (unsigned short objectQualityStateIndex = OBJECT_QUALITY_HIGH; objectQualityStateIndex <=  OBJECT_QUALITY_LOW; objectQualityStateIndex++)
        for (unsigned short objectIndex = 0; objectIndex < totalObjects; objectIndex++)
        {
          objectsList[objectIndex]->setListID(objectQualityStateIndex, glGenLists(1));
          glNewList(objectsList[objectIndex]->getListID(objectQualityStateIndex), GL_COMPILE);

          for (unsigned long index = 0;
               index < 3*objectsList[objectIndex]->totalTriangles[objectQualityStateIndex];
               index++
              )
              {
                glNormal3fv(objectsList[objectIndex]->normals[objectQualityStateIndex][index].float_type());
                glVertex3fv(objectsList[objectIndex]->vertices[objectQualityStateIndex][index].float_type());
              }
          glEndList();
        } // of for (unsigned short objectIndex = 0;
    }
    else // of if (totalClippingVolumes == 0)
    {
      for (unsigned short objectQualityStateIndex = OBJECT_QUALITY_HIGH; objectQualityStateIndex <=  OBJECT_QUALITY_LOW; objectQualityStateIndex++)
        for (unsigned short objectIndex = 0; objectIndex < totalObjects; objectIndex++)
        {
          objectsList[objectIndex]->setListID(objectQualityStateIndex, glGenLists(1));
          glNewList(objectsList[objectIndex]->getListID(objectQualityStateIndex), GL_COMPILE);

            bool objectClipped = false;
            for (int clippingVolumeIndex = 0; clippingVolumeIndex<totalClippingVolumes; clippingVolumeIndex++)
              objectClipped  |=  clippingVolumesList[clippingVolumeIndex]->getClippedStateAtIndex(objectIndex);

            if (objectClipped == false)
              for (unsigned long index = 0;
                   index < 3*objectsList[objectIndex]->totalTriangles[objectQualityStateIndex];
                   index++
                  )
                {
                  glNormal3fv(objectsList[objectIndex]->normals[objectQualityStateIndex][index].float_type());
                  glVertex3fv(objectsList[objectIndex]->vertices[objectQualityStateIndex][index].float_type());
                }
            else // of if (objectClipped == false
              for (unsigned long index = 0;
                   index < 3*objectsList[objectIndex]->totalTriangles[objectQualityStateIndex];
                   index += 3
                  )
             {

//                    Use gravity of center for triangles....

                v1 = ( objectsList[objectIndex]->vertices[objectQualityStateIndex][index].x
                          + objectsList[objectIndex]->vertices[objectQualityStateIndex][index+1].x
                          + objectsList[objectIndex]->vertices[objectQualityStateIndex][index+2].x
                         ) / (triVoxelWidth);

                v2 = ( objectsList[objectIndex]->vertices[objectQualityStateIndex][index].y
                          + objectsList[objectIndex]->vertices[objectQualityStateIndex][index+1].y
                          + objectsList[objectIndex]->vertices[objectQualityStateIndex][index+2].y
                         ) / (triVoxelHeight);

                v3 = ( objectsList[objectIndex]->vertices[objectQualityStateIndex][index].z
                          + objectsList[objectIndex]->vertices[objectQualityStateIndex][index+1].z
                          + objectsList[objectIndex]->vertices[objectQualityStateIndex][index+2].z
                         ) / (triVoxelDepth);


                bool voxelClipped = false;

                for (int clippingVolumeIndex = 0; clippingVolumeIndex<totalClippingVolumes; clippingVolumeIndex++)
                  voxelClipped  |=  (clippingVolumesList[clippingVolumeIndex]->isPointInsideVoxelIJKForObject( v1, v2, v3, objectIndex));

                if (voxelClipped == false)
                {
                  glNormal3fv(objectsList[objectIndex]->normals[objectQualityStateIndex][index].float_type());
                  glVertex3fv(objectsList[objectIndex]->vertices[objectQualityStateIndex][index].float_type());

                  glNormal3fv(objectsList[objectIndex]->normals[objectQualityStateIndex][index+1].float_type());
                  glVertex3fv(objectsList[objectIndex]->vertices[objectQualityStateIndex][index+1].float_type());

                  glNormal3fv(objectsList[objectIndex]->normals[objectQualityStateIndex][index+2].float_type());
                  glVertex3fv(objectsList[objectIndex]->vertices[objectQualityStateIndex][index+2].float_type());
                } // of if (voxelClipped == false)
              } // of for (unsigned long index = 0;
          glEndList();
        } // of for (unsigned short objectIndex = 0;
    }


    sendFeedback("Done...!");
}





void MarchingCubesScene::interpolate(
                  unsigned char thresholdIntensity, unsigned short stepSize,
                  short int indexK, short int indexJ, short int indexI,
                  short int nextK, short int nextJ, short int nextI,
                  Point3Df* vertexPointer, Point3Df* normalPointer
                )
{
  static  float interpolatedValueForK, interpolatedValueForJ, interpolatedValueForI,
                normalAtK, normalAtJ, normalAtI,
                normalAtNextK, normalAtNextJ, normalAtNextI,
                normalForK, normalForJ, normalForI,
                ratio,
                deltaX, deltaY, deltaZ,
                vectorLength;

  ratio     = 1.0
              *
              (   thresholdIntensity
                -
                  imageSet->getSlice( indexK )->getVoxelGray( indexI, indexJ )
              )
              /
              (
                   imageSet->getSlice( nextK )->getVoxelGray( nextI, nextJ )
                -
                   imageSet->getSlice( indexK )->getVoxelGray( indexI, indexJ )
              );


  interpolatedValueForK = (indexK + (nextK-indexK) * ratio) * voxelDepth;
  interpolatedValueForJ = (indexJ + (nextJ-indexJ) * ratio) * voxelHeight;
  interpolatedValueForI = (indexI + (nextI-indexI) * ratio) * voxelWidth;

  vertexPointer->x = interpolatedValueForI;
  vertexPointer->y = interpolatedValueForJ;
  vertexPointer->z = interpolatedValueForK;


  deltaZ = 2.0 * stepSize * voxelDepth;
  deltaY = 2.0 * stepSize * voxelHeight;
  deltaX = 2.0 * stepSize * voxelWidth;


  normalAtK =  (
                  1.0 * imageSet->getSlice( indexK + stepSize ) -> getVoxelGray( indexI, indexJ )
                -
                  1.0 * imageSet->getSlice( indexK - stepSize ) -> getVoxelGray( indexI, indexJ )
               )
               /
               deltaZ;

  normalAtJ =  (
                  1.0 * imageSet->getSlice( indexK ) -> getVoxelGray( indexI, indexJ + stepSize )
                -
                  1.0 * imageSet->getSlice( indexK ) -> getVoxelGray( indexI, indexJ - stepSize )
               )
               /
               deltaY;

  normalAtI =  (
                  1.0 * imageSet->getSlice( indexK ) -> getVoxelGray( indexI + stepSize, indexJ )
                -
                  1.0 * imageSet->getSlice( indexK ) -> getVoxelGray( indexI - stepSize, indexJ )
               )
               /
               deltaX;


  normalAtNextK =  (
                      1.0 * imageSet->getSlice( nextK + stepSize ) -> getVoxelGray( nextI, nextJ )
                    -
                      1.0 * imageSet->getSlice( nextK - stepSize ) -> getVoxelGray( nextI, nextJ )
                   )
                   /
                   deltaZ;

  normalAtNextJ =  (
                      1.0 * imageSet->getSlice( nextK ) -> getVoxelGray( nextI, nextJ + stepSize )
                    -
                      1.0 * imageSet->getSlice( nextK ) -> getVoxelGray( nextI, nextJ - stepSize )
                   )
                   /
                   deltaY;

  normalAtNextI =  (
                      1.0 * imageSet->getSlice( nextK ) -> getVoxelGray( nextI + stepSize, nextJ )
                    -
                      1.0 * imageSet->getSlice( nextK ) -> getVoxelGray( nextI - stepSize, nextJ )
                   )
                   /
                   deltaX;


  normalForK = normalAtK + (normalAtNextK-normalAtK) * ratio;
  normalForJ = normalAtJ + (normalAtNextJ-normalAtJ) * ratio;
  normalForI = normalAtI + (normalAtNextI-normalAtI) * ratio;


  vectorLength = -1.0*sqrt((normalForK * normalForK) + (normalForJ * normalForJ) + (normalForI * normalForI));

  if (vectorLength == 0)
  {
    normalPointer->x = 0;
    normalPointer->y = 0;
    normalPointer->z = 0;
  }
  else
  {
    normalPointer->x = normalForI/vectorLength;
    normalPointer->y = normalForJ/vectorLength;
    normalPointer->z = normalForK/vectorLength;
  }
}




void MarchingCubesScene::calculateTotalTriangles()
{
    static unsigned int   i, j, k;
    static unsigned short stepSize,
                          objectQualityStateIndex, objectIndex;

    if ( imageSet == NULL)
      return;

    sendFeedback("Calculating total triangle counts for objects...");


    for (objectQualityStateIndex = OBJECT_QUALITY_HIGH; objectQualityStateIndex <=  OBJECT_QUALITY_LOW; objectQualityStateIndex++)
       for (objectIndex = 0; objectIndex < totalObjects; objectIndex++)
          objectsList[objectIndex]->totalTriangles[objectQualityStateIndex]  = 0;


    for (objectQualityStateIndex = OBJECT_QUALITY_HIGH; objectQualityStateIndex <=  OBJECT_QUALITY_LOW; objectQualityStateIndex++)
    {
        stepSize = (objectQualityStateIndex  ==  OBJECT_QUALITY_HIGH) ? 1 : 2 ;

        for (k = stepSize; k < imageSetDepth - 2*stepSize; k += stepSize)
        {
            for (j = stepSize; j < imageSetHeight - 2*stepSize; j += stepSize)
            {
                for (i = stepSize; i < imageSetWidth - 2*stepSize; i += stepSize)
                {
                    for (objectIndex = 0; objectIndex < totalObjects; objectIndex++)
                    {
                        if (objectsList[objectIndex]->triangleIndexes[objectQualityStateIndex] > MAXIMUM_TRIANGLE_COUNT_PER_OBJECT)
                            break;

                        objectsList[objectIndex]->cubeIndex = 0;

                        if (imageSet->getSlice(k)->getVoxelGray( i, j )                       > objectsList[objectIndex]->getThresholdIntensity() )
                           objectsList[objectIndex]->cubeIndex  |=  1;
                        if (imageSet->getSlice(k)->getVoxelGray( i + stepSize, j )            > objectsList[objectIndex]->getThresholdIntensity() )
                           objectsList[objectIndex]->cubeIndex  |=  2;
                        if (imageSet->getSlice(k)->getVoxelGray( i + stepSize, j + stepSize ) > objectsList[objectIndex]->getThresholdIntensity() )
                           objectsList[objectIndex]->cubeIndex  |=  4;
                        if (imageSet->getSlice(k)->getVoxelGray( i, j + stepSize )            > objectsList[objectIndex]->getThresholdIntensity() )
                           objectsList[objectIndex]->cubeIndex  |=  8;

                        if (imageSet->getSlice( k + stepSize )->getVoxelGray( i, j )                       > objectsList[objectIndex]->getThresholdIntensity() )
                           objectsList[objectIndex]->cubeIndex  |=  16;
                        if (imageSet->getSlice( k + stepSize )->getVoxelGray( i + stepSize, j )            > objectsList[objectIndex]->getThresholdIntensity() )
                           objectsList[objectIndex]->cubeIndex  |=  32;
                        if (imageSet->getSlice( k + stepSize )->getVoxelGray( i + stepSize, j + stepSize ) > objectsList[objectIndex]->getThresholdIntensity() )
                           objectsList[objectIndex]->cubeIndex  |=  64;
                        if (imageSet->getSlice( k + stepSize )->getVoxelGray( i, j + stepSize )            > objectsList[objectIndex]->getThresholdIntensity() )
                           objectsList[objectIndex]->cubeIndex  |=  128;


                        objectsList[objectIndex]->edgeIndex = edgeTable[objectsList[objectIndex]->cubeIndex];

                        // if no edge intersection
                        if ( objectsList[objectIndex]->edgeIndex == 0 )
                             // skip to the next cube
                            continue;
                            // else
                        objectsList[objectIndex]->totalTriangles[objectQualityStateIndex] += triangleNumberInTheCube[objectsList[objectIndex]->cubeIndex];

                    } // of for (objectIndex =
                }  // of for (i =
            }  // of for (j =
        }  // of for (k =
    } // of for (objectuQalityIndex =

    for (objectQualityStateIndex = OBJECT_QUALITY_HIGH; objectQualityStateIndex <=  OBJECT_QUALITY_LOW; objectQualityStateIndex++)
      for (objectIndex = 0; objectIndex < totalObjects; objectIndex++)
      {
        sendFeedback(  objectsList[objectIndex]->getName()
                     + " "
                     + AnsiString( (objectQualityStateIndex  ==  OBJECT_QUALITY_HIGH) ? "high" : "low")
                     + " quality  has "
                     + AnsiString(objectsList[objectIndex]->totalTriangles[objectQualityStateIndex])+ " triangles.");
      }

} // of calculateTotalTriangles





void MarchingCubesScene::marchTheCubes()
{
    unsigned int   i, j, k;
    unsigned short stepSize,
                   objectQualityStateIndex, objectIndex, clippingVolumeIndex,
                   p, q;
    GLfloat        normal[3], vertex[3];

    if (imageSet == NULL)
      return;



    calculateTotalTriangles();



    sendFeedback("Now marching cubes...");

    for (objectQualityStateIndex = OBJECT_QUALITY_HIGH; objectQualityStateIndex <=  OBJECT_QUALITY_LOW; objectQualityStateIndex++)
    {
      for (objectIndex = 0; objectIndex < totalObjects; objectIndex++)
      {
        objectsList[objectIndex]->triangleIndexes[objectQualityStateIndex]=0;

        if(objectsList[objectIndex]->normals[objectQualityStateIndex])
          delete objectsList[objectIndex]->normals[objectQualityStateIndex];

        if (objectsList[objectIndex]->totalTriangles[objectQualityStateIndex]>0)
          objectsList[objectIndex]->normals[objectQualityStateIndex] = new Point3Df[3*objectsList[objectIndex]->totalTriangles[objectQualityStateIndex]];
        else
          objectsList[objectIndex]->normals[objectQualityStateIndex] = NULL;


        if(objectsList[objectIndex]->vertices[objectQualityStateIndex])
          delete objectsList[objectIndex]->vertices[objectQualityStateIndex];
        if (objectsList[objectIndex]->totalTriangles[objectQualityStateIndex]>0)
          objectsList[objectIndex]->vertices[objectQualityStateIndex] = new Point3Df[3*objectsList[objectIndex]->totalTriangles[objectQualityStateIndex]];
        else
          objectsList[objectIndex]->vertices[objectQualityStateIndex] = NULL;
      }
    }


    for (objectQualityStateIndex = OBJECT_QUALITY_HIGH; objectQualityStateIndex <= OBJECT_QUALITY_LOW; objectQualityStateIndex++)
    {
        stepSize = (objectQualityStateIndex  ==  OBJECT_QUALITY_HIGH) ? 1 : 2 ;

        sendFeedback(AnsiString(objectQualityStateIndex  ==  OBJECT_QUALITY_HIGH ? "High quality " : "Low quality ") + "objects are being generated...");

        for (k = stepSize; k < imageSetDepth - 2*stepSize; k += stepSize)
        {
            for (j = stepSize; j < imageSetHeight - 2*stepSize; j += stepSize)
            {
                for (i = stepSize; i < imageSetWidth - 2*stepSize; i += stepSize)
                {
                    for (objectIndex = 0; objectIndex < totalObjects; objectIndex++)
                    {
                        if (objectsList[objectIndex]->triangleIndexes[objectQualityStateIndex] > MAXIMUM_TRIANGLE_COUNT_PER_OBJECT)
                            break;

                        objectsList[objectIndex]->cubeIndex = 0;

                        if (imageSet->getSlice( k )->getVoxelGray( i , j )                       > objectsList[objectIndex]->getThresholdIntensity())
                              objectsList[objectIndex]->cubeIndex  |=  1;
                        if (imageSet->getSlice( k )->getVoxelGray( i + stepSize , j )            > objectsList[objectIndex]->getThresholdIntensity())
                              objectsList[objectIndex]->cubeIndex  |=  2;
                        if (imageSet->getSlice( k )->getVoxelGray( i + stepSize , j + stepSize ) > objectsList[objectIndex]->getThresholdIntensity())
                              objectsList[objectIndex]->cubeIndex  |=  4;
                        if (imageSet->getSlice( k )->getVoxelGray( i , j + stepSize )            > objectsList[objectIndex]->getThresholdIntensity())
                              objectsList[objectIndex]->cubeIndex  |=  8;

                        if (imageSet->getSlice( k + stepSize )->getVoxelGray( i , j )                       > objectsList[objectIndex]->getThresholdIntensity())
                              objectsList[objectIndex]->cubeIndex  |=  16;
                        if (imageSet->getSlice( k + stepSize )->getVoxelGray( i + stepSize , j )            > objectsList[objectIndex]->getThresholdIntensity())
                              objectsList[objectIndex]->cubeIndex  |=  32;
                        if (imageSet->getSlice( k + stepSize )->getVoxelGray( i + stepSize , j + stepSize ) > objectsList[objectIndex]->getThresholdIntensity())
                              objectsList[objectIndex]->cubeIndex  |=  64;
                        if (imageSet->getSlice( k + stepSize )->getVoxelGray( i , j + stepSize )            > objectsList[objectIndex]->getThresholdIntensity())
                              objectsList[objectIndex]->cubeIndex  |=  128;

                        objectsList[objectIndex]->edgeIndex = edgeTable[objectsList[objectIndex]->cubeIndex];

                        if (objectsList[objectIndex]->edgeIndex == 0) // if no edge intersection
                            continue;       // skip to the next cube
                                              // else

                        if (objectsList[objectIndex]->edgeIndex & 1)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k, j, i, k, j, i + stepSize, &objectsList[objectIndex]->vertexList[0], &objectsList[objectIndex]->normalList[0] );
                        if (objectsList[objectIndex]->edgeIndex & 2)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k, j, i + stepSize, k , j + stepSize, i + stepSize, &objectsList[objectIndex]->vertexList[1], &objectsList[objectIndex]->normalList[1] );
                        if (objectsList[objectIndex]->edgeIndex & 4)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k , j + stepSize, i + stepSize,  k , j + stepSize, i, &objectsList[objectIndex]->vertexList[2], &objectsList[objectIndex]->normalList[2] );
                        if (objectsList[objectIndex]->edgeIndex & 8)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k , j + stepSize, i, k, j, i, &objectsList[objectIndex]->vertexList[3], &objectsList[objectIndex]->normalList[3] );
                        if (objectsList[objectIndex]->edgeIndex & 16)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k + stepSize, j, i, k + stepSize, j, i + stepSize, &objectsList[objectIndex]->vertexList[4], &objectsList[objectIndex]->normalList[4] );
                        if (objectsList[objectIndex]->edgeIndex & 32)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k + stepSize, j, i + stepSize, k + stepSize , j + stepSize, i + stepSize, &objectsList[objectIndex]->vertexList[5], &objectsList[objectIndex]->normalList[5] );
                        if (objectsList[objectIndex]->edgeIndex & 64)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k + stepSize , j + stepSize, i + stepSize,  k + stepSize , j + stepSize, i, &objectsList[objectIndex]->vertexList[6], &objectsList[objectIndex]->normalList[6] );
                        if (objectsList[objectIndex]->edgeIndex & 128)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k + stepSize , j + stepSize, i, k + stepSize, j, i, &objectsList[objectIndex]->vertexList[7], &objectsList[objectIndex]->normalList[7] );
                        if (objectsList[objectIndex]->edgeIndex & 256)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize, k, j, i, k + stepSize, j, i, &objectsList[objectIndex]->vertexList[8], &objectsList[objectIndex]->normalList[8] );
                        if (objectsList[objectIndex]->edgeIndex & 512)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize,k, j, i + stepSize, k + stepSize, j, i + stepSize, &objectsList[objectIndex]->vertexList[9], &objectsList[objectIndex]->normalList[9] );
                        if (objectsList[objectIndex]->edgeIndex & 1024)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize,k, j + stepSize, i + stepSize, k + stepSize, j + stepSize, i + stepSize, &objectsList[objectIndex]->vertexList[10], &objectsList[objectIndex]->normalList[10] );
                        if (objectsList[objectIndex]->edgeIndex & 2048)
                              interpolate( objectsList[objectIndex]->getThresholdIntensity(), stepSize,k, j + stepSize, i, k + stepSize, j + stepSize, i, &objectsList[objectIndex]->vertexList[11], &objectsList[objectIndex]->normalList[11] );

                        for (p = 0; p<5; p++)
                        {
                            if (triangleVerticesTable[objectsList[objectIndex]->cubeIndex][ 3 * p] < 0)
                                break;

                             for (q = 0; q<3; q++)
                             {
                                objectsList[objectIndex]->edgeNumber = triangleVerticesTable[objectsList[objectIndex]->cubeIndex][ 3*p + q];

                                objectsList[objectIndex]->normals[objectQualityStateIndex][3*objectsList[objectIndex]->triangleIndexes[objectQualityStateIndex] + q] = Point3Df(
                                        objectsList[objectIndex]->normalList[objectsList[objectIndex]->edgeNumber].x,
                                        objectsList[objectIndex]->normalList[objectsList[objectIndex]->edgeNumber].y,
                                        objectsList[objectIndex]->normalList[objectsList[objectIndex]->edgeNumber].z);

                                objectsList[objectIndex]->vertices[objectQualityStateIndex][3*objectsList[objectIndex]->triangleIndexes[objectQualityStateIndex] + q] = Point3Df(
                                        objectsList[objectIndex]->vertexList[objectsList[objectIndex]->edgeNumber].x,
                                        objectsList[objectIndex]->vertexList[objectsList[objectIndex]->edgeNumber].y,
                                        objectsList[objectIndex]->vertexList[objectsList[objectIndex]->edgeNumber].z);
                             } // of for(q =

                             objectsList[objectIndex]->triangleIndexes[objectQualityStateIndex]++;

                        } // of for (p =
                    } // of for (objectIndex =
                }  // of for (i =
            }  // of for (j =
        }  // of for (k =
    } // of for (objectuQalityIndex =

    generateLists();
} // of marchTheCubes




Object3D* MarchingCubesScene::addObject()
{
  if (totalObjects < MAX_OBJECT_NUMBER)
  {
    objectsList[totalObjects] = new Object3D(totalObjects, "Object " + AnsiString(totalObjects));
    objectsList[totalObjects]->setColor(Color3UnsignedChar( ((totalObjects%3 == 2) ? 255 - 12 * totalObjects : 0 ),
                                                            ((totalObjects%3 == 1) ? 255 - 12 * totalObjects : 0 ),
                                                            ((totalObjects%3 == 0) ? 255 - 12 * totalObjects : 0 )));
    totalObjects++;

    return objectsList[totalObjects-1];
  }
  else
    return NULL;
}


ClippingVolume* MarchingCubesScene::addClippingVolume()
{
  if (totalClippingVolumes < MAX_CLIPPING_VOLUME_NUMBER)
  {
    clippingVolumesList[totalClippingVolumes] = new ClippingVolume(0, "Clipping volume " + AnsiString(totalClippingVolumes));
    totalClippingVolumes++;

    return clippingVolumesList[totalClippingVolumes-1];
  }
  else
    return NULL;
}



static MarchingCubesScene *marchingCubesSceneForGLUT;


void setMarchingCubesScene(unsigned char* marchingCubesScene)
{
  marchingCubesSceneForGLUT = (MarchingCubesScene *) marchingCubesScene;
}


void handleReshape(int w, int h)
{
  int      smallest =  w <=   h ? w : h;
  GLfloat  border = marchingCubesSceneForGLUT->getSceneEdgeLength()/2.2;

  marchingCubesSceneForGLUT->setViewportWidth(smallest);

  glutReshapeWindow(smallest, smallest);
  glViewport(0, 0, smallest, smallest);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();


  glOrtho(-border, border,
           border, -border,
           border, -border
         );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void handleReshapeForNewImageSet(void)
{
  GLfloat  border = marchingCubesSceneForGLUT->getSceneEdgeLength()/2.2;

  glutReshapeWindow(marchingCubesSceneForGLUT->getViewportWidth(), marchingCubesSceneForGLUT->getViewportWidth());
  glViewport(0, 0, marchingCubesSceneForGLUT->getViewportWidth(), marchingCubesSceneForGLUT->getViewportWidth());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();


  glOrtho(-border, border,
           border, -border,
           border, -border
         );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}

void handleDisplay()
{
  static GLfloat tempElements[5];

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  tempElements[0] = marchingCubesSceneForGLUT->getLightSource()->getLightIntensityFloat()/5;
  tempElements[1] = tempElements[0];
  tempElements[2] = tempElements[0];
  tempElements[3] = 1.0;
  glLightfv(GL_LIGHT0, GL_AMBIENT,  tempElements);

  tempElements[0] = marchingCubesSceneForGLUT->getLightSource()->getLightIntensityFloat();
  tempElements[1] = tempElements[0];
  tempElements[2] = tempElements[0];
  tempElements[3] = 1.0;
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  tempElements);
  glLightfv(GL_LIGHT0, GL_SPECULAR, tempElements);

  glLighti(GL_LIGHT0, GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);
  glLightfv(GL_LIGHT0, GL_POSITION, marchingCubesSceneForGLUT->getLightSource()->getDirections());

  glRotatef(marchingCubesSceneForGLUT->getRotationX(), 1.0f, 0.0f, 0.0f);
  glRotatef(marchingCubesSceneForGLUT->getRotationY(), 0.0f, 1.0f, 0.0f);
  glRotatef(marchingCubesSceneForGLUT->getRotationZ(), 0.0f, 0.0f, 1.0f);

  glTranslatef(-marchingCubesSceneForGLUT->getImageSetWidthWorldSpace()/2,
               -marchingCubesSceneForGLUT->getImageSetHeightWorldSpace()/2,
               -marchingCubesSceneForGLUT->getImageSetDepthWorldSpace()/2
              );

  static unsigned int i,j,k,w,h,d;

  if (marchingCubesSceneForGLUT->getSelectedClippingVolume())
  {
    i = marchingCubesSceneForGLUT->getSelectedClippingVolume()->getCornerIndexI(),
    j = marchingCubesSceneForGLUT->getSelectedClippingVolume()->getCornerIndexJ(),
    k = marchingCubesSceneForGLUT->getSelectedClippingVolume()->getCornerIndexK(),
    w = marchingCubesSceneForGLUT->getSelectedClippingVolume()->getVolumeWidth(),
    h = marchingCubesSceneForGLUT->getSelectedClippingVolume()->getVolumeHeight(),
    d = marchingCubesSceneForGLUT->getSelectedClippingVolume()->getVolumeDepth();
  }

  static float voxelWidth,voxelHeight,voxelDepth;

  voxelWidth = marchingCubesSceneForGLUT->getVoxelWidth();
  voxelHeight = marchingCubesSceneForGLUT->getVoxelHeight();
  voxelDepth = marchingCubesSceneForGLUT->getVoxelDepth();


  switch (marchingCubesSceneForGLUT->getSceneState())
  {
     case STATE_CLIPPING_VOLUME  :
                                  for (int i = marchingCubesSceneForGLUT->getTotalObjectCount()-1; i >= 0; i--)
                                  {
                                    tempElements[0] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().red/255.0;
                                    tempElements[1] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().green/255.0;
                                    tempElements[2] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().blue/255.0;
                                    tempElements[3] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getAlpha()/255.0;
                                    tempElements[4] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getShininess();

                                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tempElements);
                                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tempElements);
                                    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, (GLint) tempElements[4]);

                                    glBegin(GL_TRIANGLES);
                                      glCallList(marchingCubesSceneForGLUT->getObjectAtIndex(i)->getListID(marchingCubesSceneForGLUT->getObjectQualityState()));
                                    glEnd();
                                  }


                                  glColor4f(1.0,1.0,1.0,1.0);
                                  glBegin(GL_LINES);
                                    glVertex3f(i*voxelWidth, j*voxelHeight, k*voxelDepth);
                                    glVertex3f((i+w)*voxelWidth, j*voxelHeight, k*voxelDepth);

                                    glVertex3f((i+w)*voxelWidth, j*voxelHeight, k*voxelDepth);
                                    glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);

                                    glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);
                                    glVertex3f(i*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);

                                    glVertex3f(i*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);
                                    glVertex3f(i*voxelWidth, j*voxelHeight, k*voxelDepth);

                                    glVertex3f((i+w)*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);
                                    glVertex3f(i*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);

                                    glVertex3f((i+w)*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);
                                    glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);

                                    glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                    glVertex3f(i*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);

                                    glVertex3f(i*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                    glVertex3f(i*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);

                                    glVertex3f(i*voxelWidth, j*voxelHeight, k*voxelDepth);
                                    glVertex3f(i*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);

                                    glVertex3f(i*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                    glVertex3f(i*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);

                                    glVertex3f((i+w)*voxelWidth, j*voxelHeight, k*voxelDepth);
                                    glVertex3f((i+w)*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);

                                    glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                    glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);
                                  glEnd();

                                   glDepthMask(GL_FALSE);
                                     glEnable(GL_BLEND);
                                       glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                                       glDisable(GL_LIGHTING);
                                         glColor4f(0.0,0.7,0.7,0.3);
                                         glBegin(GL_QUADS);
                                           glVertex3f(i*voxelWidth, j*voxelHeight, k*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, j*voxelHeight, k*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);
                                           glVertex3f(i*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);

                                           glVertex3f(i*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f(i*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);


                                           glVertex3f(i*voxelWidth, j*voxelHeight, k*voxelDepth);
                                           glVertex3f(i*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f(i*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f(i*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);

                                           glVertex3f((i+w)*voxelWidth, j*voxelHeight, k*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);


                                           glVertex3f(i*voxelWidth, j*voxelHeight, k*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, j*voxelHeight, k*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f(i*voxelWidth, j*voxelHeight, (k+d)*voxelDepth);

                                           glVertex3f(i*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, k*voxelDepth);
                                           glVertex3f((i+w)*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                           glVertex3f(i*voxelWidth, (j+h)*voxelHeight, (k+d)*voxelDepth);
                                         glEnd();

                                       glEnable(GL_LIGHTING);


                                     glDisable(GL_BLEND);
                                   glDepthMask(GL_TRUE);

                                   break;

     case STATE_TEXTURED_SURFACE :
                                   break;

     default                     :
                                   for (int i = marchingCubesSceneForGLUT->getTotalObjectCount()-1; i >= 0; i--)
                                     if (marchingCubesSceneForGLUT->getObjectAtIndex(i)->isVisible() && marchingCubesSceneForGLUT->getObjectAtIndex(i)->getAlpha() == 255)
                                     {
                                       tempElements[0] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().red/255.0;
                                       tempElements[1] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().green/255.0;
                                       tempElements[2] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().blue/255.0;
                                       tempElements[3] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getAlpha()/255.0;
                                       tempElements[4] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getShininess();

                                       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tempElements);
                                       glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tempElements);
                                       glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tempElements);
                                       glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, (GLint) tempElements[4]);

                                       glBegin(GL_TRIANGLES);
                                         glCallList(marchingCubesSceneForGLUT->getObjectAtIndex(i)->getListID(marchingCubesSceneForGLUT->getObjectQualityState()));
                                       glEnd();

                                     }

                                   glDepthMask(GL_FALSE);

                                   glEnable(GL_BLEND);
                                     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                                     for (int i =  marchingCubesSceneForGLUT->getTotalObjectCount()-1; i  >= 0; i--)
                                       if (marchingCubesSceneForGLUT->getObjectAtIndex(i)->isVisible() && marchingCubesSceneForGLUT->getObjectAtIndex(i)->getAlpha() != 255)
                                       {
                                         tempElements[0] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().red/255.0;
                                         tempElements[1] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().green/255.0;
                                         tempElements[2] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getColor().blue/255.0;
                                         tempElements[3] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getAlpha()/255.0;
                                         tempElements[4] = marchingCubesSceneForGLUT->getObjectAtIndex(i)->getShininess();

                                         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tempElements);
                                         glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tempElements);
                                         glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tempElements);
                                         glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, (GLint) tempElements[4]);

                                         glBegin(GL_TRIANGLES);
                                           glCallList(marchingCubesSceneForGLUT->getObjectAtIndex(i)->getListID(marchingCubesSceneForGLUT->getObjectQualityState()));
                                         glEnd();
                                       }
                                   glDisable(GL_BLEND);

                                   glDepthMask(GL_TRUE);

                                   break;

  }


  glutSwapBuffers();
}


void handleMouse(GLint button, GLint state, int x, int y)
{
  pressedMouseButton = button;

  if (state  ==  GLUT_DOWN)
    marchingCubesSceneForGLUT->setObjectQualityState(OBJECT_QUALITY_LOW);
  else
  {
    marchingCubesSceneForGLUT->setObjectQualityState(OBJECT_QUALITY_HIGH);
    glutPostRedisplay();
  }
  oldPixelsX = x;
  oldPixelsY = y;
}


void handleMouseMotion(int x, int y)
{
  if (pressedMouseButton  ==  GLUT_LEFT_BUTTON)
  {
    if (abs(y-oldPixelsY)>pixelChange)
    marchingCubesSceneForGLUT->setRotationX( marchingCubesSceneForGLUT->getRotationX() + rotationChange * (y-oldPixelsY) );

    if (abs(x-oldPixelsX)>pixelChange)
    marchingCubesSceneForGLUT->setRotationY( marchingCubesSceneForGLUT->getRotationY() + rotationChange * (x-oldPixelsX) );
  }
  else
  {
    if (abs(y-oldPixelsY)>pixelChange)
    marchingCubesSceneForGLUT->setRotationZ( marchingCubesSceneForGLUT->getRotationZ() + rotationChange * (y-oldPixelsY) );

    if (abs(x-oldPixelsX)>pixelChange)
    marchingCubesSceneForGLUT->setRotationZ( marchingCubesSceneForGLUT->getRotationZ() + rotationChange * (x-oldPixelsX) );
  }

  oldPixelsX = x;
  oldPixelsY = y;
  glutPostRedisplay();
}

