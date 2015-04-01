#ifndef ClippingVolumeH
#define ClippingVolumeH

#include <dstring.h>
#include "MarchingCubesSceneConstants.h"

extern void sendFeedback(AnsiString );

class ClippingVolume
{
  private:
    unsigned char  ID;
    AnsiString     name;
    unsigned int   voxelI;
    unsigned int   voxelJ;
    unsigned int   voxelK;
    unsigned int   volumeWidth;
    unsigned int   volumeHeight;
    unsigned int   volumeDepth;

    bool           clippedObjectsList[MAX_OBJECT_NUMBER];

  public:

    ClippingVolume(unsigned char volumeId, AnsiString volumeName)
    {
      ID = volumeId;
      name = volumeName;

      voxelI = 0;
      voxelJ = 0;
      voxelK = 0;

      volumeWidth  = 15;
      volumeHeight = 15;
      volumeDepth  = 15;

      for (int i = 0; i<MAX_OBJECT_NUMBER; i++)
        clippedObjectsList[i] = false;
    }

    unsigned char getID()
    {
      return ID;
    }

    AnsiString getName()
    {
      return name;
    }

    unsigned int getCornerIndexI()
    {
      return voxelI;
    }

    unsigned int getCornerIndexJ()
    {
      return voxelJ;
    }

    unsigned int getCornerIndexK()
    {
      return voxelK;
    }

    unsigned int getVolumeWidth()
    {
      return volumeWidth;
    }

    unsigned int getVolumeHeight()
    {
      return volumeHeight;
    }

    unsigned int getVolumeDepth()
    {
      return volumeDepth;
    }

    bool getClippedStateAtIndex(unsigned char index)
    {
      if (index<MAX_OBJECT_NUMBER)
        return clippedObjectsList[index];
       else
         return false;
    }




    void setID(unsigned char volumeID)
    {
      ID = volumeID;
    }

    void setName(AnsiString volumeName)
    {
      name = volumeName;
    }

    void setCornerIndexI(unsigned int index)
    {
      voxelI = index;
    }

    void setCornerIndexJ(unsigned int index)
    {
      voxelJ = index;
    }

    void setCornerIndexK(unsigned int index)
    {
      voxelK = index;
    }

    void setVolumeWidth(unsigned int width)
    {
      volumeWidth = width;
    }

    void setVolumeHeight(unsigned int height)
    {
      volumeHeight = height;
    }

    void setVolumeDepth(unsigned int depth)
    {
      volumeDepth = depth;
    }

    void setClippedStateAtIndex(unsigned char volumeIndex, bool state)
    {
      if (volumeIndex<MAX_OBJECT_NUMBER)
        clippedObjectsList[volumeIndex] = state;
    }

    bool isPointInsideVoxelIJKForObject(unsigned int i, unsigned int j, unsigned int k, unsigned char objectIndex)
    {
      if (   (clippedObjectsList[objectIndex] == true)
           &&
             (i >= voxelI) && (i < voxelI+volumeWidth)
           &&
             (j >= voxelJ) && (j < voxelJ+volumeHeight)
           &&
             (k >= voxelK) && (k < voxelK+volumeDepth)

         )
        return true;
      else
        return false;
    }
};

#endif