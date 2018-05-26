#ifndef FIREWORKS2D_H
#define FIREWORKS2D_H

#include "Animation2D.h"
#include "LEDUtils.h"

typedef struct _firework_t {
  int16_t xPos;
  int16_t yPos;
  int16_t yMaxHeight;
  uint16_t currentRadius;
  uint16_t radius;
  rgb24 color;
  bool isActive;
} Firework_t;

class Fireworks2D : public Animation2D
{
  public:
    Fireworks2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, 
      int16_t _startY, int16_t _endX, int16_t _endY, uint8_t _maxFireworks, uint16_t _maxRadius,
      rgb24* _colors, uint8_t _numColors, long _updateTime);
    ~Fireworks2D() { delete[] colors; delete[] fireworks; }

    void start(void);
    void stop(void);
    bool update(void);

  private:
    uint8_t
      maxFireworks,
      numColors;
    uint16_t
      maxRadius;
    rgb24*
      colors;
    Firework_t*
      fireworks;
};

#endif
