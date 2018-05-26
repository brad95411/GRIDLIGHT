#include "Collision2D.h"

Collision2D::Collision2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY,
  int16_t _endX, int16_t _endY, bool _isHorizontalScan, rgb24 _color1, rgb24 _color2, long _updateTime) :
  color1(_color1), color2(_color2), collisionInt(0)
{
  layer = _layer;
  refNum = _refNum;
  startX = _startX;
  startY = _startY;
  endX = _endX;
  endY = _endY;
  isHorizontalScan = _isHorizontalScan;
  updateTime = _updateTime;
  enabled = false;
}

void Collision2D::start(void)
{
  collisionInt = 0;
  timer = 0;
  enabled = true;
}

void Collision2D::stop(void)
{
  enabled = false;
}

bool Collision2D::update(void)
{
  if(enabled)
  {
    if(isNextFrame())
    {
      if(isHorizontalScan)
      {
        if(collisionInt == 0)
        {
          LEDUtils::clearSection(layer, startX, startY, endX, endY);
          
          layer->drawFastVLine(startX, startY, endY-1, color1);

          layer->drawFastVLine(endX - 1, startY, endY-1, color2);

          collisionInt++;
        }
        else if(collisionInt < (endX - startX))
        {
          layer->drawFastVLine(startX + collisionInt, startY, endY-1, color1);

          layer->drawFastVLine(endX - collisionInt - 1, startY, endY-1, color2);

          collisionInt++;
        }
        else
        {
          collisionInt = 0;
        }
      }
      else
      {
        if(collisionInt == 0)
        {
          LEDUtils::clearSection(layer, startX, startY, endX, endY);

          layer->drawFastHLine(startX, endX-1, startY, color1);

          layer->drawFastHLine(startX, endX-1, endY - 1, color2);

          collisionInt++;
        }
        else if(collisionInt < (endY - startY))
        {
          layer->drawFastHLine(startX, endX-1, startY + collisionInt, color1);

          layer->drawFastHLine(startX, endX-1, endY - collisionInt - 1, color2);

          collisionInt++;
        }
        else
        {
          collisionInt = 0;
        }
      }

      resetTimer();

      return true;
    }
  }
  return false;
}

