#include "LEDUtils.h"

void LEDUtils::clearSection(SMLayerBackground<rgb24, 0>* layer, int16_t startX, int16_t startY, int16_t endX, int16_t endY)
{
  LEDUtils::setAll(layer, startX, startY, endX, endY, {0, 0, 0});
}

void LEDUtils::setAll(SMLayerBackground<rgb24, 0>* layer, int16_t startX, int16_t startY, int16_t endX, int16_t endY, rgb24 color)
{
  layer->fillRectangle(startX, startY, endX - 1, endY - 1, color, color);
}

void LEDUtils::splitColor(rgb24 color, uint8_t* rgb)
{
  rgb[0] = color.red;
  rgb[1] = color.green;
  rgb[2] = color.blue;
}

void LEDUtils::createColor(uint32_t color, rgb24* rgb)
{
  rgb->red = (uint8_t)(color >> 16);
  rgb->green = (uint8_t)(color >> 8);
  rgb->blue = (uint8_t)(color >> 0);
}

void LEDUtils::rgbToHSV(rgb24 rgb, float* hsv)
{
  float r = (float)rgb.red/255;
  float g = (float)rgb.green/255;
  float b = (float)rgb.blue/255;

  float smallest = min(r, g);
  smallest = min(smallest, b);

  float largest = max(r, g);
  largest = max(largest, b);

  hsv[2] = largest;

  float delta = largest - smallest;

  if(largest != 0)
  {
    hsv[1] = delta/largest;
  }
  else
  {
    hsv[1] = 0;
    hsv[0] = -1;
    return;
  }

  if(r == largest)
  {
    hsv[0] = (g - b)/delta;
  }
  else if(g == largest)
  {
    hsv[0] = 2 + (b - r)/delta;
  }
  else
  {
    hsv[0] = 4 + (r - g)/delta;
  }

  hsv[0] = hsv[0] * 60;

  if(hsv[0] < 0)
  {
    hsv[0] = hsv[0] + 360;
  }
}

void LEDUtils::hsvToRGB(float* hsv, rgb24* rgb)
{
  int i;
  float f, p, q, t;

  if(hsv[1] == 0)
  {
    rgb->red = rgb->green = rgb->blue = hsv[2] * 255;
    return;
  }

  float hTemp = hsv[0] / 60;
  i = floor(hTemp);

  f = hTemp - i;
  p = hsv[2] * (1 - hsv[1]);
  q = hsv[2] * (1 - hsv[1] * f);
  t = hsv[2] * (1 - hsv[1] * (1 - f));

  switch(i)
  {
    case 0:
      rgb->red = hsv[2] * 255;
      rgb->green = t * 255;
      rgb->blue = p * 255;
      break;
    case 1:
      rgb->red = q * 255;
      rgb->green = hsv[2] * 255;
      rgb->blue = p * 255;
      break;
    case 2:
      rgb->red = p * 255;
      rgb->green = hsv[2] * 255;
      rgb->blue = t * 255;
      break;
    case 3:
      rgb->red = p * 255;
      rgb->green = q * 255;
      rgb->blue = hsv[2] * 255;
      break;
    case 4:
      rgb->red = t * 255;
      rgb->green = p * 255;
      rgb->blue = hsv[2] * 255;
      break;
    case 5:
      rgb->red = hsv[2] * 255;
      rgb->green = p * 255;
      rgb->blue = q * 255;
      break;
  }
}

/*
 * Designed to split a string into an array based on a particular Break-Point Character (bpc). It returns the number of elements
 * placed into the array
 */
uint8_t LEDUtils::split(String** strings, String s, char bpc)
{
  uint8_t index = 0;
  int val;

  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(LEDUTILS):BEGINNING SPLITTING PROCESS"));
  }
    
  while(true)
  {
    val = s.indexOf(String(bpc));
    if(val == -1)
    {
      if(GRIDLIGHTDEBUG)
      {
        SERIALPORT.println(F("ALERT(LEDUTILS):LAST PROCESS"));
      }
      
      strings[index] = &s;
      index++;
      break;
    }
    else
    {
      if(GRIDLIGHTDEBUG)
      {
        SERIALPORT.println(F("ALERT(LEDUTILS):PROCESSING REMAINING DATA"));
        SERIALPORT.println(s);
      }
      
      strings[index] = new String(s.substring(0, val));
      index++;
      s = s.substring(val + 1, s.length());
    }
  }

  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(LEDUTILS):SPLIT FINISHED PROCESSING"));
  }

  return index;
}

