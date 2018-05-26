#ifndef CYCLELIGHT2D_H
#define CYCLELIGHT2D_H

#include "Animation2D.h"
#include "LEDUtils.h"

class CycleLight2D : public Animation2D
{
  public:
    CycleLight2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY, int16_t _endX, 
      int16_t _endY, bool _isHorizontalScan, rgb24 _color1, rgb24 _color2, long _updateTime);
    ~CycleLight2D() {}
    void start(void);
    void stop(void);
    bool update(void);

    void setHorizontalScan(bool _isHorizontalScan) { isHorizontalScan = _isHorizontalScan; }

    bool getHorizontalScan(void) { return isHorizontalScan; }

    private:
      int16_t
        cycleLightInt;
      rgb24
        color1,
        color2;
      bool
        cycleLightBool,
        isHorizontalScan;
};

#endif
