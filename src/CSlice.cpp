#include "CSlice.h"

CSlice::CSlice()
{
  width = 0;
  height = 0;
  pixelformat = 0;
  bitcount = 0;

  vertexes = NULL;
  data = NULL;
}

CSlice::~CSlice()
{
  clearSlice();
}

bool CSlice::createSlice(int SliceWidth,
                         int SliceHeight,
                         int PixelFormat)
{
  clearSlice();

  vertexes = new CVertexInfo[SliceHeight];
  if (vertexes == NULL) return false;

  initializeVertexes();

  int rowSize = getRowSize(SliceWidth, PixelFormat);

  int dataSize = SliceHeight*rowSize;
  unsigned char *tmpdata = new unsigned char [dataSize];
  if (tmpdata == NULL)
  {
    clearSlice();
    return false;
  }
  memset(tmpdata, 0, dataSize);

  data = new unsigned char *[SliceHeight];

  width = SliceWidth;
  height = SliceHeight;
  pixelformat = PixelFormat;
  bitcount = getPixelBitCount(PixelFormat);

  for (int y=0; y<height; y++)
    data[y] = (tmpdata + y*rowSize);

  return true;
}

bool CSlice::clearSlice(void)
{
  if (vertexes != NULL)
     delete vertexes;

  if (data != NULL)
  {
    delete [] data;

    width = 0;
    height = 0;
    pixelformat = 0;
    bitcount = 0;
    data = NULL;

    return true;
  }
  else return false;
}

bool CSlice::clearData(int value)
{
  if (data != NULL)
  {
    int width = getWidth();
    int height = getHeight();

    switch (getPixelFormat())
    {
      case DT_UNSIGNED_CHAR:
      {
        memset(data, value, width*height);
        break;
      }
      case DT_SIGNED_SHORT:
      {
        short int *ptr;
        for (int y=0; y<height; y++)
        {
          ptr = (short int *)data[y];
          for (int x=0; x<width; x++)
          {
            *ptr = value;
            ptr++;
          }
        }
        break;
      }
      case DT_SIGNED_INT:
      {
        int *ptr;
        for (int y=0; y<height; y++)
        {
          ptr = (int *)data[y];
          for (int x=0; x<width; x++)
          {
            *ptr = value;
            ptr++;
          }
        }
        break;
      }
      default :
      {
        for (int y=0; y<height; y++)
          for (int x=0; x<width; x++)
            setVoxel(x,y,value);
      }
    }
    return true;
  }
  else return false;
}

CSlice * CSlice::cloneSlice(bool copyDate)
{
  CSlice * clonedSlice = new CSlice();
  if (clonedSlice == NULL) return NULL;

  if (clonedSlice->createSlice(width, height, pixelformat) == true)
  {
    if (copyDate == true)
       memcpy(clonedSlice->data[0], data[0], getRowSize()*height);
       
    return clonedSlice;
  }
  else
  {
    delete clonedSlice;
    return NULL;
  }
}

bool CSlice::copyData(CSlice *target)
{
  if (getHeight() == target->getHeight() &&
      getWidth() == target->getWidth() &&
      getPixelFormat() == target->getPixelFormat())
      {
        memcpy(target->data[0], data[0], getRowSize()*height);
        return true;
      }
      else return false;
}

bool CSlice::initializeVertexes(void)
{
  int width = getWidth();
  int height = getHeight();

  for (int y=0; y<height; y++)
  {
    vertexes[y].vertex_start = 0;
    vertexes[y].vertex_end = width-1;
  }

  return true;
}

bool CSlice::calculateVertexes(void)
{
  int width = getWidth();
  int height = getHeight();

  for (int y=0; y<height; y++)
  {
    vertexes[y].vertex_start = width-1;
    vertexes[y].vertex_end = 0;

    for (int x=0; x<width; x++)
    {
      if (getVoxel(x,y) != 0)
      {
        vertexes[y].vertex_start = x;
        break;
      }
    }

    for (int x=width-1; x>=0; x--)
    {
      if (getVoxel(x,y) != 0)
      {
        vertexes[y].vertex_end = x;
        break;
      }
    }
  }

  return true;
}

bool CSlice::isCreated(void)
{
  return (data != NULL);
}

int CSlice::getWidth(void)
{
  return width;
}

int CSlice::getHeight(void)
{
  return height;
}

int CSlice::getPixelFormat(void)
{
  return pixelformat;
}

int CSlice::getPixelBitCount(int PixelFormat)
{
  if (PixelFormat == -1)
     return bitcount;
  else return getVoxelBitCount(PixelFormat);
}

int CSlice::getRowSize(int SliceWidth, int PixelFormat)
{
  int rowWidth;
  if (SliceWidth == -1)
     rowWidth = width;
  else rowWidth = SliceWidth;

  if (PixelFormat == -1) PixelFormat = getPixelFormat();

  return calculateRowSize(rowWidth, PixelFormat);
}

int CSlice::getDataSize(void)
{
  return getRowSize()*getHeight();
}

