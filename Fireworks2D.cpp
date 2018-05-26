#include "Fireworks2D.h"

Fireworks2D::Fireworks2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX,
  int16_t _startY, int16_t _endX, int16_t _endY, uint8_t _maxFireworks, uint16_t _maxRadius, 
  rgb24* _colors, uint8_t _numColors, long _updateTime) : colors(new rgb24[_numColors]), 
  numColors(_numColors), fireworks(new Firework_t[_maxFireworks]), maxFireworks(_maxFireworks),
  maxRadius(_maxRadius)
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
}

void Fireworks2D::start(void)
{
  for(uint8_t i = 0; i < maxFireworks; i++)
  {
    fireworks[i].isActive = false;
  }

  uint8_t third = maxFireworks/6;

  for(uint8_t i = 0; i < third; i++)
  {
    randomSeed(random(0, 100000000));
    
    fireworks[i].radius = random(1, maxRadius + 1);
    fireworks[i].currentRadius = 1;
    fireworks[i].xPos = random(startX + fireworks[i].radius, endX - fireworks[i].radius);
    fireworks[i].yPos = endY; //startY
    fireworks[i].yMaxHeight = random(startY + fireworks[i].radius, endY - fireworks[i].radius); //random(startY + fireworks[i].radius, endY - fireworks[i].radius); 
    fireworks[i].color = colors[random(0, numColors)];
    fireworks[i].isActive = true;
  }

  timer = 0;
  enabled = true;
}

void Fireworks2D::stop(void)
{
  enabled = false;
}

bool Fireworks2D::update(void)
{
  if(enabled)
  {
    if(isNextFrame())
    {
      LEDUtils::clearSection(layer, startX, startY, endX, endY);
  
      uint8_t totalInactive = 0;
    
      for(uint8_t i = 0; i < maxFireworks; i++)
      {
        if(!fireworks[i].isActive)
        {
          totalInactive++;
        }
      }
    
      for(uint8_t i = 0; i < totalInactive; i++)
      {
        randomSeed(random(0, 100000000));
    
        if(random(0, 1000) > 500)
        {
          for(uint8_t j = 0; j < maxFireworks; j++)
          {
            if(!fireworks[j].isActive)
            {
              fireworks[j].radius = random(1, maxRadius + 1);
              fireworks[j].currentRadius = 1;
              fireworks[j].xPos = random(startX + fireworks[j].radius, endX - fireworks[j].radius);
              fireworks[j].yPos = endY; //startY;
              fireworks[j].yMaxHeight = random(startY + fireworks[j].radius, endY - fireworks[j].radius); //random(startY + fireworks[i].radius, endY - fireworks[i].radius); 
              fireworks[j].color = colors[random(0, numColors)];
              fireworks[j].isActive = true;
              break;
            }
          }
        }
      }
    
      for(uint8_t i = 0; i < maxFireworks; i++)
      {
        if(fireworks[i].isActive)
        {
          if(fireworks[i].yMaxHeight == fireworks[i].yPos && fireworks[i].currentRadius == fireworks[i].radius)
          {
            fireworks[i].isActive = false;
          }
          else if(fireworks[i].yMaxHeight == fireworks[i].yPos && fireworks[i].currentRadius < fireworks[i].radius)
          {
            layer->drawCircle(fireworks[i].xPos, fireworks[i].yPos, fireworks[i].currentRadius, fireworks[i].color);
            fireworks[i].currentRadius++;
          }
          else if(fireworks[i].yPos > fireworks[i].yMaxHeight)
          {
            layer->drawPixel(fireworks[i].xPos, fireworks[i].yPos, fireworks[i].color);
            fireworks[i].yPos--;
          }
        }
      }

      resetTimer();

      return true;
    }
  }

  return false;
}

