#include "StreamProcessor.h"
#include "GlobalSettings.h"
#include "DrawingAnimationsStreamListener.h"

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

StreamProcessor* processor;

DrawingAnimationsStreamListener* daListener;

void setup() {
  SERIALPORT.begin(115200);

  matrix.addLayer(&backgroundLayer);
  matrix.begin();
  matrix.setBrightness(255);
  backgroundLayer.enableColorCorrection(true);
  backgroundLayer.setRotation(DEFAULTROTATION);
  
  processor = new StreamProcessor(&SERIALPORT);

  daListener = new DrawingAnimationsStreamListener(&SERIALPORT, &backgroundLayer, TOTALMAXANIMATIONS);

  if(processor->addListener(daListener) && GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(GRIDLIGHT):DRAWING ANIMATION LISTENER SUPPOSEDLY ADDED"));
  }

  if(GRIDLIGHTDEBUG)
  {
    SERIALPORT.println(F("ALERT(GRIDLIGHT):SETUP COMPLETE"));
  }
}

void loop() {
  processor->updateStream();

  bool shouldUpdate = daListener->updateAllAnimations();

  if(shouldUpdate)
  {
    backgroundLayer.swapBuffers();
  }

  delayMicroseconds(500);
}
