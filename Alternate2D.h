#ifndef ALTERNATE2D_H
#define ALTERNATE2D_H

#include "Animation2D.h"

class Alternate2D : public Animation2D
{
  public:
    Alternate2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY, 
      int16_t _endX, int16_t _endY, bool _isHorizontalScan, rgb24* _colors, uint8_t _numColors, long _updateTime);
    ~Alternate2D() { free(colors); }

    void setHorizontalScan(bool _isHorizontalScan) { isHorizontalScan = _isHorizontalScan; }

    bool getHorizontalScan(void) { return isHorizontalScan; }
    
    void start(void);
    void stop(void);
    bool update(void);

  private:
    uint16_t
      alternateInt;
    rgb24*
      colors;
    uint8_t
      numColors;
    bool 
      isHorizontalScan;
};

#endif
