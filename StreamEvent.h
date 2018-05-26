#ifndef STREAMEVENT_H
#define STREAMEVENT_H

#include "GlobalSettings.h"

class StreamEvent
{
  public:
    StreamEvent() : dataArray(new char*[MAXSTRINGSINSPLIT]) {}
  
    char** dataArray;
    uint8_t arrayLength;
    bool handled;
};

#endif

