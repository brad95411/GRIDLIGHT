#ifndef TIMETEXTPROVIDER_H
#define TIMETEXTPROVIDER_H

#include "ITextProvider.h"
#include <TimeLib.h>
#include <Arduino.h>

enum dateTimeTypes {
  kDateTimeComplex,
  kDateTimeBasic,
  kDateOnly,
  kTimeOnly
};

class TimeTextProvider : public ITextProvider {
  public:
    TimeTextProvider(dateTimeTypes _type) : type(_type), conversionArray(new char[5]) {}
    ~TimeTextProvider() {}

    void setDateTimeType(dateTimeTypes _type) { type = _type; }

    dateTimeTypes getDateTimeType(void) { return type; }

    char* getCurrentText();

    static dateTimeTypes ordinalToDateTimeType(uint8_t ordinal);

    static String dateTimeTypeOrdinalToHumanReadableName(uint8_t ordinal);

    static uint8_t getTotalDateTimeTypes() { return 4; }

  private:
    dateTimeTypes
      type;
    char*
      conversionArray;
};

#endif
