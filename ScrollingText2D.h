#ifndef SCROLLINGTEXT2D_H
#define SCROLLINGTEXT2D_H

#include "Animation2D.h"
#include "LEDUtils.h"
#include "ITextProvider.h"

class ScrollingText2D : public Animation2D
{
  public:
    ScrollingText2D(SMLayerScrolling<rgb24, 0>& _scrollingLayer, ITextProvider* _provider, 
          ScrollMode _mode, rgb24 newColor, fontChoices newFont, 
          int _upperOffset, int _leftOffset, bool _shouldUpdate, long _updateTime);
    ~ScrollingText2D() {}

    bool update(void);
    void start(void);
    void stop(void);

    void setScrollingMode(ScrollMode mode);
    void setDrawColor(rgb24 drawColor);
    void setDrawFont(fontChoices newFont);
    void setScrollOffsets(int topOffset, int leftOffset);

    static ScrollMode ordinalToScrollMode(uint8_t ordinal);

    static fontChoices ordinalToFontChoice(uint8_t ordinal);

    static String scrollModeOrdinalToHumanReadableName(uint8_t ordinal);

    static String fontChoiceOrdinalToHumanReadableName(uint8_t ordinal);

    static uint8_t getTotalScrollModeTypes() { return 6; }

    static uint8_t getTotalFontChoiceTypes() { return 6; }

    private:
      ITextProvider*
        provider;
      bool
        shouldUpdate;
      ScrollMode
        mode;
};

#endif
