#include "ScrollingText2D.h"

ScrollingText2D::ScrollingText2D(SMLayerScrolling<rgb24, 0>& _scrollingLayer, ITextProvider* _provider,
ScrollMode _mode, rgb24 newColor, fontChoices newFont, int _upperOffset, 
int _leftOffset, bool _shouldUpdate, long _updateTime) : provider(_provider), shouldUpdate(_shouldUpdate), mode(_mode)
{
  scrollingLayer = &_scrollingLayer;

  scrollingLayer->setMode(mode);
  scrollingLayer->setColor(newColor);
  scrollingLayer->setFont(newFont);
  scrollingLayer->setOffsetFromTop(_upperOffset);
  scrollingLayer->setStartOffsetFromLeft(_leftOffset);

  updateTime = _updateTime;

  enabled = false;
}

void ScrollingText2D::start(void)
{
  scrollingLayer->start(provider->getCurrentText(), shouldUpdate ? 1 : -1);
  timer = 0;
  enabled = true;
}

void ScrollingText2D::stop(void)
{
  scrollingLayer->stop();
  enabled = false;
}

bool ScrollingText2D::update(void)
{
  if(enabled)
  {
    if(updateTime != 0)
    {
      if(isNextFrame())
      {
        if(shouldUpdate && (!scrollingLayer->getStatus() || mode == stopped || mode == off))
        {
          scrollingLayer->start(provider->getCurrentText(), 1);
        }
        
        resetTimer();
      }
    }
  }

  return false;
}

void ScrollingText2D::setScrollingMode(ScrollMode mode)
{
  scrollingLayer->setMode(mode);
}

void ScrollingText2D::setDrawColor(rgb24 drawColor)
{
  scrollingLayer->setColor(drawColor);
}

void ScrollingText2D::setDrawFont(fontChoices newFont)
{
  scrollingLayer->setFont(newFont);
}

void ScrollingText2D::setScrollOffsets(int topOffset, int leftOffset)
{
  scrollingLayer->setOffsetFromTop(topOffset);
  scrollingLayer->setStartOffsetFromLeft(leftOffset);
}

ScrollMode ScrollingText2D::ordinalToScrollMode(uint8_t ordinal)
{
  switch(ordinal)
  {
    case 0:
      return wrapForward;
    case 1:
      return bounceForward;
    case 2: 
      return bounceReverse;
    case 3:
    default:
      return stopped;
    case 4:
      return off;
    case 5:
      return wrapForwardFromLeft;
  }
}

fontChoices ScrollingText2D::ordinalToFontChoice(uint8_t ordinal)
{
  switch(ordinal)
  {
    case 0:
    default:
      return font3x5;
    case 1:
      return font5x7;
    case 2:
      return font6x10;
    case 3:
      return font8x13;
    case 4:
      return gohufont11;
    case 5:
      return gohufont11b;
  }
}

String ScrollingText2D::scrollModeOrdinalToHumanReadableName(uint8_t ordinal)
{
  switch(ordinal)
  {
    case 0:
      return "Wrap Forward";
    case 1:
      return "Bounce Forward";
    case 2:
      return "Bounce Reverse";
    case 3:
    default:
      return "Stopped";
    case 4:
      return "Off";
    case 5:
      return "Wrap Forward From Left";
  }
}

String ScrollingText2D::fontChoiceOrdinalToHumanReadableName(uint8_t ordinal)
{
  switch(ordinal)
  {
    case 0:
    default:
      return "Apple Font 3x5";
    case 1:
      return "Apple Font 5x7";
    case 2:
      return "Apple Font 6x10";
    case 3:
      return "Apple Font 8x13";
    case 4:
      return "Gohu Font 6x11";
    case 5:
      return "Gohu Font 6x11 Version B";
  }
}

