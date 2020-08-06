//
//  Union Jack
//  Fly the flag and watch it wave in the breeze.
//  August 2020, Charles Goodwin
//

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#include "readFile.h"
#include "xy.h"
FASTLED_USING_NAMESPACE

#define DATA_PIN    12 // pins tested so far on the Feather ESP32: 13, 12, 27, 33, 15, 32, 14, SCL
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 50
//Irregular Matrix fully defined
#define NUM_SHORT_STRIPS 11
#define NUM_LONG_STRIPS 8
#define NUM_LEDS_PER_SHORT_STRIP 13
#define NUM_LEDS_PER_LONG_STRIP 39
#define NUM_TOTAL_STRIPS (NUM_SHORT_STRIPS + NUM_LONG_STRIPS)
#define NUM_LEDS (NUM_LEDS_PER_LONG_STRIP * NUM_LONG_STRIPS) + (NUM_LEDS_PER_SHORT_STRIP * NUM_SHORT_STRIPS)
#define MAX_POWER_MILLIAMPS 10000

//////////////////////////////////////////////////////////////////////////

CRGB leds[NUM_LEDS];

void setup() {
  delay( 3000); // 3 second delay for boot recovery, and a moment of silence
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection( TypicalLEDStrip );
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);
  FastLED.setBrightness(BRIGHTNESS );
}

void loop()
{
  EVERY_N_MILLISECONDS( 80) {
    //pacifica_loop();
    unionJack();
    FastLED.show();
  }
}




// red white and blue shades to fly the Union Jack
// Shade numbers run from dark to light for the colours
// Red    48 - 80
// White  96 - 128
// Blue   0  - 32  
 
#define lightRed 0xFF3333
#define darkRed 0x110000
#define lightGrey 0xAAAAAA
#define darkGrey 0x222222
#define lightBlue 0x3333FF
#define darkBlue 0x000011
CRGB black = CRGB::Black;

CRGBPalette16 UnionJack_p = CRGBPalette16
( 
      darkBlue, lightBlue,  darkBlue, darkRed,
      lightRed, darkRed,    darkGrey, lightGrey,
      darkGrey, black,      black,    black,
      black,    black,      black,    black 
);

// My first go at flying the Union Jack flag
// Read csv file from SPIFFS to hold the colour anchors for each pixel and then poll through the colour
// gradients to give the impression the flag is waving in the wind
// Inputs:
// Filename refers to a csv file that holds a palette index for eaxh pixel you have in your matrix
// palette represents the colours referenced by the csv file
void waveFlag(char fileName[50], CRGBPalette16 palette) {
  static uint8_t strip[NUM_LEDS];
  static uint8_t firstTime = 1;
  const uint8_t freq = 2;  // wave frequency 
  const uint8_t slope = 3; //higher = milder
  uint8_t palletIndex;
  static uint8_t inc = 0;
  int serial;
  uint8_t waveShift;
  
  if (firstTime) {
    //load up strip with color indices
    FetchColorsFromFile("/unionJack.csv", strip);
    firstTime = 0; 
  }
  else {
    inc -= 1;
    for ( int i = 0; i < NUM_TOTAL_STRIPS; i++) {
      for (int j = 0; j < NUM_LEDS_PER_LONG_STRIP; j++) {
        serial = XY(i,j);
        if (serial != -1) {
          waveShift = mod8((i*freq) + (j/slope) + inc, 32);
          palletIndex = strip[serial] + waveShift;
          leds[serial] = ColorFromPalette(palette, palletIndex);
        }  
      }
    }    
  }
}

void unionJack()
{
  waveFlag("/unionJack.csv", UnionJack_p);
}
