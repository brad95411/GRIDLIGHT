#include "ColorRandomizer2D.h"

ColorRandomizer2D::ColorRandomizer2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX, int16_t _startY,
  int16_t _endX, int16_t _endY, rgb24* _colors, uint8_t _numColors, bool _fade, long _updateTime) :
  colors(new rgb24[_numColors]), numColors(_numColors), fade(_fade), colorRandomizerInt(0), isFading(false), 
  scale(DEFAULT_FADER), fadingValues(new rgb24[(_endY - _startY) * (_endX - _startX)])
{
  layer = _layer;
  refNum = _refNum;
  startX = _startX;
  startY = _startY;
  endX = _endX;
  endY = _endY;
  updateTime = _updateTime;

  for(uint8_t i = 0; i < numColors; i++)
  {
    colors[i] = _colors[i];
  }

  enabled = false;
}

void ColorRandomizer2D::start(void)
{
  colorRandomizerInt = 0;
  isFading = false;
  //memset(fadingValues, rgb24(0, 0, 0), (endY - startY) * (endX - startX));
  timer = 0;
  enabled = true;
}

void ColorRandomizer2D::stop(void)
{
  enabled = false;
}

bool ColorRandomizer2D::update(void)
{
  if(enabled)
  {
    if(isNextFrame())
    {
      if(fade && isFading) // If we are supposed to be ABLE to fade and we are CURRENTLY supposed to be fading
      {
        rgb24 rgb;
        
        if(colorRandomizerInt == 0) //Setup the fading values for the animation
        {
          for(int16_t i = 0; i < endX - startX; i++)
          {
            for(int16_t j = 0; j < endY - startY; j++)
            {
              rgb = layer->readPixel(startX + i, startY + j);

              uint8_t subVal = ceil((float)rgb.red/scale);
              fadingValues[i * (endX - startX) + j].red = subVal;

              subVal = ceil((float)rgb.green/scale);
              fadingValues[i * (endX - startX) + j].green = subVal;

              subVal = ceil((float)rgb.blue/scale);
              fadingValues[i * (endX - startX) + j].blue = subVal;
            }
          }

          colorRandomizerInt++;
        }
        else if(colorRandomizerInt > 0 && colorRandomizerInt < scale+1) //While the counter is less thanthe scale value + 1
        {
          for(int16_t i = 0; i < endX - startX; i++)
          {
            for(int16_t j = 0; j < endY - startY; j++)
            {
              rgb = layer->readPixel(startX + i, startY + j);

              if(rgb.red == 0)
              {
                //Do nothing!
              }
              else if((int16_t)rgb.red - fadingValues[i * (endX - startX) + j].red < 0)
              {
                rgb.red = 0;
              }
              else
              {
                rgb.red = rgb.red - fadingValues[i * (endX - startX) + j].red;
              }

              if(rgb.green == 0)
              {
                //Do nothing!
              }
              else if((int16_t)rgb.green - fadingValues[i * (endX - startX) + j].green < 0)
              {
                rgb.green = 0;
              }
              else
              {
                rgb.green = rgb.green - fadingValues[i * (endX - startX) + j].green;
              }

              if(rgb.blue == 0)
              {
                //Do nothing!
              }
              else if((int16_t)rgb.blue - fadingValues[i * (endX - startX) + j].blue < 0)
              {
                rgb.blue = 0;
              }
              else
              {
                rgb.blue = rgb.blue - fadingValues[i * (endX - startX) + j].blue;
              }

              layer->drawPixel(startX + i, startY + j, rgb);
            }
          }
          
          colorRandomizerInt++;
        }
        else //If we've faded to black, reset the counter and disable fading
        {
          colorRandomizerInt = 0;
          isFading = false;
        }
      }
      else //If not fading, create a new random "frame" so to speak
      {
        uint8_t rand;

        for(int16_t i = 0; i < (endX - startX); i++)
        {
          for(int16_t j = 0; j < (endY - startY); j++)
          {
            rand = random(0, numColors);

            layer->drawPixel(startX + i, startY + j, colors[rand]);
          }
        }

        //If we supposed to be ABLE to fade...
        if(fade)
        {
          isFading = true; //The set up to be fading
        }
      }
           
      resetTimer();

      return true;
    }
  }
  return false;
}

