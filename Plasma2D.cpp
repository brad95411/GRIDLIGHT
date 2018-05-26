#include "Plasma2D.h"

Plasma2D::Plasma2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY, int16_t _endX, int16_t _endY, long _updateTime) :
paletteShift(0), palette(new rgb24[256])
{
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
    SERIALPORT.println(F("ALERT(PLASMA2D):ELEMENTS"));
    SERIALPORT.print(F("ALERT(PLASMA2D):REFNUM "));
    SERIALPORT.println(refNum);
    SERIALPORT.print(F("ALERT(PLASMA2D):STARTX "));
    SERIALPORT.println(startX);
    SERIALPORT.print(F("ALERT(PLASMA2D):STARTY "));
    SERIALPORT.println(startY);
    SERIALPORT.print(F("ALERT(PLASMA2D):ENDX "));
    SERIALPORT.println(endX);
    SERIALPORT.print(F("ALERT(PLASMA2D):ENDY "));
    SERIALPORT.println(endY);
    SERIALPORT.print(F("ALERT(PLASMA2D):UPDATETIME "));
    SERIALPORT.println(updateTime);
    SERIALPORT.println(F("ALERT(PLASMA2D):SETUP PLASMA ARRAY"));
  }
 
  plasma = new uint8_t*[endX - startX];

  for(int16_t i = 0; i < (endX - startX); i++)
  {
    plasma[i] = new uint8_t[endY - startY];
  }

  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(PLASMA2D):CALCULATE PLASMA WAVE"));
  }

  for(int16_t i = 0; i < (endX - startX); i++)
  {
    for(int16_t j = 0; j < (endY - startY); j++)
    {
      plasma[i][j] = (uint8_t) ((128.0 + (128 * sinf(i/8.0)) + 128 + (128.0 * sinf(j/8.0)))/2);
    }
  }

  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(PLASMA2D):GENERATE HSV COLOR MAP"));
  }

  float* hsv = new float[3];

  for(uint16_t i = 0; i < 256; i++)
  {
    hsv[0] = map(i, 0, 255, 0, 359);
    hsv[1] = 1;
    hsv[2] = 1;
    
    LEDUtils::hsvToRGB(hsv, &palette[i]);
  }

  delete[] hsv;

  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(PLASMA2D):SETUP COMPLETE"));
  }
}

Plasma2D::~Plasma2D()
{
  delete[] palette;

  for(int16_t i = 0; i < (endX - startX); i++)
  {
    delete[] plasma[i];
  }

  delete[] plasma;
}

void Plasma2D::start(void)
{
  paletteShift = 0;
  timer = 0;
  enabled = true;
}

void Plasma2D::stop(void)
{
  enabled = false;
}

bool Plasma2D::update(void)
{
  if(enabled)
  {
    if(isNextFrame())
    {
      for(int16_t i = 0; i < (endX - startX); i++)
      {
        for(int16_t j = 0; j < (endY - startY); j++)
        {
          uint8_t color = (plasma[i][j] + paletteShift) % 256;

          layer->drawPixel(startX + i, startY + j, palette[color]);
        }
      }

      paletteShift++;

      resetTimer();

      return true;
    }
  }

  return false;
}

