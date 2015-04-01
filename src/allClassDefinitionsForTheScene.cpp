MAX_OBJECT_NUMBER=20;
MAX_CLIPPING_VOLUME_NUMBER=20;
MAX_TEXTURED_SURFACE_NUMBER= 4 * MAX_CLIPPING_VOLUME_NUMBER;

class Object3D
{
  public:
    unsigned char       ID;
    AnsiString          name;
    unsigned char       intensity;
    bool                visible;
    GLint               listID;
    GLint               lowQualityListID;
    Color3UnsignedChar  ambient;
    Color3UnsignedChar  diffuse;
    Color3UnsignedChar  specular;
    unsigned char       shininess;
    unsigned char       alpha;
};

class ClippingVolume
{
  public:
    unsigned char  ID;
    AnsiString     name;
    unsigned int   voxelI;
    unsigned int   voxelJ;
    unsigned int   voxelK;
    unsigned int   volumeWidth;
    unsigned int   volumeHeight;
    unsigned int   volumeDepth;

    Object clippedObjectsList[MAX_OBJECT_NUMBER];
};


class TexturedSurface
{
  public:
    unsigned char ID;
    AnsiString    name;
    unsigned int  voxelI;
    unsigned int  voxelJ;
    unsigned int  voxelK;
};


class LightSource
{
  public:
    GLfloat       directionX;
    GLfloat       directionY;
    GLfloat       directionZ;

    Color         ambient
    Color         diffuse;
    Color         specular;
};


class MarchingCubesScene
{
  unsigned char   totalObjects;

  Light           lightSource;
  
  Object3D        objectsList[MAX_OBJECT_NUMBER];

  Object3D        selectedObject;
  Object3D        selectedObjects[MAX_OBJECT_NUMBER];

  ClippingVolume  clippingVolumesList[MAX_CLIPPING_VOLUME_NUMBER];

  TexturedSurface texturedSurfacesList[MAX_TEXTURED_SURFACE_NUMBER];

  GLfloat         sceneLeft;
  GLfloat         sceneTop;
  GLfloat         sceneNear;

  GLfloat         rotationX;
  GLfloat         rotationY;
  GLfloat         rotationZ;
};