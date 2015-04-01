#ifndef CSliceDisplayH
#define CSliceDisplayH

#include <graphics.hpp>

#include "CSlice.h"

extern Graphics::TBitmap* CreateBitmap(int width, int height, TPixelFormat pixelFormat = pf8bit);
CSlice* getFromBitmapData(Graphics::TBitmap *Bitmap, CSlice *slice = NULL);
Graphics::TBitmap* getFromSliceData(CSlice *slice, Graphics::TBitmap *Bitmap = NULL);

#endif
