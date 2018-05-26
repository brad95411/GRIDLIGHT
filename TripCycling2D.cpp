#include "TripCycling2D.h"

TripCycling2D::TripCycling2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, 
  int16_t _startX, int16_t _startY, int16_t _endX, int16_t _endY, uint16_t _sizeOfTrip, 
  bool _isHorizontalScan, rgb24 _color1, rgb24 _color2, long _updateTime) :
  color1(_color1), color2(_color2), sizeOfTrip(_sizeOfTrip), isHorizontalScan(_isHorizontalScan),
  tripCycleInt(0), tripCycleBool(false)
{
  layer = _layer;
  refNum = _refNum;
  startX = _startX;
  startY = _startY;
  endX = _endX;
  endY = _endY;
  updateTime = _updateTime;
  enabled = false;
}

void TripCycling2D::start(void)
{
  tripCycleInt = 0;
  tripCycleBool = false;
  timer = 0;
  enabled = true;
}

void TripCycling2D::stop(void)
{
  enabled = false;
}

bool TripCycling2D::update(void)
{
  if(enabled)
  {
    if(timer > updateTime)
    {
      if((!tripCycleBool) && (tripCycleInt == 0))
      {
        LEDUtils::clearSection(layer, startX, startY, endX, endY);

        if(isHorizontalScan)
        {
          LEDUtils::setAll(layer, startX + sizeOfTrip, startY, endX, endY, color2);
          LEDUtils::setAll(layer, startX, startY, startX + sizeOfTrip, endY, color1);
        }
        else
        {
          LEDUtils::setAll(layer, startX, startY + sizeOfTrip, endX, endY, color2);
          LEDUtils::setAll(layer, startX, startY, endX, startY + sizeOfTrip, color1);
        }

        tripCycleInt++;
      }
      else if((tripCycleBool) && (tripCycleInt == 0))
      {
        LEDUtils::clearSection(layer, startX, startY, endX, endY);

        if(isHorizontalScan)
        {
          LEDUtils::setAll(layer, startX + sizeOfTrip, startY, endX, endY, color1);
          LEDUtils::setAll(layer, startX, startY, startX + sizeOfTrip, endY, color2);
        }
        else
        {
          LEDUtils::setAll(layer, startX, startY + sizeOfTrip, endX, endY, color1);
          LEDUtils::setAll(layer, startX, startY, endX, startY + sizeOfTrip, color2);
        }

        tripCycleInt++;
      }
      else if((!tripCycleBool) && (tripCycleInt < (isHorizontalScan ? (endX - startX) - 1 : (endY - startY) - 1)))
      {
        if(isHorizontalScan)
        {
          layer->drawFastVLine(startX + tripCycleInt + sizeOfTrip - 1, startY, endY-1, color1);
          layer->drawFastVLine(startX + tripCycleInt - 1, startY, endY-1, color2);
        }
        else
        {
          layer->drawFastHLine(startX, endX - 1, startY + tripCycleInt + sizeOfTrip - 1, color1);
          layer->drawFastHLine(startX, endX - 1, startY + tripCycleInt - 1, color2);
        }

        tripCycleInt++;
      }
      else if((tripCycleBool) && (tripCycleInt < (isHorizontalScan ? (endX - startX) - 1 : (endY - startY) - 1)))
      {
        if(isHorizontalScan)
        {
          layer->drawFastVLine(startX + tripCycleInt + sizeOfTrip - 1, startY, endY-1, color2);
          layer->drawFastVLine(startX + tripCycleInt - 1, startY, endY-1, color1);
        }
        else
        {
          layer->drawFastHLine(startX, endX - 1, startY + tripCycleInt + sizeOfTrip - 1, color2);
          layer->drawFastHLine(startX, endX - 1, startY + tripCycleInt - 1, color1);
        }

        tripCycleInt++;
      }
      else
      {
        tripCycleBool = !tripCycleBool;
        tripCycleInt = 0;
      }

      timer = 0;

      return true;
    }
  }

  return false;
}

