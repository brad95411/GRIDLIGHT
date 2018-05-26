#ifndef STREAMPROCESSOR_H
#define STREAMPROCESSOR_H

#include "IStreamListener.h"
#include "GlobalSettings.h"

class StreamProcessor
{
  public:
    StreamProcessor(Stream* _stream) : stream(_stream), 
      listeners(new IStreamListener*[MAXLISTENERS]), temp(new char[INBOUNDSTREAMBUFFERSIZE]),
      event(new StreamEvent()) { for(uint8_t i = 0; i < MAXLISTENERS; i++) {listeners[i] = NULL;}}
    ~StreamProcessor() {}

    void updateStream(void);

    bool addListener(IStreamListener* listener);
    IStreamListener* removeAtIndex(uint8_t index);

  private:
    Stream*
      stream;
    IStreamListener**
      listeners;
    char*
      temp;
    StreamEvent*
      event;
};

#endif
