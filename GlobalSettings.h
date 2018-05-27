#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

//This is done so that standard files are included in .h and .cpp files, because that is
//apparently a thing that does not happen automatically
#include <Arduino.h>

#include <SmartMatrix3.h>

#define GRIDLIGHTDEBUG 1
#define SERIALPORT Serial
#define MAXSTRINGSINSPLIT 25
#define INBOUNDSTREAMBUFFERSIZE 300
#define MAXLISTENERS 10
#define DEFAULTROTATION rotation180
#define TOTALMAXANIMATIONS 10
#define MAXSCROLLINGLAYERS 3
#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24

const uint8_t kMatrixWidth = 96;        // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 64;       // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 36;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t kMatrixOptions = SMARTMATRIX_OPTIONS_BOTTOM_TO_TOP_STACKING;      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

#endif
