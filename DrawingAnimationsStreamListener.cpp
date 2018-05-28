#include "DrawingAnimationsStreamListener.h"

//Data Tree
//[0] = processor check
//[1] = processor action (EXIST or NEW)
//[2] = processsor sub action (VARIOUS)
//[3] = refID
//[4]... = extraneous data
void DrawingAnimationsStreamListener::processEvent(StreamEvent* event)
{
  if(GRIDLIGHTDEBUG)
  {
    stream->println(F("ALERT(DRAWING ANIMATIONS):INSIDE DRAWING ANIMATIONS"));
  }
  
  if(strcmp_P(event->dataArray[0], PSTR("BACK")) == 0)
  {
    if(GRIDLIGHTDEBUG)
    {
      stream->println(F("ALERT(DRAWING ANIMATIONS):PROCESSING AS BACK"));
    }
    
    uint16_t animationPos = getAnimationPosByID(atoi(event->dataArray[3]));
    
    if(strcmp_P(event->dataArray[1], PSTR("EXIST")) == 0)
    {
      if(animationPos == 65535)
      {
        stream->print(F("BACK:EXIST:IDNOTFOUND~"));
      }
      else
      {
        if(strcmp_P(event->dataArray[2], PSTR("DLA")) == 0)
        {
          delete animations[animationPos];
          animations[animationPos] = NULL;
          stream->print(F("BACK:EXIST:DLA:OK~"));
        }
        else if(strcmp_P(event->dataArray[2], PSTR("STA")) == 0)
        {
          animations[animationPos]->stop();
          stream->print(F("BACK:EXIST:STA:OK~"));
        }
        else if(strcmp_P(event->dataArray[2], PSTR("RSA")) == 0)
        {
          animations[animationPos]->resume();
          stream->print(F("BACK:EXIST:RSA:OK~"));
        }
      }
    }
    else if(strcmp_P(event->dataArray[1], PSTR("NEW")) == 0)
    {
      if(GRIDLIGHTDEBUG)
      {
        stream->println(F("ALERT(DRAWING ANIMATIONS):PROCESSING AS NEW"));
      }
      
      uint16_t nextPos = getNextAniPos();

      if(GRIDLIGHTDEBUG)
      {
        stream->print(F("ALERT(DRAWING ANIMATIONS):ANIMATION POSITION VALIDATION VALUE: "));
        stream->println(animationPos);
        stream->print(F("ALERT(DRAWING ANIMATIONS):NEXT ANIMATION POSITION IDENTIFIED: "));
        stream->println(nextPos);
      }

      if(nextPos == 65535)
      {
        stream->print(F("BACK:NEW:NOFREESPACE~"));
      }
      else
      {
        if(GRIDLIGHTDEBUG)
        {
          stream->println(F("ALERT(DRAWING ANIMATIONS):FOUND FREE SPACE"));
        }
        
        if(animationPos != 65535)
        {
          stream->print(F("BACK:NEW:IDINUSE~"));
        }
        else
        {
          if(GRIDLIGHTDEBUG)
          {
            stream->println(F("ALERT(DRAWING ANIMATIONS):ID SPECIFIED IS AVAILABLE"));
          }
          
          if(strcmp_P(event->dataArray[2], PSTR("ALT")) == 0)
          {
            rgb24 colors[event->arrayLength - 10];

            for(uint8_t i = 10; i < event->arrayLength; i++)
            {
              LEDUtils::createColor(atoi(event->dataArray[i]), &colors[i-10]);
            }

            animations[nextPos] = new Alternate2D(layer, atoi(event->dataArray[3]), atoi(event->dataArray[4]),
              atoi(event->dataArray[5]), atoi(event->dataArray[6]), atoi(event->dataArray[7]),
              atoi(event->dataArray[8]), colors, event->arrayLength - 10, atoi(event->dataArray[9]));
            animations[nextPos]->start();
          }
          else if(strcmp_P(event->dataArray[2], PSTR("COL")) == 0)
          {
            rgb24 color1;
            rgb24 color2;

            LEDUtils::createColor(atoi(event->dataArray[10]), &color1);
            LEDUtils::createColor(atoi(event->dataArray[11]), &color2);
            
            animations[nextPos] = new Collision2D(layer, atoi(event->dataArray[3]), 
              atoi(event->dataArray[4]), atoi(event->dataArray[5]), atoi(event->dataArray[6]),
              atoi(event->dataArray[7]), atoi(event->dataArray[8]), color1, color2, 
              atoi(event->dataArray[9]));
            animations[nextPos]->start();
          }
          else if(strcmp_P(event->dataArray[2], PSTR("CRZ")) == 0)
          {
            rgb24 colors[event->arrayLength - 10];

            for(uint8_t i = 10; i < event->arrayLength; i++)
            {
              LEDUtils::createColor(atoi(event->dataArray[i]), &colors[i-10]);
            }

            animations[nextPos] = new ColorRandomizer2D(layer, atoi(event->dataArray[3]),
              atoi(event->dataArray[4]), atoi(event->dataArray[5]), atoi(event->dataArray[6]),
              atoi(event->dataArray[7]), colors, event->arrayLength - 10, 
              atoi(event->dataArray[8]), atoi(event->dataArray[9]));
            animations[nextPos]->start();
          }
          else if(strcmp_P(event->dataArray[2], PSTR("CLT")) == 0)
          {
            rgb24 color1;
            rgb24 color2;

            LEDUtils::createColor(atoi(event->dataArray[10]), &color1);
            LEDUtils::createColor(atoi(event->dataArray[11]), &color2);

            animations[nextPos] = new CycleLight2D(layer, atoi(event->dataArray[3]),
              atoi(event->dataArray[4]), atoi(event->dataArray[5]), atoi(event->dataArray[6]),
              atoi(event->dataArray[7]), atoi(event->dataArray[8]), color1, color2, 
              atoi(event->dataArray[9]));
            animations[nextPos]->start();
          }
          else if(strcmp_P(event->dataArray[2], PSTR("FKS")) == 0)
          {
            rgb24 colors[event->arrayLength - 11];

            for(uint8_t i = 11; i < event->arrayLength; i++)
            {
              LEDUtils::createColor(atoi(event->dataArray[i]), &colors[i-11]);
            }

            animations[nextPos] = new Fireworks2D(layer, atoi(event->dataArray[3]),
              atoi(event->dataArray[4]), atoi(event->dataArray[5]), atoi(event->dataArray[6]),
              atoi(event->dataArray[7]), atoi(event->dataArray[8]), atoi(event->dataArray[9]),
              colors, event->arrayLength - 11, atoi(event->dataArray[10]));
            animations[nextPos]->start();
          }
          else if(strcmp_P(event->dataArray[2], PSTR("FLC")) == 0)
          {
            if(event->arrayLength == 3)
            {
              for(uint8_t i = 0; i < FluidColor2D::getTotalEnumeratedTypes(); i++)
              {
                stream->print(F("BACK:NEW:FLC:PART:"));
                stream->print(FluidColor2D::ordinalToHumanReadableName(i));
                stream->print(F("~"));
              }

              stream->print(F("BACK:NEW:FLC:DONE~"));
            }
            else
            {
              animations[nextPos] = new FluidColor2D(layer, atoi(event->dataArray[3]),
                atoi(event->dataArray[4]), atoi(event->dataArray[5]), atoi(event->dataArray[6]),
                atoi(event->dataArray[7]), atof(event->dataArray[8]), FluidColor2D::ordinalToFluidType(atoi(event->dataArray[9])),
                atoi(event->dataArray[10]));
              animations[nextPos]->start();
            }
          }
          else if(strcmp_P(event->dataArray[2], PSTR("PLA")) == 0)
          {
            if(GRIDLIGHTDEBUG)
            {
              stream->println(F("ALERT(DRAWING ANIMATIONS):CREATE PLASMA ANIMATION"));
            }
            
            animations[nextPos] = new Plasma2D(layer, atoi(event->dataArray[3]),
              atoi(event->dataArray[4]), atoi(event->dataArray[5]), atoi(event->dataArray[6]),
              atoi(event->dataArray[7]), atoi(event->dataArray[8]));
            animations[nextPos]->start();

            if(GRIDLIGHTDEBUG)
            {
              stream->println(F("ALERT(DRAWING ANIMATIONS):PLASMA ANIMATION GENERATED"));
            }
          }
          else if(strcmp_P(event->dataArray[2], PSTR("RCO")) == 0)
          {
            rgb24 colors[event->arrayLength - 10];

            for(uint8_t i = 10; i < event->arrayLength; i++)
            {
              LEDUtils::createColor(atoi(event->dataArray[i]), &colors[i-10]);
            }

            animations[nextPos] = new Ricochet2D(layer, atoi(event->dataArray[3]),
              atoi(event->dataArray[4]), atoi(event->dataArray[5]), atoi(event->dataArray[6]),
              atoi(event->dataArray[7]), atoi(event->dataArray[8]), colors, event->arrayLength-10,
              atoi(event->dataArray[9]));
            animations[nextPos]->start();
          }
          else if(strcmp_P(event->dataArray[2], PSTR("TCL")) == 0)
          {
            rgb24 color1;
            rgb24 color2;

            LEDUtils::createColor(atoi(event->dataArray[11]), &color1);
            LEDUtils::createColor(atoi(event->dataArray[12]), &color2);

            animations[nextPos] = new TripCycling2D(layer, atoi(event->dataArray[3]), 
              atoi(event->dataArray[4]), atoi(event->dataArray[5]), atoi(event->dataArray[6]),
              atoi(event->dataArray[7]), atoi(event->dataArray[8]), atoi(event->dataArray[9]),
              color1, color2, atoi(event->dataArray[10]));
            animations[nextPos]->start();
          }
          else if(strcmp_P(event->dataArray[2], PSTR("TEXT")) == 0)
          {
            if(event->arrayLength == 4)
            {
              if(strcmp_P(event->dataArray[3], PSTR("SMO")) == 0)
              {
                for(uint8_t i = 0; i < ScrollingText2D::getTotalScrollModeTypes(); i++)
                {
                  stream->print(F("BACK:NEW:TEXT:SMO:PART:"));
                  stream->print(ScrollingText2D::scrollModeOrdinalToHumanReadableName(i));
                  stream->print(F("~"));
                }

                stream->print(F("BACK:NEW:TEXT:SMO:DONE~"));
              }
              else if(strcmp_P(event->dataArray[3], PSTR("FCO")) == 0)
              {
                for(uint8_t i = 0; i < ScrollingText2D::getTotalFontChoiceTypes(); i++)
                {
                  stream->print(F("BACK:NEW:TEXT:FCO:PART:"));
                  stream->print(ScrollingText2D::fontChoiceOrdinalToHumanReadableName(i));
                  stream->print(F("~"));
                }

                stream->print(F("BACK:NEW:TEXT:FCO:DONE~"));
              }
            }
            else
            {
              int8_t nextAnimationID = getAvailableScrollingLayerID();

              if(nextAnimationID == -1)
              {
                stream->print(F("BACK:NEW:TEXT:NO AVAILABLE SCROLLING TEXT LAYERS AT THIS TIME"));
              }
              else
              {
                if(strcmp_P(event->dataArray[3], PSTR("SST")) == 0)
                {
                  rgb24 textColor;

                  LEDUtils::createColor(atoi(event->dataArray[5]), &textColor);
                  
                  animations[nextPos] = new ScrollingText2D(*scrollingLayers[nextAnimationID], 
                  new SemiStaticTextProvider(event->dataArray[11]), 
                  ScrollingText2D::ordinalToScrollMode(atoi(event->dataArray[4])),
                  textColor, ScrollingText2D::ordinalToFontChoice(atoi(event->dataArray[6])),
                  atoi(event->dataArray[7]), atoi(event->dataArray[8]),
                  atoi(event->dataArray[9]), atoi(event->dataArray[10]));
                  animations[nextPos]->start();
                }
                else if(strcmp_P(event->dataArray[3], PSTR("TIM")) == 0)
                {
                  if(event->arrayLength == 4)
                  {
                    for(uint8_t i = 0; i < TimeTextProvider::getTotalDateTimeTypes(); i++)
                    {
                      stream->print(F("BACK:NEW:TEXT:TIM:PART:"));
                      stream->print(TimeTextProvider::dateTimeTypeOrdinalToHumanReadableName(i));
                      stream->print(F("~"));
                    }

                    stream->print(F("BACK:NEW:TEXT:TIM:DONE~"));
                  }
                  else
                  {
                    rgb24 textColor;

                    LEDUtils::createColor(atoi(event->dataArray[5]), &textColor);
                  
                    animations[nextPos] = new ScrollingText2D(*scrollingLayers[nextAnimationID], 
                    new TimeTextProvider(TimeTextProvider::ordinalToDateTimeType(atoi(event->dataArray[11]))), 
                    ScrollingText2D::ordinalToScrollMode(atoi(event->dataArray[4])),
                    textColor, ScrollingText2D::ordinalToFontChoice(atoi(event->dataArray[6])),
                    atoi(event->dataArray[7]), atoi(event->dataArray[8]),
                    atoi(event->dataArray[9]), atoi(event->dataArray[10]));
                    animations[nextPos]->start();
                  }
                }
              }
            }
          }
        }
      }
    }

    event->handled = true;
  }
}

