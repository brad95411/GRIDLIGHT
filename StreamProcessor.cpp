#include "StreamProcessor.h"

void StreamProcessor::updateStream(void)
{
  if(stream->available())
  {
    if(GRIDLIGHTDEBUG)
    {
      stream->println(F("ALERT(STREAM PROCESSOR):DATA DISCOVERED"));
    }
    
    stream->readStringUntil('~').toCharArray(temp, INBOUNDSTREAMBUFFERSIZE);

    if(GRIDLIGHTDEBUG)
    {
      stream->println(F("ALERT(STREAM PROCESSOR):DIVIDING DATA"));
      stream->println(temp);
    }

    char* pch = strtok(temp, ":");

    uint8_t i;

    for(i = 0; pch != NULL; i++)
    {
      event->dataArray[i] = pch;
      pch = strtok(NULL, ":");
    }

    event->arrayLength = i;
    event->handled = false;

    if(GRIDLIGHTDEBUG)
    {
      stream->println(F("ALERT(STREAM PROCESSOR):PROCESSING LISTENERS"));

      for(uint8_t i = 0; i < event->arrayLength; i++)
      {
        stream->print(F("ALERT(STREAM PROCESSOR):DATA ARRAY ELEMENT: "));
        stream->println(event->dataArray[i]);
      }
    }

    for(uint8_t i = 0; i < MAXLISTENERS; i++)
    {
      if(GRIDLIGHTDEBUG)
      {
        stream->print(F("ALERT(STREAM PROCESSOR):IS LISTENER ID "));
        stream->print(i);
        stream->print(F(" NULL"));
        stream->println(listeners[i] == NULL ? F("YES") : F("NO"));
      }
      
      if(listeners[i] != NULL)
      {
        if(!event->handled)
        {
          listeners[i]->processEvent(event);
        }
        else
        {
          break;
        }
      }
    }

    if(GRIDLIGHTDEBUG)
    {
      stream->println(F("ALERT(STREAM PROCESSOR):PROCESSING COMPLETE"));
    }
  }
}

bool StreamProcessor::addListener(IStreamListener* listener)
{
  for(uint8_t i = 0; i < MAXLISTENERS; i++)
  {
    if(listeners[i] == NULL)
    {
      listeners[i] = listener;
      return true;
    }
  }

  return false;
}

IStreamListener* StreamProcessor::removeAtIndex(uint8_t index)
{
  IStreamListener* listTemp;

  listTemp = listeners[index];

  listeners[index] = NULL;

  return listTemp;
}

