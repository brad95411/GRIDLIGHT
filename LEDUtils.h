#ifndef LEDUTILS_H
#define LEDUTILS_H

#include "GlobalSettings.h"

#include <SmartMatrix3.h>

class LEDUtils
{
  public:
    static void
      clearSection(SMLayerBackground<rgb24, 0>* layer, int16_t startX, int16_t startY, int16_t endX, int16_t endY),
      setAll(SMLayerBackground<rgb24, 0>* layer, int16_t startX, int16_t startY, int16_t endX, int16_t endY, rgb24 color),
      splitColor(rgb24 color, uint8_t* rgb),
      createColor(uint32_t color, rgb24* rgb),
      rgbToHSV(rgb24 rgb, float* hsv),
      hsvToRGB(float* hsv, rgb24* rgb);
    static uint8_t
      split(String** strings, String s, char bpc);
};

#endif

