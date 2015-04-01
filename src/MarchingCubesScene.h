#ifndef MarchingCubesSceneH
#define MarchingCubesSceneH

#include <system.hpp>
#include "MarchingCubesSceneConstants.h"
#include "MarchingCubesTables.h"
#include "Color3UnsignedChar.h"
#include "Point3Df.h"
#include "LightSource.h"
#include "Object3D.h"
#include "ClippingVolume.h"
#include "TexturedSurface.h"
#include "CAnalyze.h"
#include <dstring.h>
#include <GL/glut.h>

extern void sendFeedback(AnsiString );

extern const unsigned char pixelChange;
extern const float         rotationChange;
extern int                 oldPixelsX;
extern int                 oldPixelsY;

extern GLint               pressedMouseButton;

extern void setMarchingCubesScene(unsigned char*);
extern void handleReshape(int, int);
extern void handleReshapeForNewImageSet(void);
extern void handleDisplay();
extern void handleMouse(GLint, GLint, int, int);
extern void handleMouseMotion(int, int);

class MarchingCubesScene
{
  private:
    unsigned char     totalObjects;
    unsigned char     totalClippingVolumes;
    unsigned char     totalTexturedSurfaces;

    CAnalyze         *imageSet;

    float             voxelWidth;
    float             voxelHeight;
    float             voxelDepth;

    unsigned int      imageSetWidth;
    unsigned int      imageSetHeight;
    unsigned int      imageSetDepth;

    float             imageSetWidthWorldSpace;
    float             imageSetHeightWorldSpace;
    float             imageSetDepthWorldSpace;

    LightSource      *lightSource;

    Object3D         *objectsList[MAX_OBJECT_NUMBER];
    Object3D         *selectedObject;

    ClippingVolume   *clippingVolumesList[MAX_CLIPPING_VOLUME_NUMBER];
    ClippingVolume   *selectedClippingVolume;

    TexturedSurface  *texturedSurfacesList[MAX_TEXTURED_SURFACE_NUMBER];
    TexturedSurface  *selectedTexturedSurface;

    unsigned char     objectQualityState;
    unsigned char     sceneState;

    GLfloat           sceneEdgeLength;

    GLint             viewportWidth;

    GLfloat           rotationX;
    GLfloat           rotationY;
    GLfloat           rotationZ;

  public:

    MarchingCubesScene();
    void setImageSet(CAnalyze* analyzeImage);
    void initializeMarchingCubesScene();
    ~MarchingCubesScene();
    void calculateTotalTriangles();
    void generateLists();
    void interpolate(
                      unsigned char thresholdIntensity, unsigned short stepSize,
                      short int indexK, short int indexJ, short int indexI,
                      short int nextK, short int nextJ, short int nextI,
                      Point3Df* vertexPointer, Point3Df* normalPointer
                    );
    void marchTheCubes();
    Object3D* addObject();
    ClippingVolume* addClippingVolume();


    void updateScene()
    {
      glutPostRedisplay();
    }

    CAnalyze* getImageSet()
    {
      return imageSet;
    }

    LightSource *getLightSource()
    {
      return lightSource;
    }

    Object3D* getObjectAtIndex(unsigned char index)
    {
      if(index < MAX_OBJECT_NUMBER)
        return objectsList[index];
      else
        return NULL;
    }

    Object3D* getSelectedObject()
    {
      return selectedObject;
    }

    unsigned char getTotalObjectCount()
    {
      return totalObjects;
    }

    ClippingVolume* getClippingVolumeAtIndex(unsigned char index)
    {
      if(index < MAX_CLIPPING_VOLUME_NUMBER)
        return clippingVolumesList[index];
      else
        return NULL;
    }

    ClippingVolume* getSelectedClippingVolume()
    {
      return selectedClippingVolume;
    }

    unsigned char getTotalClippingVolumeCount()
    {
      return totalClippingVolumes;
    }

    unsigned char getObjectQualityState()
    {
      return objectQualityState;
    }

    float getImageSetWidthWorldSpace()
    {
      return imageSetWidthWorldSpace;
    }

    float getImageSetHeightWorldSpace()
    {
      return imageSetHeightWorldSpace;
    }

    float getImageSetDepthWorldSpace()
    {
      return imageSetDepthWorldSpace;
    }

    float getVoxelWidth()
    {
      return voxelWidth;
    }

    float getVoxelHeight()
    {
      return voxelHeight;
    }

    float getVoxelDepth()
    {
      return voxelDepth;
    }

    unsigned char getSceneState()
    {
      return sceneState;
    }

    GLfloat getSceneEdgeLength()
    {
      return sceneEdgeLength;
    }

    GLint getViewportWidth()
    {
      return viewportWidth;
    }

    GLfloat getRotationX()
    {
      return rotationX;
    }

    GLfloat getRotationY()
    {
      return rotationY;
    }

    GLfloat getRotationZ()
    {
      return rotationZ;
    }



    void setSelectedObject(Object3D* object)
    {
      selectedObject = object;
    }

    void setSelectedObjectAtIndex(unsigned char index)
    {
      if(index < MAX_OBJECT_NUMBER)
        selectedObject = objectsList[index];
      else
        selectedObject = NULL;
    }

    void setSelectedClippingVolume(ClippingVolume* clippingVolume)
    {
      selectedClippingVolume = clippingVolume;
    }

    void setSelectedClippingVolumeAtIndex(unsigned char index)
    {
      if(index < MAX_CLIPPING_VOLUME_NUMBER)
        selectedClippingVolume = clippingVolumesList[index];
      else
        selectedClippingVolume = NULL;
    }

    void setObjectQualityState(unsigned char state)
    {
      objectQualityState = state;
    }

    void setSceneState(unsigned char state)
    {
      sceneState = state;
    }

    void setSceneEdgeLength(GLfloat s)
    {
      sceneEdgeLength=s;
    }

    void setViewportWidth(GLint w)
    {
      viewportWidth=w;
    }

    void setRotationX(GLfloat x)
    {
      rotationX=x;
    }

    void setRotationY(GLfloat y)
    {
      rotationY=y;
    }

    void setRotationZ(GLfloat z)
    {
      rotationZ=z;
    }


    void reshapeForNewImageSet()
    {
      handleReshapeForNewImageSet();
    }

};


#endif

