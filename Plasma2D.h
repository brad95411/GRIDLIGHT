#ifndef PLASMA2D_H
#define PLASMA2D_H

#include "LEDUtils.h"
#include "GlobalSettings.h"
#include "Animation2D.h"

class Plasma2D : public Animation2D
{
  public:
    Plasma2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY, 
      int16_t _endX, int16_t _endY, long _updateTime);
    ~Plasma2D();

    bool update(void);
    void start(void);
    void stop(void);

    private:
      int16_t
        paletteShift;
      rgb24*
        palette;
      uint8_t**
        plasma;
};

#endif
