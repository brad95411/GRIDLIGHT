#ifndef RICOCHET2D_H
#define RICOCHET2D_H

#include "LEDUtils.h"
#include "Animation2D.h"
#include "RicochetHelper.h"

class Ricochet2D : public Animation2D
{
  public:
    Ricochet2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, 
      int16_t _startY, int16_t _endX, int16_t _endY, uint16_t _numBalls, rgb24* _colors, 
      uint8_t _numColors, long _updateTime);
    ~Ricochet2D() { delete[] colors; delete[] balls; }

    void start(void);
    void stop(void);
    bool update(void);

  private:
    uint16_t
      numBalls;
    rgb24*
      colors;
    uint8_t
      numColors;
    RicochetHelper**
      balls;
};

#endif
