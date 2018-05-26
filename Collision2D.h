#ifndef COLLISION2D_H
#define COLLISION2D_H

#include "Animation2D.h"
#include "LEDUtils.h"

class Collision2D : public Animation2D
{
  public:
    Collision2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY, 
      int16_t _endX, int16_t _endY, bool _isHorizontalScan, rgb24 _color1, rgb24 _color2, long _updateTime);
    ~Collision2D() {}

    void setHorizontalScan(bool _isHorizontalScan) { isHorizontalScan = _isHorizontalScan; }

    bool getHorizontalScan(void) { return isHorizontalScan; }

    bool update(void);
    void start(void);
    void stop(void);

  private:
    int16_t
      collisionInt;
    rgb24
      color1,
      color2;
    bool
      isHorizontalScan;
    
};

#endif
