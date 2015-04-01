#ifndef Point3DfH
#define Point3DfH

class Point3Df
{
  public:
    float x,y,z;

    Point3Df(): x(0), y(0), z(0) {}
    Point3Df(float x, float y, float z): x(x), y(y), z(z) {}

    Point3Df &operator=(const Point3Df & point)
    {
      x = point.x;
      y = point.y;
      z = point.z;

      return *this;
    }

    float* float_type()
    {
      return &x;
    }

};

#endif