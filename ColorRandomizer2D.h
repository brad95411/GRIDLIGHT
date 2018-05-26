#ifndef COLORRANDOMIZER2D_H
#define COLORRANDOMIZER2D_H

#include "Animation2D.h"
#include "LEDUtils.h"

#define DEFAULT_FADER 64

class ColorRandomizer2D : public Animation2D
{
  public:
    ColorRandomizer2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY,
      int16_t _endX, int16_t _endY, rgb24* _colors, uint8_t _numColors, bool _fade, long _updateTime);
    ~ColorRandomizer2D() { free(fadingValues); }

    void start(void);
    void stop(void);
    bool update(void);

    void setFade(bool _fade) { fade = _fade; }
    bool getFade(void) { return fade; }
    void setFadeScale(uint8_t _scale) { scale = _scale; }
    uint8_t getFadeScale(void) { return scale; }

    private:
      rgb24
        *colors,
        *fadingValues;
      int16_t
        colorRandomizerInt;
      uint8_t
        scale,
        numColors;
      bool
        isFading,
        fade;
};

#endif

