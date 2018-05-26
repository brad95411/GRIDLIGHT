#include "Alternate2D.h"

Alternate2D::Alternate2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY,
  int16_t _endX, int16_t _endY, bool _isHorizontalScan, rgb24* _colors, uint8_t _numColors, long _updateTime) :
  colors(new rgb24[_numColors]), numColors(_numColors), alternateInt(0)
{
  layer = _layer;
  refNum = _refNum;
  startX = _startX;
  startY = _startY;
  isHorizontalScan = _isHorizontalScan;
  endX = _endX;
  endY = _endY;
  updateTime = _updateTime;

  for(uint8_t i = 0; i < numColors; i++)
  {
    colors[i] = _colors[i];
  }

  enabled = false;
}

void Alternate2D::start(void)
{
  alternateInt = 0;
  timer = 0;
  enabled = true;
}

void Alternate2D::stop(void)
{
  enabled = false;
}

bool Alternate2D::update(void)
{
  if(enabled)
  {
    if(isNextFrame())
    {
      if(isHorizontalScan)
      {
        for(int16_t i = startX; i < endX; i++)
        {
          layer->drawFastVLine(i, startY, endY-1, colors[(i + alternateInt) % numColors]);
        }
      }
      else
      {
        for(int16_t i = startY; i < endY; i++)
        {
          layer->drawFastHLine(startX, endX-1, i, colors[(i + alternateInt) % numColors]);
        }
      }

      alternateInt++;

      if(alternateInt >= numColors)
      {
        alternateInt = 0;
      }

      resetTimer();

      return true;
    }
  }
  return false;
}

