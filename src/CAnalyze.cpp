/*

  Visualize uses Analyze library written by Fatih Nar ( https://www.linkedin.com/pub/fatih-nar/16/436/9b )

*/

#include <windows.h>
#include "CAnalyze.h"
#include "CAnalyzeLibrary.h"

CAnalyze::CAnalyze()
{
  slices = NULL;
  analyzeHeader = NULL;
  fileName = NULL;
  little_endian = true;

  for (int i=0; i<256; i++)
  {
    gradientMap[i] = RGB(i,i,i);
    selectedMap[i] = false;
  }
}

CAnalyze::~CAnalyze()
{
  if (fileName != NULL) delete fileName;
  clearSlices();
}

dsr* CAnalyze::getHeader(void)
{
  return analyzeHeader;
}

CSlice * CAnalyze::getSlice(int SliceNumber)
{
  if (SliceNumber>=0 && SliceNumber<getSliceCount())
     return &slices[SliceNumber];
  else return NULL;
}

bool CAnalyze::cloneHeader(dsr * danalyzeHeader)
{
  if (analyzeHeader != NULL && danalyzeHeader != NULL)
  {
    for (int i=0; i<8; i++)
        danalyzeHeader->dime.pixdim[i] = analyzeHeader->dime.pixdim[i]; 

    memcpy( &danalyzeHeader->hk, &analyzeHeader->hk, sizeof(header_key) );
    memcpy( &danalyzeHeader->hist, &analyzeHeader->hist, sizeof(data_history) );

    return true;
  }
  else return false;
}

CAnalyze * CAnalyze::cloneImage(bool copyColorMap)
{
  CAnalyze *cloned = new CAnalyze();
  if (cloned == NULL) return NULL;

  if (cloned->createSlices(getWidth(), getHeight(), getSliceCount(), getPixelFormat()) == false)
  {
    delete cloned;
    return NULL;
  }

  try
  {
    cloneHeader(cloned->analyzeHeader );
    cloned->little_endian = little_endian;

    if (copyColorMap == true)
    {
       memcpy(&cloned->gradientMap[0], &gradientMap[0], sizeof(int)*256 );
       memcpy(&cloned->selectedMap[0], &selectedMap[0], sizeof(bool)*256 );
    }

    for (int z=0; z<getSliceCount(); z++)
        memcpy(cloned->getSlice(z)->data[0], getSlice(z)->data[0], getSlice(z)->getRowSize()*getHeight() );
  }
  catch (...)
  {
    delete cloned;
    return NULL;
  }

  return cloned;
}

bool CAnalyze::copyData(CAnalyze *source)
{
  int sliceCount = getSliceCount();
  if (sliceCount == 0 ||
      source == NULL ||
      getWidth() != source->getWidth() ||
      source->getHeight() != source->getHeight() ||
      getPixelFormat() != source->getPixelFormat() )
      return false;
  else
  {
    for (int z=0; z<sliceCount; z++)
        memcpy(getSlice(z)->data[0], source->getSlice(z)->data[0], getSlice(z)->getRowSize()*getHeight() );
    return true;
  }
}

