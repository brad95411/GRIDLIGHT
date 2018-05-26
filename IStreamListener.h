#ifndef ISTREAMLISTENER_H
#define ISTREAMLISTENER_H

#include "StreamEvent.h"

class IStreamListener
{
  public:
    virtual void processEvent(StreamEvent* event) = 0;
};

#endif

