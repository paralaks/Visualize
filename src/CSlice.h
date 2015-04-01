#ifndef CSliceH
#define CSliceH

#include <stdlib.h>
#include <math.h>
#include <mem.h>

#include "CVoxel.h"

struct CVertexInfo {int vertex_start,vertex_end;};

class CSlice
{
 private:
   int width;
   int height;
   int pixelformat;
   int bitcount;
 public:
   CVertexInfo *vertexes;
   unsigned char **data;

   CSlice();
   ~CSlice();
   bool  createSlice(int SliceWidth,
                     int SliceHeight,
                     int PixelFormat);
   bool  clearSlice(void);
   bool  clearData(int value = 0);
   CSlice *cloneSlice(bool copyDate);
   bool  copyData(CSlice *target); 
   bool  initializeVertexes(void);
   bool  calculateVertexes(void);
   bool  isCreated(void);
   int   getWidth(void);
   int   getHeight(void);
   int   getPixelFormat(void);
   int   getPixelBitCount(int PixelFormat = -1);
   int   getRowSize(int SliceWidth = -1, int PixelFormat = -1);
   int   getDataSize(void);

   int           getVoxel(int x, int y);
   unsigned char getVoxelGray(int x, int y);
   unsigned char getVoxelBinary(int x, int y);
   unsigned char getVoxelByte(int x, int y);
   short int     getVoxelShortInt(int x, int y);
   int           getVoxelInt(int x, int y);
   float         getVoxelFloat(int x, int y);
   COMPLEX       getVoxelComplex(int x, int y);
   double        getVoxelDouble(int x, int y);
   RGBVOXEL      getVoxelRGB(int x, int y);

   void setVoxel(int x, int y, int value);
   void setVoxelBinary(int x, int y, unsigned char value);
   void setVoxelByte(int x, int y, unsigned char value);
   void setVoxelShortInt(int x, int y, short int value);
   void setVoxelInt(int x, int y, int value);
   void setVoxelFloat(int x, int y, float value);
   void setVoxelComplex(int x, int y, COMPLEX value);
   void setVoxelDouble(int x, int y, double value);
   void setVoxelRGB(int x, int y, RGBVOXEL value);
};

#endif
