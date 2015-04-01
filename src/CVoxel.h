#ifndef CVoxelH
#define CVoxelH

#define DT_NONE				0
#define DT_UNKNOWN			0
#define DT_BINARY			1       // 1 bit per voxel
#define DT_UNSIGNED_CHAR		2       // 8 bit per voxel
#define DT_SIGNED_SHORT			4       // 16 bit per voxel
#define DT_SIGNED_INT			8       // 32 bit per voxel
#define DT_FLOAT			16      // 32 bit per voxel
#define DT_COMPLEX			32      // 64 bit per voxel
#define DT_DOUBLE			64      // 64 bit per voxel
#define DT_RGB				128     // 24 bit per voxel
#define DT_ALL				255

#define MAX_BINARY			1
#define MAX_UNSIGNED_CHAR		255
#define MAX_SIGNED_SHORT		32767
#define MAX_SIGNED_INT			((unsigned int)(1<<31)-1)


struct COMPLEX
{
  float real;
  float imag;
};

struct RGBVOXEL
{
  unsigned char Red;
  unsigned char Green;
  unsigned char Blue;
};

struct point2di {int x; int y;};
struct point3di {int x; int y; int z;};
struct point2df {float x; float y;};
struct point3df {float x; float y; float z;};
struct point2dd {double x; double y;};
struct point3dd {double x; double y; double z;};

extern point3di xyzi(int x,int y,int z);
extern point3dd xyzd(double x,double y,double z);
extern int getVoxelBitCount(int PixelFormat);
extern int calculateRowSize(int SliceWidth, int PixelFormat);

#endif
