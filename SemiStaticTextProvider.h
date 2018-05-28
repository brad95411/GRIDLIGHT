#ifndef SEMISTATICTEXTPROVIDER_H
#define SEMISTATICTEXTPROVIDER_H

#include "ITextProvider.h"

class SemiStaticTextProvider : public ITextProvider {
  public:
    SemiStaticTextProvider(char* text) { strcpy(stringMemory, text); }
    ~SemiStaticTextProvider() {}

    void setCurrentText(char* text) { strcpy(stringMemory, text); }
      
};

#endif
