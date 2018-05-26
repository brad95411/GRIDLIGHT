#ifndef DRAWINGANIMATIONSSTREAMLISTENER_H
#define DRAWINGANIMATIONSSTREAMLISTENER_H

#include "IStreamListener.h"
#include "Animation2D.h"
#include "Alternate2D.h"
#include "Collision2D.h"
#include "ColorRandomizer2D.h"
#include "CycleLight2D.h"
#include "Fireworks2D.h"
#include "FluidColor2D.h"
#include "Plasma2D.h"
#include "Ricochet2D.h"
#include "TripCycling2D.h"
#include "GlobalSettings.h"
#include <SmartMatrix3.h>
#include <Print.h>

class DrawingAnimationsStreamListener : public IStreamListener
{
  public:
    DrawingAnimationsStreamListener(Print* _stream, SMLayerBackground<rgb24, 0>* _layer, 
      uint16_t _maxAnimations) : maxAnimations(_maxAnimations), stream(_stream), 
      layer(_layer), animations(new Animation2D*[_maxAnimations]) 
      {for(uint16_t i = 0; i < _maxAnimations; i++) {animations[i] = NULL;}}
    ~DrawingAnimationsStreamListener() {}

    void processEvent(StreamEvent* event);

    bool updateAllAnimations();

  private:
    uint16_t
      maxAnimations,
      getAnimationPosByID(uint16_t id),
      getNextAniPos();
    Print*
      stream;
    SMLayerBackground<rgb24, 0>*
      layer;
    Animation2D**
      animations;
};

#endif
