#ifndef Color3UnsignedCharH
#define Color3UnsignedCharH

class Color3UnsignedChar
{
  public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Color3UnsignedChar(unsigned char r, unsigned char g, unsigned char b)
    {
      red   = r;
      green = g;
      blue  = b;
    }

    Color3UnsignedChar(const  Color3UnsignedChar & color)
    {
      red   = color.red;
      green = color.green;
      blue  = color.blue;
    }

    Color3UnsignedChar()
    {
      red   = 0;
      green = 0;
      blue  = 0;
    }

    Color3UnsignedChar& operator= (const  Color3UnsignedChar & color)
    {
      red   = color.red;
      green = color.green;
      blue  = color.blue;

      return *this;
    }
};

#endif