bool CAnalyze::createDefaultHeader(int SliceWidth,
                                   int SliceHeight,
                                   int SliceCount,
                                   int PixelFormat)
{
  if (analyzeHeader == NULL)
     analyzeHeader = new dsr();

  if (analyzeHeader != NULL)
  {
    analyzeHeader->hk.sizeof_hdr = HEADER_SIZE;
    analyzeHeader->hk.extents = 16384;
    analyzeHeader->hk.session_error = 0;
    analyzeHeader->hk.regular = 'r';
    analyzeHeader->hk.hkey_un0 = char(0);

    analyzeHeader->dime.dim[0] = 3;
    analyzeHeader->dime.dim[1] = SliceWidth;
    analyzeHeader->dime.dim[2] = SliceHeight;
    analyzeHeader->dime.dim[3] = SliceCount;
    analyzeHeader->dime.dim[4] = 0;
    analyzeHeader->dime.dim[5] = 0;
    analyzeHeader->dime.dim[6] = 0;
    analyzeHeader->dime.dim[7] = 0;
    analyzeHeader->dime.vox_units[0] = 'm';
    analyzeHeader->dime.vox_units[1] = 'm';
    analyzeHeader->dime.vox_units[2] = char(0);
    analyzeHeader->dime.cal_units[0] = char(0);
    analyzeHeader->dime.unused1 = 0;
    analyzeHeader->dime.datatype = PixelFormat;
    analyzeHeader->dime.bitpix = getVoxelBitCount(PixelFormat);
    analyzeHeader->dime.dim_un0 = 0;
    analyzeHeader->dime.pixdim[0] = 1.0;
    analyzeHeader->dime.pixdim[1] = 1.0;
    analyzeHeader->dime.pixdim[2] = 1.0;
    analyzeHeader->dime.pixdim[3] = 1.0;
    analyzeHeader->dime.pixdim[4] = 0.0;
    analyzeHeader->dime.pixdim[5] = 0.0;
    analyzeHeader->dime.pixdim[6] = 0.0;
    analyzeHeader->dime.pixdim[7] = 0.0;
    analyzeHeader->dime.vox_offset = 0.0;
    analyzeHeader->dime.roi_scale = 1.0;
    analyzeHeader->dime.unused1 = 0.0;
    analyzeHeader->dime.cal_max = 0.0;
    analyzeHeader->dime.cal_min = 0.0;
    analyzeHeader->dime.compressed = 0;
    analyzeHeader->dime.verified = 1;

    analyzeHeader->hist.descrip[0] = char(0);
    analyzeHeader->hist.aux_file[0] = char(0);
    analyzeHeader->hist.orient = char(0);
    analyzeHeader->hist.originator[0] = 0;
    analyzeHeader->hist.originator[1] = 0;
    analyzeHeader->hist.originator[2] = 0;
    analyzeHeader->hist.originator[3] = 0;
    analyzeHeader->hist.originator[4] = 0;
    analyzeHeader->hist.generated[0] = char(0);
    analyzeHeader->hist.scannum[0] = char(0);
    analyzeHeader->hist.patient_id[0] = char(0);
    analyzeHeader->hist.exp_date[0] = char(0);
    analyzeHeader->hist.exp_time[0] = char(0);
    analyzeHeader->hist.hist_un0[0] = char(0);
    analyzeHeader->hist.views = 0;
    analyzeHeader->hist.vols_added = 0;
    analyzeHeader->hist.start_field = 0;
    analyzeHeader->hist.field_skip = 0;
    analyzeHeader->hist.omax = 0;
    analyzeHeader->hist.omin = 0;
    analyzeHeader->hist.smax = 0;
    analyzeHeader->hist.smin = 0;

    return true;
  }
  else return false;
}

bool CAnalyze::createSlices(int SliceWidth,
                            int SliceHeight,
                            int SliceCount,
                            int PixelFormat)
{
  if ( SliceWidth>0 && SliceWidth<MAX_SIGNED_SHORT &&
       SliceHeight>0 && SliceHeight<MAX_SIGNED_SHORT &&
       SliceCount>0 && SliceCount<MAX_SIGNED_SHORT &&
       PixelFormat>0 && getVoxelBitCount(PixelFormat) != 0 )
  {
    if (analyzeHeader == NULL)
    {
      if (createDefaultHeader(SliceWidth, SliceHeight, SliceCount, PixelFormat) == false)
         return false;
    }

    slices = new CSlice[SliceCount];

    if (slices != NULL)
    {
      for (int z=0; z<SliceCount; z++)
      {
         if (slices[z].createSlice(SliceWidth, SliceHeight, PixelFormat) == false)
         {
           delete analyzeHeader;
           analyzeHeader = NULL;

           clearSlices();
           return false;
         }
      }

      return true;
    }
    else return false;
  }
  else return false;
}

bool CAnalyze::clearSlices(void)
{
  bool slicesExist = (analyzeHeader != NULL || slices != NULL);

  if (analyzeHeader != NULL)
  {
    delete analyzeHeader;
    analyzeHeader = NULL;
  }

  if (slices != NULL)
  {
    delete [] slices;
    slices = NULL;
  }

  return slicesExist;
}

bool CAnalyze::clearData(int value)
{
  int sliceCount = getSliceCount();
  if (sliceCount>0)
  {
    for (int z=0; z<sliceCount; z++)
        getSlice(z)->clearData(value);
    return true;
  }
  else return false;
}

