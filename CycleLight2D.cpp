#include "CycleLight2D.h"

CycleLight2D::CycleLight2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY, 
  int16_t _endX, int16_t _endY, bool _isHorizontalScan, rgb24 _color1, rgb24 _color2, long _updateTime) :
  cycleLightInt(0), cycleLightBool(false), color1(_color1), color2(_color2)
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

void CycleLight2D::start(void)
{
  cycleLightInt = 0;
  cycleLightBool = false;
  timer = 0;
  enabled = true;
}

void CycleLight2D::stop(void)
{
  enabled = false;
}

bool CycleLight2D::update(void)
{
  if(enabled)
  {
    if(isNextFrame())
    {
      if(isHorizontalScan)
      {
        if((!cycleLightBool) && (cycleLightInt == 0))
        {
          LEDUtils::clearSection(layer, startX, startY, endX, endY);

          layer->drawFastVLine(startX, startY, endY - 1, color1);
          cycleLightInt++;
        }
        else if((cycleLightBool) && (cycleLightInt == 0))
        {
          LEDUtils::clearSection(layer, startX, startY, endX, endY);

          layer->drawFastVLine(startX, startY, endY - 1, color2);
          cycleLightInt++;
        }
        else if((!cycleLightBool) && (cycleLightInt < (endX - startX)))
        {
          layer->drawFastVLine(startX + cycleLightInt, startY, endY - 1, color1);
          cycleLightInt++;
        }
        else if((cycleLightBool) && (cycleLightInt < (endX - startX)))
        {
          layer->drawFastVLine(startX + cycleLightInt, startY, endY - 1, color2);
          cycleLightInt++;
        }
        else
        {
          cycleLightBool = !cycleLightBool;
          cycleLightInt = 0;
        }
      }
      else
      {
        if((!cycleLightBool) && (cycleLightInt == 0))
        {
          LEDUtils::clearSection(layer, startX, startY, endX, endY);

          layer->drawFastHLine(startX, endX - 1, startY, color1);
          cycleLightInt++;
        }
        else if((cycleLightBool) && (cycleLightInt == 0))
        {
          LEDUtils::clearSection(layer, startX, startY, endX, endY);

          layer->drawFastHLine(startX, endX - 1, startY, color2);
          cycleLightInt++;
        }
        else if((!cycleLightBool) && (cycleLightInt < (endY - startY)))
        {
          layer->drawFastHLine(startX, endX - 1, startY + cycleLightInt, color1);
          cycleLightInt++;
        }
        else if((cycleLightBool) && (cycleLightInt < (endY - startY)))
        {
          layer->drawFastHLine(startX, endX - 1, startY + cycleLightInt, color2);
          cycleLightInt++;
        }
        else
        {
          cycleLightBool = !cycleLightBool;
          cycleLightInt = 0;
        }
      }
      
      resetTimer();
      
      return true;
    }
  }
  return false;
}

