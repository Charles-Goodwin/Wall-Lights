//
//  Union Jack
//  Fly the flag and watch it wave in the breeze.
//  August 2020, Charles Goodwin
//

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#include "define.h"
#include "OTA.h"
#include "patterns.h"
#include "timeSync.h"
#include "web.h"

FASTLED_USING_NAMESPACE

//////////////////////////////////////////////////////////////////////////


void setup() {
  delay( 3000); // 3 second delay for boot recovery, and a moment of silence
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection( TypicalLEDStrip );
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(115200);

  //Just need these 2 lines to enable OTA
  //ArduinoOTA.setHostname("Wall Lights");
  //setupOTA();

  //connect to WiFi
  connectToWIFI();

  //Initialise web server
  handleServerRequests();
    
  //timeSync();
  
  randomSeed(analogRead(A0));
}

void loop(){
  
  //ArduinoOTA.handle();
  
  // Fast as you like
  // Keep invoking the current pattern to render the next frame
  patterns[patternIndex].pattern();
  FastLED.show();

  EVERY_N_MILLISECONDS(1000) {
    ws.cleanupClients();
  } 
}


 