bool CAnalyze::initializeVertexes(void)
{
  bool result = true;
  for (int z=0; z<getSliceCount(); z++)
  {
    CSlice *slice = getSlice(z);

    if ( slice != NULL)
       result = result && slice->initializeVertexes();
    else result = false;
  }
  return result;
}

bool CAnalyze::calculateVertexes(void)
{
  bool result = true;
  for (int z=0; z<getSliceCount(); z++)
  {
    CSlice *slice = getSlice(z);
    
    if ( slice != NULL)
       result = result && slice->calculateVertexes();
    else result = false;
  }
  return result;
}

bool CAnalyze::isCreated(void)
{
  return (analyzeHeader != NULL);
}

bool CAnalyze::isLittleEndian(void)
{
  return little_endian;
}

bool CAnalyze::swapBytes(void)
{
  int rowSize;
  int sheight = getHeight();
  unsigned char tmp;
  CSlice *slice;

  if (getPixelFormat() == DT_SIGNED_SHORT)
  {
    unsigned char *ptr;

    for (int z=0; z<getSliceCount(); z++)
    {
      slice = getSlice(z);
      rowSize = slice->getRowSize();

      ptr = slice->data[0];
      for (int y=0; y<sheight; y++)
      {
        for (int x=0; x<rowSize; x+=2)
        {
          tmp = *ptr;
          *ptr = *(ptr+1);
          *(ptr+1) = tmp;
          ptr+=2;
        }
      }
    }

    return true;
  }
  else return false;
}

bool CAnalyze::loadImage(char *FileName)
{
  int fnLen = strlen(FileName);
  if (fnLen<5) return false;

  if (analyzeHeader == NULL) analyzeHeader = new dsr();
  if (analyzeHeader == NULL) return false;
  char * buffer = (unsigned char *)analyzeHeader;

  try
  {
    ifstream file (FileName, ios::in|ios::binary|ios::ate);
    file.seekg (0, ios::beg);
    file.read (buffer, sizeof(dsr));
    file.close();
  }
  catch (...)
  {
    return false;
  }

  if (analyzeHeader->dime.dim[0] < 0 || analyzeHeader->dime.dim[0] > 15)
  {
     swap_hdr(analyzeHeader);
     little_endian = false;
  }
  else little_endian = true;

  FileName[fnLen-3] = 'i';
  FileName[fnLen-2] = 'm';
  FileName[fnLen-1] = 'g';

  if (createSlices(getWidth(), getHeight(), getSliceCount(), getPixelFormat()) == true)
  {
    ifstream file (FileName, ios::in|ios::binary|ios::ate);
    file.seekg (0, ios::beg);

    double roi_scale = getROIScale();
    bool scale_voxel;
    if (roi_scale != 1.0)
       scale_voxel = true;
    else scale_voxel = false;

    for (int z=0; z<getSliceCount(); z++)
    {
      int rowSize = getSlice(z)->getRowSize();
      CSlice * slice = getSlice(z);

      file.read (slice->data[0], getHeight()*rowSize);

      unsigned char *ptr1;
      unsigned char *ptr2;
      unsigned char tmp;
      int sheight = slice->getHeight();

      for (int y=0; y<sheight/2; y++)
      {
        ptr1 = slice->data[y];
        ptr2 = slice->data[sheight-y-1];
        for (int x=0; x<rowSize; x++)
        {
          tmp = *ptr1;
          *ptr1 = *ptr2;
          *ptr2 = tmp;

          ptr1++;
          ptr2++;
        }
      }

      if (getPixelFormat() == DT_SIGNED_SHORT)
      {
        unsigned char *ptr;
        short int *iptr;
        for (int y=0; y<sheight; y++)
        {
          ptr = slice->data[y];
          for (int x=0; x<rowSize; x+=2)
          {
            if (little_endian == false)
            {
              tmp = *ptr;
              *ptr = *(ptr+1);
              *(ptr+1) = tmp;
            }

            if (scale_voxel)
            {
              iptr = (short int *)ptr;

              if (*iptr<0) *iptr = 0;
              if (*iptr!=0) *iptr *= roi_scale;
            }

            ptr+=2;
          }
        }
      }
    }

    analyzeHeader->dime.roi_scale = 1.0;

    FileName[fnLen-3] = 'h';
    FileName[fnLen-2] = 'd';
    FileName[fnLen-1] = 'r';

    return true;
  }
  else
  {
    FileName[fnLen-3] = 'h';
    FileName[fnLen-2] = 'd';
    FileName[fnLen-1] = 'r';

    return false;
  }
}

