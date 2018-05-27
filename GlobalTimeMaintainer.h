#ifndef GLOBALTIMEMAINTAINER_H
#define GLOBALTIMEMAINTAINER_H

#include <TimeLib.h>

class GlobalTimeMaintainer {
  public:
    static time_t getTeensy3Time() { return Teensy3Clock.get(); }
};

#endif
