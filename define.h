#ifndef DEFINE_H
#define DEFINE_H

#include <FastLED.h> 

#define DATA_PIN    12 // pins tested so far on the Feather ESP32: 13, 12, 27, 33, 15, 32, 14, SCL
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 255
//Irregular Matrix fully defined
#define NUM_SHORT_STRIPS 11
#define NUM_LONG_STRIPS 8
#define NUM_LEDS_PER_SHORT_STRIP 13
#define NUM_LEDS_PER_LONG_STRIP 39
#define NUM_TOTAL_STRIPS (NUM_SHORT_STRIPS + NUM_LONG_STRIPS)
#define NUM_LEDS (NUM_LEDS_PER_LONG_STRIP * NUM_LONG_STRIPS) + (NUM_LEDS_PER_SHORT_STRIP * NUM_SHORT_STRIPS)
#define MAX_POWER_MILLIAMPS 10000
#define X_SCALE 5

#define COL_NUMERAL 0x00FF00
#define COL_SYMBOL 0xFF0000




#define NUMERAL_COLOUR  Green
#define SYMBOL_COLOUR  Red
#define BACK_COLOUR  Black

#define MAX_PATTERNS 8
#define MAX_PALETTES 8



CRGB leds[NUM_LEDS];
uint8_t hues[NUM_LEDS];
static uint8_t patternIndex = 2;
static uint8_t paletteIndex = 2;
uint8_t g_brightness = BRIGHTNESS;
uint8_t g_hueTempo = 0;
uint8_t g_hueShift = 0;

#endif
