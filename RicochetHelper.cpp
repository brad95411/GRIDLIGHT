#include "RicochetHelper.h"

RicochetHelper::RicochetHelper(int16_t _startPosX, int16_t _startPosY, int16_t _startX, int16_t _startY, int16_t _endX, int16_t _endY, rgb24 _color) :
  currentX(_startPosX), currentY(_startPosY), startX(_startX), startY(_startY), endX(_endX), endY(_endY), color(_color)
{
  xDir = random(0, 101) >= 51 ? -1 : 1;
  yDir = random(0, 101) >= 51 ? -1 : 1;
}

void RicochetHelper::updatePositions()
{
  currentX += xDir;
  currentY += yDir;

  if(currentX >= endX || currentX <= startX)
  {
    xDir *= -1;
  }

  if(currentY >= endY || currentY <= startY)
  {
    yDir *= -1;
  }
}

