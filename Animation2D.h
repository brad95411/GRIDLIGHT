#ifndef ANIMATION2D_H
#define ANIMATION2D_H

#include <elapsedMillis.h>
#include <SmartMatrix3.h>

class Animation2D
{
  public:
    Animation2D() : layer(NULL), startX(0), startY(0), endX(0), endY(0), updateTime(0), refNum(65535), enabled(false) {}
    virtual ~Animation2D() {}

    virtual bool update() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void resume(void) { enabled = true; }

    void setStartX(int16_t _startX) { startX = _startX; }
    void setStartY(int16_t _startY) { startY = _startY; }
    void setWidth(int16_t _endX) { endX = _endX; }
    void setHeight(int16_t _endY) { endY = _endY; }
    void setUpdateTime(long _updateTime) { updateTime = _updateTime; }
    void resetTimer(void) { timer = 0; }

    int16_t getStartX() { return startX; }
    int16_t getStartY() { return startY; }
    int16_t getWidth() { return endX; }
    int16_t getHeight() { return endY; }

    uint16_t getRefNum() { return refNum; }

    long getUpdateTime() { return updateTime; }

    bool isEnabled() { return enabled; }
    
  protected:
    uint16_t
      refNum;
    int16_t
      startX,
      startY,
      endX,
      endY;
    long
      updateTime;
    bool
      enabled;
    SMLayerBackground<rgb24, 0>*
      layer;
    SMLayerScrolling<rgb24, 0>*
      scrollingLayer;
    elapsedMillis
      timer;
    bool isNextFrame() { return timer > updateTime; }
      
};

#endif

