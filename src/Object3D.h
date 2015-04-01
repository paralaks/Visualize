#ifndef Object3DH
#define Object3DH

#include "Color3UnsignedChar.h"
#include "Point3Df.h"
#include <GL/glut.h>
#include <stdio.h>
#include <dstring.h>


class Object3D
{
  private:
    unsigned char       ID;
    AnsiString          name;
    bool                visible;

    GLint               listIDs[2];

    Color3UnsignedChar  color;

    unsigned char       shininess;
    unsigned char       alpha;

    unsigned char       thresholdIntensity;

  public:
    unsigned char       cubeIndex;
    unsigned int        edgeIndex;
    unsigned int        edgeNumber;

    unsigned long       totalTriangles[2];
    unsigned long       triangleIndexes[2];

    Point3Df           *normals[2];
    Point3Df           *vertices[2];


    Point3Df            vertexList [12];
    Point3Df            normalList [12];


    Object3D(unsigned char id, AnsiString n)
    {
      ID=id;
      name=n;

      thresholdIntensity=255;
      color=Color3UnsignedChar(150,150,150);

      visible=true;
      shininess=120;
      alpha=255;

      for (char q=0; q<2; q++)
      {
        listIDs[q]=0;

        totalTriangles[q]=0;
        triangleIndexes[q]=0;

        normals[q]  =NULL;
        vertices[q] =NULL;
      }

      cubeIndex=0;
      edgeIndex=0;
      edgeNumber=0;

      for (char i=0; i<12; i++)
      {
        vertexList[i]=Point3Df(0,0,0);
        normalList[i]=Point3Df(0,0,0);
      }
    }

    ~Object3D()
    {
      for (int i=0; i<2; i++)
      {
        if (normals[i])
          delete normals[i];
        if (vertices[i])
          delete vertices[i];
        if (listIDs[i]>0) 
          glDeleteLists(listIDs[i],1); 
      }
    }

    unsigned char getID()
    {
      return ID;
    }

    AnsiString getName()
    {
      return name;
    }

    bool isVisible()
    {
      return visible;
    }

    bool getVisible()
    {
      return visible;
    }

    GLint getListID(unsigned char i)
    {
      if (i==0 || i==1)
        return listIDs[i];
      else
        return -1;
    }

    Color3UnsignedChar getColor()
    {
      return color;
    }

    unsigned char getShininess()
    {
      return shininess;
    }

    unsigned char getAlpha()
    {
      return alpha;
    }

    unsigned char getThresholdIntensity()
    {
      return thresholdIntensity;
    }




    void setID(unsigned char id)
    {
      ID=id;
    }

    void setName(AnsiString n)
    {
      name=n;
    }

    void setVisible(bool v)
    {
      visible=v;
    }

    void setListID(unsigned char i, GLint l)
    {
      if (i==0 || i==1)
        listIDs[i]=l;
    }

    void setColor(Color3UnsignedChar c)
    {
      color=c;
    }

    void setShininess(unsigned char s)
    {
      shininess=s;
    }

    void setAlpha(unsigned char a)
    {
      alpha=a;
    }

    void setThresholdIntensity(unsigned char ti)
    {
      thresholdIntensity=ti;
    }
};

#endif