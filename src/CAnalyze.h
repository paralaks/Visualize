#ifndef CAnalyzeH
#define CAnalyzeH

#include <iostream.h>
#include <fstream.h>

#include "dbh.h"
#include "CSlice.h"

#define IM_LINEER             0
#define IM_TRILINEER          1
#define IM_SINC               2
#define IM_FOURIER_SPACE      3

#define PM_AND                0
#define PM_OR                 1
#define PM_XOR                2

class CAnalyze
{
 private:
   CSlice         *slices;
   dsr            *analyzeHeader;
   char           *fileName;
   bool           little_endian;
 public:
   CAnalyze();
   ~CAnalyze();
   dsr*  getHeader(void);
   int gradientMap[256];
   bool selectedMap[256];
   CSlice * getSlice(int SliceNumber);
   bool cloneHeader(dsr * danalyzeHeader);
   CAnalyze * cloneImage(bool copyColorMap = false);
   bool  copyData(CAnalyze *source);
   bool  createDefaultHeader(int SliceWidth,
                             int SliceHeight,
                             int SliceCount,
                             int PixelFormat);
   bool  createSlices(int SliceWidth,
                      int SliceHeight,
                      int SliceCount,
                      int PixelFormat);
   bool  clearSlices(void);
   bool  clearData(int value = 0);
   bool  initializeVertexes(void);
   bool  calculateVertexes(void);
   bool  isCreated(void);
   bool  isLittleEndian(void);
   bool  swapBytes(void);
   bool  loadImage(char *FileName);
   bool  saveImage(char *FileName);
   bool  applyPixelMask(int pixelMask, int maskOperator);
   bool  normalizeVolume(void);
   float normalizeHistogram(int maxColor);
   int   getWidth(void);
   int   getHeight(void);
   int   getSliceCount(void);
   void setWorldSpace(point3dd worldSpace);
   point3dd getWorldSpace(void);
   void  setOrigin(point3dd origin);
   point3dd getOrigin(void);
   int   getPixelFormat(void);
   int   getPixelBitCount(int PixelFormat = -1);
   int   getGLMin(void);
   int   getGLMax(void);
   int   findMinValue(void);
   int   findMaxValue(void);
   float getROIScale(void);
   void  setFileName(char *FileName);
   char *getFileName(void);
};

#endif
