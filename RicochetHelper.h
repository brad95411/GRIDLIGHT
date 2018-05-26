#ifndef RICOCHETHELPER_H
#define RICOCHETHELPER_H

#include <SmartMatrix3.h>

class RicochetHelper
{
  public:
    RicochetHelper() {}
    RicochetHelper(int16_t _startPosX, int16_t _startPosY, int16_t _startX, int16_t _startY, int16_t _endX, int16_t _endY, rgb24 _color);

    int16_t getCurrentXPos() { return currentX; }
    int16_t getCurrentYPos() { return currentY; }

    rgb24 getCurrentColor() { return color; }

    void setCurrentColor(rgb24 _color) { color = _color; }
    
    void updatePositions();

  private:
    int16_t
      currentX,
      currentY,
      startX,
      startY,
      endX,
      endY;
    int8_t
      xDir,
      yDir;
    rgb24
      color;
};

#endif
