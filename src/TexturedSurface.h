#ifndef TexturedSurfaceH
#define TexturedSurfaceH

#include <dstring.h>

class TexturedSurface
{

  private:
    unsigned char  ID;
    AnsiString     name;
    unsigned char  plane;
    unsigned int   voxelI;
    unsigned int   voxelJ;
    unsigned int   voxelK;


  public:
  
  TexturedSurface(unsigned char id, AnsiString n)
    {
      ID = id;
      name = n;

      plane  = 0;

      voxelI = 0;
      voxelJ = 0;
      voxelK = 0;
    }

    unsigned char getId()
    {
      return ID;
    }

    AnsiString getName()
    {
      return name;
    }
     
    unsigned char getPlane()
    {
      return plane;
    }

    unsigned int getPlaneIndexI()
    {
      return voxelI;
    }

    unsigned int getPlaneIndexJ()
    {
      return voxelJ;
    }

    unsigned int getPlaneIndexK()
    {
      return voxelK;
    }



    void setID(unsigned char id)
    {
      ID = id;
    }

    void setName(AnsiString n)
    {
      name = n;
    }

    void setPlane(unsigned char p)
    {
      plane = p;
    }

    void setPlaneIndexI(unsigned int i)
    {
      voxelI = i;
    }

    void setPlaneIndexJ(unsigned int j)
    {
      voxelJ = j;
    }

    void setPlaneIndexK(unsigned int k)
    {
      voxelK = k;
    }

};

#endif