bool CAnalyze::saveImage(char *FileName)
{
  if (!isCreated()) return false;
  
  int fnLen = strlen(FileName);
  if (fnLen<5) return false;

  char * buffer = (unsigned char *)analyzeHeader;

  ofstream hfile (FileName, ios::out|ios::binary|ios::ate);
  hfile.write(buffer, HEADER_SIZE);
  hfile.close();

  FileName[fnLen-3] = 'i';
  FileName[fnLen-2] = 'm';
  FileName[fnLen-1] = 'g';

  ofstream ifile (FileName, ios::out|ios::binary|ios::ate);

  for (int z=0; z<getSliceCount(); z++)
  {
    int height = getHeight();
    int rowSize = getSlice(z)->getRowSize();

    for (int y=height-1; y>=0; y--)
        ifile.write (getSlice(z)->data[y], rowSize);
  }
  ifile.close();

  FileName[fnLen-3] = 'h';
  FileName[fnLen-2] = 'd';
  FileName[fnLen-1] = 'r';

  return true;
}

bool CAnalyze::applyPixelMask(int pixelMask, int maskOperator)
{
  if (maskOperator!=PM_AND &&
      maskOperator!=PM_OR &&
      maskOperator!=PM_XOR)
      return false;

  int height = getHeight();
  int width = getWidth();
  int count = getSliceCount();

  CSlice *slice;
  for (int z=0; z<count; z++)
  {
    slice = getSlice(z);

    switch (getPixelFormat())
    {
      case DT_BINARY :
       {
         // sonra implement edilecek
         break;
       }
      case DT_UNSIGNED_CHAR :
       {
         unsigned char *ptr;
         ptr = (unsigned char *)(slice->data[0]);

         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             switch (maskOperator)
             {
               case PM_AND : *ptr = (*ptr) & pixelMask; break;
               case PM_OR  : *ptr = (*ptr) | pixelMask; break;
               case PM_XOR : *ptr = (*ptr) ^ pixelMask;
             }
             ptr++;
           }
         }
         break;
       }
      case DT_SIGNED_SHORT :
       {
         short int *ptr;
         ptr = (short int *)(slice->data[0]);
         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             switch (maskOperator)
             {
               case PM_AND : *ptr = (*ptr) & pixelMask; break;
               case PM_OR  : *ptr = (*ptr) | pixelMask; break;
               case PM_XOR : *ptr = (*ptr) ^ pixelMask;
             }
             ptr++;
           }
         }
         break;
       }
      case DT_SIGNED_INT :
       {
         int *ptr;
         ptr = (int *)(slice->data[0]);
         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             switch (maskOperator)
             {
               case PM_AND : *ptr = (*ptr) & pixelMask; break;
               case PM_OR  : *ptr = (*ptr) | pixelMask; break;
               case PM_XOR : *ptr = (*ptr) ^ pixelMask;
             }
             ptr++;
           }
         }
       }
    }
  }

  return true;
}

bool CAnalyze::normalizeVolume(void)
{
  switch (getPixelFormat())
  {
    case DT_UNSIGNED_CHAR : normalizeHistogram( MAX_UNSIGNED_CHAR ); return true;
    case DT_SIGNED_SHORT  : normalizeHistogram( MAX_SIGNED_SHORT );  return true;
    case DT_SIGNED_INT    : normalizeHistogram( MAX_SIGNED_INT );    return true;
    default : return false;
  }
}

