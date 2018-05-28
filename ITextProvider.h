#ifndef ITEXTPROVIDER_H
#define ITEXTPROVIDER_H

#define MAXTEXTLENGTH 100

#include <string.h>

class ITextProvider {
  public:
    ITextProvider() : stringMemory(new char[MAXTEXTLENGTH]) {}
    virtual ~ITextProvider() { delete[] stringMemory; }
    virtual char* getCurrentText(void) { return stringMemory; }
  protected:
    char*
      stringMemory;
};

#endif