bool DrawingAnimationsStreamListener::updateAllAnimations()
{
  bool shouldUpdate = false;

  for(uint16_t i = 0; i < maxAnimations; i++)
  {
    if(animations[i] != NULL)
    {
      shouldUpdate = shouldUpdate || animations[i]->update();
    }
  }

  return shouldUpdate;
}

uint16_t DrawingAnimationsStreamListener::getAnimationPosByID(uint16_t id)
{
  for(uint16_t i = 0; i < maxAnimations; i++)
  {
    if(animations[i]->getRefNum() == id)
    {
      return i;
    }
  }

  return 65535;
}

uint16_t DrawingAnimationsStreamListener::getNextAniPos()
{
  for(uint16_t i = 0; i < maxAnimations; i++)
  {
    if(animations[i] == NULL)
    {
      return i;
    }
  }

  return 65535;
}

int8_t DrawingAnimationsStreamListener::getAvailableScrollingLayerID()
{
  for(uint16_t i = 0; i < MAXSCROLLINGLAYERS; i++)
  {
    if(scrollingLayers[i] != NULL)
    {
      if(scrollingLayers[i]->getStatus() == 0)
      {
        scrollingLayerAvailable[i] = true;
      }
    }
  }

  for(uint16_t i = 0; i < MAXSCROLLINGLAYERS; i++)
  {
    if(scrollingLayerAvailable[i])
    {
      if(scrollingLayers[i] == NULL)
      {
        SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(temporaryLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
        temporaryLayer.setRotation(DEFAULTROTATION);

        scrollingLayers[i] = &temporaryLayer;
      }

      scrollingLayerAvailable[i] = false;
      return i;
    }
  }

  return -1;
}