float CAnalyze::normalizeHistogram(int maxColor)
{
  switch (getPixelFormat())
  {
    case DT_UNSIGNED_CHAR :
     {
       if (maxColor <= 0 || maxColor>MAX_UNSIGNED_CHAR) return false;

       unsigned char *ptr;

       unsigned char minValue = MAX_UNSIGNED_CHAR;
       unsigned char maxValue = 0;
       int height = getHeight();
       int width = getWidth();

       for (int z=0; z<getSliceCount(); z++)
       {
         CSlice *slice = getSlice(z);

         ptr = (unsigned char *)(slice->data[0]);
         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             if (*ptr>maxValue) maxValue = *ptr;
             if (*ptr<minValue) minValue = *ptr;
             ptr++;
           }
         }
       }

       if (maxValue<minValue) return false;

       double quantizer = double(maxValue - minValue)/maxColor;

       unsigned char value;
       for (int z=0; z<getSliceCount(); z++)
       {
         CSlice *slice = getSlice(z);

         ptr = (unsigned char *)(slice->data[0]);
         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             value = double(*ptr-minValue)/quantizer;
             if (value > maxColor) value = maxColor;
             *ptr = value;
             ptr++;
           }
         }
       }

       analyzeHeader->dime.glmin = 0;
       analyzeHeader->dime.glmax = maxColor;
       return true;
     }
    case DT_SIGNED_SHORT  :
     {
       if (maxColor <= 0 || maxColor>MAX_SIGNED_SHORT) return false;

       short int *ptr;

       short int minValue = MAX_SIGNED_SHORT;
       short int maxValue = 0;
       int height = getHeight();
       int width = getWidth();

       for (int z=0; z<getSliceCount(); z++)
       {
         CSlice *slice = getSlice(z);

         ptr = (short int *)(slice->data[0]);
         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             if (*ptr>maxValue) maxValue = *ptr;
             if (*ptr<minValue) minValue = *ptr;
             ptr++;
           }
         }
       }

       if (maxValue<minValue) return false;

       double quantizer = double(maxValue - minValue)/maxColor;

       short int value;
       for (int z=0; z<getSliceCount(); z++)
       {
         CSlice *slice = getSlice(z);

         ptr = (short int *)(slice->data[0]);
         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             value = double(*ptr-minValue)/quantizer;
             if (value > maxColor) value = maxColor;
             *ptr = value;
             ptr++;
           }
         }
       }

       analyzeHeader->dime.glmin = 0;
       analyzeHeader->dime.glmax = maxColor;
       return true;
     }
    case DT_SIGNED_INT    :
     {
       if (maxColor <=0 ) return false;

       int *ptr;

       int minValue = MAX_SIGNED_INT;
       int maxValue = 0;
       int height = getHeight();
       int width = getWidth();

       for (int z=0; z<getSliceCount(); z++)
       {
         CSlice *slice = getSlice(z);

         ptr = (int *)(slice->data[0]);
         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             if (*ptr>maxValue) maxValue = *ptr;
             if (*ptr<minValue) minValue = *ptr;
             ptr++;
           }
         }
       }

       if (maxValue<minValue) return false;

       double quantizer = double(maxValue - minValue)/maxColor;

       int value;
       for (int z=0; z<getSliceCount(); z++)
       {
         CSlice *slice = getSlice(z);

         ptr = (int *)(slice->data[0]);
         for (int y=0; y<height; y++)
         {
           for (int x=0; x<width; x++)
           {
             value = double(*ptr-minValue)/quantizer;
             if (value > maxColor) value = maxColor;
             *ptr = value;
             ptr++;
           }
         }
       }

       analyzeHeader->dime.glmin = 0;
       analyzeHeader->dime.glmax = maxColor;
       return true;
     }
    default : return false;
  }
}

int CAnalyze::getWidth(void)
{
  if (analyzeHeader != NULL)
    return analyzeHeader->dime.dim[1];
  else return 0;
}

int CAnalyze::getHeight(void)
{
  if (analyzeHeader != NULL)
    return analyzeHeader->dime.dim[2];
  else return 0;
}

int CAnalyze::getSliceCount(void)
{
  if (analyzeHeader != NULL)
    return analyzeHeader->dime.dim[3]; 
  else return 0;
}

void CAnalyze::setWorldSpace(point3dd worldSpace)
{
  analyzeHeader->dime.pixdim[1] = worldSpace.x;
  analyzeHeader->dime.pixdim[2] = worldSpace.y;
  analyzeHeader->dime.pixdim[3] = worldSpace.z;
}

