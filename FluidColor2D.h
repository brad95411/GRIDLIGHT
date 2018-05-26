#ifndef FLUIDCOLOR2D_H
#define FLUIDCOLOR2D_H

#include "Animation2D.h"
#include "LEDUtils.h"
#include "GlobalSettings.h"

enum fluidTypes {
  kPixelByPixel,
  kVerticalScroll,
  kHorizontalScroll
};

class FluidColor2D : public Animation2D
{
  public:
    FluidColor2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY, 
      int16_t _endX, int16_t _endY, float _colorResolution, fluidTypes _type, long _updateTime);
    ~FluidColor2D() { delete[] colors; }

    void start(void);
    void stop(void);
    bool update(void);

    static fluidTypes ordinalToFluidType(uint8_t ordinal);
    
    static String ordinalToHumanReadableName(uint8_t ordinal);
    
    static uint8_t getTotalEnumeratedTypes() { return 3; }

  private:
    rgb24*
      colors;
    uint16_t
      colorShifter;
    float
      colorResolution;
    fluidTypes
      type;
};

#endif
