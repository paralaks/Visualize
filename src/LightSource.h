#ifndef LightSourceH
#define LightSourceH

#include <GL/glut.h>
#include "Color3UnsignedChar.h"

class LightSource
{
  private:
    GLfloat         directions[4];
    unsigned char   intensity;


  public:

    LightSource(GLfloat directionX, GLfloat directionY, GLfloat directionZ, unsigned char lightIntensity)
    {
      directions[0] = directionX;
      directions[1] = directionY;
      directions[2] = directionZ;
      directions[3] = 0.0000000000000f;

      intensity = lightIntensity;
    }

    GLfloat getLightDirectionX()
    {
      return directions[0];
    }

    GLfloat getLightDirectionY()
    {
      return directions[1];
    }

    GLfloat getLightDirectionZ()
    {
      return directions[2];
    }

    unsigned char getLightIntensity()
    {
      return intensity;
    }

    float getLightIntensityFloat()
    {
      return (1.0*intensity/255.0);
    }

    float* getDirections()
    {
      return directions;
    }



    void setLightDirectionX(GLfloat directionX)
    {
      directions[0] = directionX;
    }

    void setLightDirectionY(GLfloat directionY)
    {
      directions[1] = directionY;
    }

    void setLightDirectionZ(GLfloat directionZ)
    {
      directions[2] = directionZ;
    }

    void setLightIntensity(unsigned char lightIntensity)
    {
      intensity = lightIntensity;
    }
};

#endif