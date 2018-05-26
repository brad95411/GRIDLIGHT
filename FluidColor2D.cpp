#include "FluidColor2D.h"

FluidColor2D::FluidColor2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY, 
  int16_t _endX, int16_t _endY, float _colorResolution, fluidTypes _type, long _updateTime) :
  type(_type), colorShifter(0), colorResolution(_colorResolution)
{
  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(FLUIDCOLOR2D):SETUP START"));
  }
  
  layer = _layer;
  refNum = _refNum;
  startX = _startX;
  startY = _startY;
  endX = _endX;
  endY = _endY;
  updateTime = _updateTime;
  enabled = false;

  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(FLUIDCOLOR2D):ELEMENTS"));
    SERIALPORT.print(F("ALERT(FLUIDCOLOR2D):REFNUM "));
    SERIALPORT.println(refNum);
    SERIALPORT.print(F("ALERT(FLUIDCOLOR2D):STARTX "));
    SERIALPORT.println(startX);
    SERIALPORT.print(F("ALERT(FLUIDCOLOR2D):STARTY "));
    SERIALPORT.println(startY);
    SERIALPORT.print(F("ALERT(FLUIDCOLOR2D):ENDX "));
    SERIALPORT.println(endX);
    SERIALPORT.print(F("ALERT(FLUIDCOLOR2D):ENDY "));
    SERIALPORT.println(endY);
    SERIALPORT.print(F("ALERT(FLUIDCOLOR2D):COLOR RESOLUTION MULTIPLIER "));
    SERIALPORT.println(colorResolution);
    SERIALPORT.print(F("ALERT(FLUIDCOLOR2D):UPDATETIME "));
    SERIALPORT.println(updateTime);
    SERIALPORT.println(F("ALERT(FLUIDCOLOR2D):GENERATE COLOR ARRAY"));
  }

  colors = new rgb24[(uint16_t)(360/colorResolution)];

  float* hsv = new float[3];

  hsv[1] = 1;
  hsv[2] = 1;
  
  for(uint16_t i = 0; i < 360/colorResolution; i++)
  {
    hsv[0] = colorResolution * i;

    LEDUtils::hsvToRGB(hsv, &colors[i]);
  }

  delete[] hsv;

  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(FLUIDCOLOR2D):SETUP COMPLETE"));
  }
}

void FluidColor2D::start(void)
{
  LEDUtils::clearSection(layer, startX, startY, endX, endY);
  colorShifter = 0;
  enabled = true;
}

void FluidColor2D::stop(void)
{
  enabled = false;
}

bool FluidColor2D::update(void)
{
  if(enabled)
  {
    if(isNextFrame())
    {
      if(type == kPixelByPixel)
      {
        for(int16_t x = 0; x < (endX - startX); x++)
        {
          for(int16_t y = 0; y < (endY - startY); y++)
          {
            layer->drawPixel(startX + x, startY + y, colors[((x * (endX - startX) + y) + colorShifter) % (uint16_t)(360/colorResolution)]);
          }
        }
      }
      else if(type == kVerticalScroll)
      {
        for(int16_t y = 0; y < (endY - startY); y++)
        {
          layer->drawFastHLine(startX, endX, startY + y, colors[(y + colorShifter) % (uint16_t)(360/colorResolution)]);
        }
      }
      else if(type == kHorizontalScroll)
      {
        for(int16_t x = 0; x < (endX - startX); x++)
        {
          layer->drawFastVLine(startX + x, startY, endY, colors[(x + colorShifter) % (uint16_t)(360/colorResolution)]);
        }
      }

      colorShifter++;

      if(colorShifter >= 360/colorResolution)
      {
        colorShifter = 0;
      }

      resetTimer();
      return true;
    }
  }
  
  return false;
}

fluidTypes FluidColor2D::ordinalToFluidType(uint8_t ordinal)
{
  switch(ordinal)
  {
    case 0:
      return kPixelByPixel;
    case 1:
      return kVerticalScroll;
    case 2:
    default:
      return kHorizontalScroll;
  }
}

String FluidColor2D::ordinalToHumanReadableName(uint8_t ordinal)
{
  switch(ordinal)
  {
    case 0:
      return "Pixel By Pixel";
    case 1:
      return "Vertical Scroll";
    case 2:
    default:
      return "Horizontal Scroll";
  }
}