point3dd CAnalyze::getWorldSpace(void)
{
  point3dd result;
  if (analyzeHeader != NULL)
  {
    for (int i=1; i<=3; i++)
        if (analyzeHeader->dime.pixdim[i]<0.0001) analyzeHeader->dime.pixdim[i] = 1.0;

    result.x = analyzeHeader->dime.pixdim[1];
    result.y = analyzeHeader->dime.pixdim[2];
    result.z = analyzeHeader->dime.pixdim[3];
  }
  else
  {
    result.x = 1.0;
    result.y = 1.0;
    result.z = 1.0;
  }

  return result;
}

void CAnalyze::setOrigin(point3dd origin)
{
  if (analyzeHeader != NULL)
  {
    analyzeHeader->hist.originator[0] = origin.x * 256;
    analyzeHeader->hist.originator[1] = origin.y * 256;
    analyzeHeader->hist.originator[2] = origin.z * 256;
    analyzeHeader->hist.originator[3] = 0;
    analyzeHeader->hist.originator[4] = 0;
  }
}

point3dd CAnalyze::getOrigin(void)
{
  point3dd result;
  if (analyzeHeader != NULL)
  {
    short int x,y,z;

    result.x = 0;
    result.y = 0;
    result.z = 0;

    x = analyzeHeader->hist.originator[0]/256;
    y = analyzeHeader->hist.originator[1]/256;
    z = analyzeHeader->hist.originator[2]/256;

    if (z == 0)
    {
      if (y == 0)
         result.z = x;
      else
      {
        result.y = x;
        result.z = y;
      }
    }
    else
    {
      result.x = x;
      result.y = y;
      result.z = z;
    }

    if (result.x <= 0)
       result.x = int(getWidth()/2.0);

    if (result.y <= 0)
       result.y = int(getHeight()/2.0);

    if (result.z <= 0)
       result.z = int(getSliceCount()/2.0);
  }
  else
  {
    result.x = int(getWidth()/2.0);
    result.y = int(getHeight()/2.0);
    result.z = int(getSliceCount()/2.0);
  }

  return result;
}

int CAnalyze::getPixelFormat(void)
{
  if (analyzeHeader != NULL)
    return analyzeHeader->dime.datatype;
  else return 0;
}

int CAnalyze::getPixelBitCount(int PixelFormat)
{
  if (analyzeHeader != NULL)
  {
     if (PixelFormat == -1)
        return analyzeHeader->dime.bitpix;
     else return getVoxelBitCount(PixelFormat);
  }
  else return 0;
}

int CAnalyze::getGLMin(void)
{
  if (analyzeHeader != NULL)
    return analyzeHeader->dime.glmin;
  else return 0;
}

int CAnalyze::getGLMax(void)
{
  if (analyzeHeader != NULL)
    return analyzeHeader->dime.glmax;
  else return 0;
}

int CAnalyze::findMinValue(void)
{
  int minColor = INT_MAX;

  for (int z=0; z<getSliceCount(); z++)
  {
    CSlice *slice = getSlice(z);
    
    int value;
    int width = getWidth();
    int height = getHeight();

    for (int y=0; y<height; y++)
    {
      for (int x=0; x<width; x++)
      {
        value = slice->getVoxel(x,y);
        if (value<minColor) minColor = value; 
      }
    }
  }

  return minColor;
}

int CAnalyze::findMaxValue(void)
{
  int width = getWidth();
  int height = getHeight();
  int count = getSliceCount();
  int maxColor = 0;
  int value;

  for (int z=0; z<count; z++)
  {
    CSlice *slice = getSlice(z);
    for (int y=0; y<height; y++)
    {
      for (int x=0; x<width; x++)
      {
        value = slice->getVoxel(x,y);
        if (value>maxColor) maxColor = value;
      }
    }
  }

  return maxColor;
}

float CAnalyze::getROIScale(void)
{
  if (analyzeHeader != NULL)
    return analyzeHeader->dime.roi_scale;
  else return 0.0;
}

void CAnalyze::setFileName(char *FileName)
{
  if (fileName != NULL) delete fileName;
  fileName = new char[strlen(FileName)+1];
  strcpy(fileName, FileName);
}

char * CAnalyze::getFileName(void)
{
  return fileName;
}