int CSlice::getVoxel(int x, int y)
{
  if ( y<0 || y>=height || x<0 || x>=width) return 0; 

  COMPLEX cvalue;
  RGBVOXEL rvalue;

  switch (pixelformat)
  {
   case DT_BINARY	 : return getVoxelBinary(x,y);
   case DT_UNSIGNED_CHAR : return getVoxelByte(x,y);
   case DT_SIGNED_SHORT	 : return getVoxelShortInt(x,y);
   case DT_SIGNED_INT	 : return getVoxelInt(x,y);
   case DT_FLOAT	 : return getVoxelFloat(x,y);
   case DT_COMPLEX	 : cvalue = getVoxelComplex(x,y);
                           return sqrt(cvalue.real*cvalue.real + cvalue.imag*cvalue.imag);
   case DT_DOUBLE	 : return getVoxelDouble(x,y);
   case DT_RGB		 : rvalue = getVoxelRGB(x,y);
                           return (rvalue.Red << 16) | (rvalue.Green << 8) | rvalue.Blue;
   default : return 0;
  }
}

unsigned char CSlice::getVoxelGray(int x, int y)
{
  if ( y<0 || y>=height || x<0 || x>=width) return 0; 

  COMPLEX cvalue;
  RGBVOXEL rvalue;

  switch (pixelformat)
  {
   case DT_BINARY	 : return getVoxelBinary(x,y) << 8;
   case DT_UNSIGNED_CHAR : return getVoxelByte(x,y);
   case DT_SIGNED_SHORT	 : return getVoxelShortInt(x,y) >> 7;
   case DT_SIGNED_INT	 : return getVoxelInt(x,y) >> 23;

   //???
   case DT_FLOAT	 : return getVoxelFloat(x,y);
   case DT_COMPLEX	 : cvalue = getVoxelComplex(x,y);
                           return sqrt(cvalue.real*cvalue.real + cvalue.imag*cvalue.imag);
   case DT_DOUBLE	 : return getVoxelDouble(x,y);
   //???

   case DT_RGB		 : rvalue = getVoxelRGB(x,y);
                           return (rvalue.Red + rvalue.Green + rvalue.Blue)/3;
   default : return 0;
  }
}

unsigned char CSlice::getVoxelBinary(int x, int y)
{
  return ((data[y][x >> 3]) >> (7 - (x & 7)) ) & 1;
}

unsigned char CSlice::getVoxelByte(int x, int y)
{
  return data[y][x];
}

short int CSlice::getVoxelShortInt(int x, int y)
{
  return *(short int *)(&data[y][x<<1]);
}

int CSlice::getVoxelInt(int x, int y)
{
  return *(int *)(&data[y][x<<2]);
}

float CSlice::getVoxelFloat(int x, int y)
{
  return *(float *)(&data[y][x<<2]);
}

COMPLEX CSlice::getVoxelComplex(int x, int y)
{
  return *(COMPLEX *)(&data[y][x<<3]);
}

double CSlice::getVoxelDouble(int x, int y)
{
  return *(double *)(&data[y][x<<3]);
}

RGBVOXEL CSlice::getVoxelRGB(int x, int y)
{
  return *(RGBVOXEL *)(&data[y][x*3]);
}


void CSlice::setVoxel(int x, int y, int value)
{
  if ( y<0 || y>=height || x<0 || x>=width) return;

  switch (pixelformat)
  {
   case DT_BINARY	 : setVoxelBinary(x,y, value>0?1:0 ); break;
   case DT_UNSIGNED_CHAR : setVoxelByte(x,y, value); break;
   case DT_SIGNED_SHORT	 : setVoxelShortInt(x,y, value); break;
   case DT_SIGNED_INT	 : setVoxelInt(x,y, value); break;
   case DT_FLOAT	 : setVoxelFloat(x,y, value); break;
   case DT_COMPLEX	 :
     {
       COMPLEX cvalue;
       cvalue.real = value;
       cvalue.imag = 0;
       setVoxelComplex(x,y, cvalue); break;
     }
   case DT_DOUBLE	 : setVoxelDouble(x,y, value); break;
   case DT_RGB		 :
     {
       RGBVOXEL rvalue;
       rvalue.Blue = value & 0xff;
       value >>= 8;
       rvalue.Green = value & 0xff;
       value >>= 8;
       rvalue.Red = value & 0xff;

       setVoxelRGB(x,y, rvalue); break;
     }
  }
}

void CSlice::setVoxelBinary(int x, int y, unsigned char value)
{
  data[y][x >> 3] |= (value & 1) << (7 - (x & 7));
}

void CSlice::setVoxelByte(int x, int y, unsigned char value)
{
  data[y][x] = value;
}

void CSlice::setVoxelShortInt(int x, int y, short int value)
{
  *(short int *)(&data[y][x<<1]) = value;
}

void CSlice::setVoxelInt(int x, int y, int value)
{
  *(int *)(&data[y][x<<2]) = value;
}

void CSlice::setVoxelFloat(int x, int y, float value)
{
  *(float *)(&data[y][x<<2]) = value;
}

void CSlice::setVoxelComplex(int x, int y, COMPLEX value)
{
  *(COMPLEX *)(&data[y][x<<3]) = value;
}

void CSlice::setVoxelDouble(int x, int y, double value)
{
  *(double *)(&data[y][x<<3]) = value;
}

void CSlice::setVoxelRGB(int x, int y, RGBVOXEL value)
{
  *(RGBVOXEL *)(&data[y][x*3]) = value;
}

