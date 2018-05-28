#include "TimeTextProvider.h"

char* TimeTextProvider::getCurrentText()
{
  memset(stringMemory, 0, sizeof(stringMemory));
  memset(conversionArray, 0, sizeof(conversionArray));
   
  if(type == kDateTimeComplex)
  {
    strcat(stringMemory, dayStr(weekday()));
    strcat(stringMemory, ", ");
    
    strcat(stringMemory, monthStr(month()));
    strcat(stringMemory, " ");

    sprintf(conversionArray, "%d", day());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, ", ");

    sprintf(conversionArray, "%d", year());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, " ");

    sprintf(conversionArray, "%d", hour());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, ":");

    uint8_t minuteTemp = minute();

    if(minuteTemp < 10)
    {
      strcat(stringMemory, "0");
    }

    sprintf(conversionArray, "%d", minuteTemp);
    strcat(stringMemory, conversionArray);
  }
  else if(type == kDateTimeBasic)
  {
    sprintf(conversionArray, "%d", month());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, "/");

    sprintf(conversionArray, "%d", day());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, "/");

    sprintf(conversionArray, "%d", year());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, " ");

    sprintf(conversionArray, "%d", hour());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, ":");

    uint8_t minuteTemp = minute();

    if(minuteTemp < 10)
    {
      strcat(stringMemory, "0");
    }

    sprintf(conversionArray, "%d", minuteTemp);
    strcat(stringMemory, conversionArray);
  }
  else if(type == kDateOnly)
  {
    sprintf(conversionArray, "%d", month());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, "/");

    sprintf(conversionArray, "%d", day());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, "/");

    sprintf(conversionArray, "%d", year());
    strcat(stringMemory, conversionArray);
  }
  else if(type == kTimeOnly)
  {
    sprintf(conversionArray, "%d", hour());
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, ":");
    
    uint8_t minuteTemp = minute();
    uint8_t secondTemp = second();

    if(minuteTemp < 10)
    {
      strcat(stringMemory, "0");
    }

    sprintf(conversionArray, "%d", minuteTemp);
    strcat(stringMemory, conversionArray);
    strcat(stringMemory, ":");

    if(secondTemp < 10)
    {
      strcat(stringMemory, "0");
    }

    sprintf(conversionArray, "%d", secondTemp);
    strcat(stringMemory, conversionArray);
  }
  
  return stringMemory;
}

dateTimeTypes TimeTextProvider::ordinalToDateTimeType(uint8_t ordinal)
{
  switch(ordinal)
  {
    case 0:
      return kDateTimeComplex;
    case 1:
      return kDateTimeBasic;
    case 2:
      return kDateOnly;
    case 3:
    default:
      return kTimeOnly;
  }
}

String TimeTextProvider::dateTimeTypeOrdinalToHumanReadableName(uint8_t ordinal)
{
  switch(ordinal)
  {
    case 0:
      return "Date Time Complex";
    case 1:
      return "Date Time Basic";
    case 2:
      return "Date Only";
    case 3:
    default:
      return "Time Only";
  }
}

