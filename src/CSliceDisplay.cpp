#include "CSliceDisplay.h"

extern Graphics::TBitmap* CreateBitmap(int width, int height, TPixelFormat pixelFormat)
{
  if (pixelFormat != pf1bit &&
      pixelFormat != pf8bit &&
      pixelFormat != pf24bit) return NULL;

  Graphics::TBitmap *Bitmap;

  RGBQUAD *oldColors;
  LOGPALETTE* pal = NULL;
  try
  {
    Bitmap = new Graphics::TBitmap();
    if (Bitmap == NULL) return NULL;
    Bitmap->PixelFormat = pixelFormat;
    Bitmap->HandleType = bmDIB;
    Bitmap->Width = width;
    Bitmap->Height = height;

    if (pixelFormat == pf8bit)
    {
      pal = (LOGPALETTE*) malloc( sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256);
      pal->palVersion = 0x300;
      pal->palNumEntries = 256;
      for(short i = 0 ; i < 256 ; i++)
      {
        pal->palPalEntry[i].peRed =  (Byte)i;
        pal->palPalEntry[i].peGreen = (Byte)i;
        pal->palPalEntry[i].peBlue = (Byte)i;
      }

      HPALETTE hpal = CreatePalette(pal);
      if(hpal) Bitmap->Palette = hpal;
    }
  }
  __finally
  {
    if (pal != NULL) delete pal;
  }

  return Bitmap;
}

CSlice* getFromBitmapData(Graphics::TBitmap *Bitmap, CSlice *slice)
{
  int width;
  int height;

  if (slice == NULL)
  {
    slice = new CSlice();
    if (slice == NULL) return NULL;

    width = Bitmap->Width;
    height = Bitmap->Height;
    int pixelFormat;
    switch (Bitmap->PixelFormat)
    {
     case pf1bit  : pixelFormat = DT_BINARY; break;
     case pf8bit  : pixelFormat = DT_UNSIGNED_CHAR; break;
     case pf24bit : pixelFormat = DT_RGB; break;
     default      : pixelFormat = DT_RGB; break;
    }
    slice->createSlice(width, height, pixelFormat);
  }
  else
  {
    width = Bitmap->Width;
    height = Bitmap->Height;

    if ( width!=slice->getWidth() ||
         height!=slice->getHeight() ) return NULL;
  }

  if ((Bitmap->PixelFormat==pf1bit && slice->getPixelFormat()==DT_BINARY) ||
      (Bitmap->PixelFormat==pf8bit && slice->getPixelFormat()==DT_UNSIGNED_CHAR) ||
      (Bitmap->PixelFormat==pf24bit && slice->getPixelFormat()==DT_RGB))
      {
        int rowsize = slice->getRowSize();
        for (int y=0; y<height; y++)
            memcpy(slice->data[y], Bitmap->ScanLine[y], rowsize);
      }
      else
      {
        for (int y=0; y<height; y++)
          for (int x=0; x<width; x++)
             slice->setVoxel(x, y, Bitmap->Canvas->Pixels[x][y]);
        // bu kýsým geliþtirilecek (hýz için optimize edilecek)
      }

  return slice;
}

Graphics::TBitmap* getFromSliceData(CSlice *slice, Graphics::TBitmap *Bitmap)
{
  int width = slice->getWidth();
  int height = slice->getHeight();

  if ( (Bitmap != NULL) &&
       (width != Bitmap->Width ||
        height != Bitmap->Height) )
  {
     delete Bitmap;
     Bitmap = NULL;
  }

  TPixelFormat pixelFormat;
  int slicePixelFormat = slice->getPixelFormat();

  switch (slicePixelFormat)
  {
   case DT_BINARY         : pixelFormat = pf1bit; break;
   case DT_UNSIGNED_CHAR  : pixelFormat = pf8bit; break;
   case DT_RGB            : pixelFormat = pf24bit; break;
   default                : pixelFormat = pf8bit; break;
  }

  if (Bitmap == NULL)
  {
    width = slice->getWidth();
    height = slice->getHeight();

    Bitmap = CreateBitmap(width, height, pixelFormat);
    if (Bitmap == NULL) return NULL;
  }

  if ((pixelFormat==pf1bit && slicePixelFormat==DT_BINARY) ||
      (pixelFormat==pf8bit && slicePixelFormat==DT_UNSIGNED_CHAR) ||
      (pixelFormat==pf24bit && slicePixelFormat==DT_RGB))
      {
        int rowsize = slice->getRowSize();
        for (int y=0; y<height; y++)
            memcpy(Bitmap->ScanLine[y], slice->data[y], rowsize);
      }
      else
      {
        switch (pixelFormat)
        {
         case pf1bit :
          {
            /*
            DT_UNSIGNED_CHAR
            DT_SIGNED_SHORT
            DT_SIGNED_INT
            DT_RGB
            */
            break;
          }
         case pf8bit :
          {
            // source 1,16,32,RGB

            unsigned char *bptr;

            switch (slicePixelFormat)
            {
             case DT_BINARY :
              {
                break;
              }
             case DT_SIGNED_SHORT :
              {
                short int *ptr;

                ptr = (short int *)slice->data[0];
                for (int y=0; y<height; y++)
                {
                  bptr = (unsigned char *)Bitmap->ScanLine[y];
                  for (int x=0; x<width; x++)
                  {
                    *bptr = (*ptr) >> 7;
                    bptr++;
                    ptr++;
                  }
                }
                break;
              }
             case DT_SIGNED_INT :
              {
                int *ptr;

                ptr = (int *)slice->data[0];
                for (int y=0; y<height; y++)
                {
                  bptr = (unsigned char *)Bitmap->ScanLine[y];
                  for (int x=0; x<width; x++)
                  {
                    *bptr = (*ptr) >> 23;
                    bptr++;
                    ptr++;
                  }
                }
                break;
              }
             case DT_RGB :
              {
                RGBVOXEL *ptr;

                ptr = (RGBVOXEL *)slice->data[0];
                for (int y=0; y<height; y++)
                {

                  bptr = (unsigned char *)Bitmap->ScanLine[y];
                  for (int x=0; x<width; x++)
                  {
                    *bptr = (ptr->Red + ptr->Green + ptr->Blue)/3;
                    bptr++;
                    ptr++;
                  }
                }
                break;
              }
            }
            break;
          }
         case pf24bit:
          {
            /*
            DT_BINARY
            DT_UNSIGNED_CHAR
            DT_SIGNED_SHORT
            DT_SIGNED_INT
            */
            break;
          }
        }
      }

  return Bitmap;
}

