#include "CVoxel.h"

point3di xyzi(int x,int y,int z)
{
  point3di xyz;
  xyz.x = x;
  xyz.y = y;
  xyz.z = z;
  return xyz;
}

point3dd xyzd(double x,double y,double z)
{
  point3dd xyz;
  xyz.x = x;
  xyz.y = y;
  xyz.z = z;
  return xyz;
}

int getVoxelBitCount(int PixelFormat)
{
  switch (PixelFormat)
  {
   case DT_BINARY	 : return 1; 
   case DT_UNSIGNED_CHAR : return 8;
   case DT_SIGNED_SHORT	 : return 16;
   case DT_SIGNED_INT	 : return 32;
   case DT_FLOAT	 : return 32;
   case DT_COMPLEX	 : return 64;
   case DT_DOUBLE	 : return 64;
   case DT_RGB		 : return 24;
   case -1               : return 0;
   default : return 0;
  }
}

int calculateRowSize(int SliceWidth, int PixelFormat)
{
  int bitsize = SliceWidth * getVoxelBitCount(PixelFormat);

  if (bitsize & 7 > 0)
    return (bitsize >> 3) + 1;
  else return (bitsize >> 3);
}

