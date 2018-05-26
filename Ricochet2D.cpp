#include "Ricochet2D.h"

Ricochet2D::Ricochet2D(SMLayerBackground<rgb24, 0>* _layer, uint16_t _refNum, int16_t _startX,
  int16_t _startY, int16_t _endX, int16_t _endY, uint16_t _numBalls, rgb24* _colors,
  uint8_t _numColors, long _updateTime) : colors(new rgb24[_numColors]), numColors(_numColors),
  numBalls(_numBalls), balls(new RicochetHelper*[_numBalls])
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

  for(uint16_t i = 0; i < numBalls; i++)
  {
    randomSeed(random(0, 10000000));
    balls[i] = new RicochetHelper(random(startX + 1, endX - 1), random(startY + 1, endY - 1), 
      startX, startY, endX, endY, colors[random(0, numColors)]);
  }
}

void Ricochet2D::start(void)
{
  timer = 0;
  enabled = true;
}

void Ricochet2D::stop(void)
{
  enabled = false;
}

bool Ricochet2D::update(void)
{
  if(enabled)
  {
    if(isNextFrame())
    {
      LEDUtils::clearSection(layer, startX, startY, endX, endY);

      for(uint16_t i = 0; i < numBalls; i++)
      {
        balls[i]->updatePositions();

        layer->drawPixel(balls[i]->getCurrentXPos(), balls[i]->getCurrentYPos(), 
          balls[i]->getCurrentColor());
      }

      resetTimer();

      return true;
    }
  }
  return false;
}

