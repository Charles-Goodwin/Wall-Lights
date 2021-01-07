
//Colour fraction
CRGB ColourFraction(CRGB colour, float fraction){
  fraction = min(1.0f, fraction);
  return CRGB(colour).fadeToBlackBy(255 * (1.0f - fraction)); 
}

void DrawPixels(float x, float y, CRGBPalette256 palette) {
  float density = 0.5;
  // x = 5.2, y = 10.25
  // For x we are going to apportion across integer and fractional part
  uint8_t x1_pos = (long)x;
  uint8_t x2_pos = x1_pos + 1;
  float x2_frac = x - x1_pos;
  float x1_frac = 1 - x2_frac;
  uint8_t y1_pos = (long)y;
  uint8_t y2_pos = y1_pos + 1;
  float y2_frac = y - y1_pos;
  float y1_frac = 1 - y2_frac;
  
  
}


void Xmas(CRGBPalette256 palette) {
  //memset(leds, 0, NUM_LEDS * 3);
  uint8_t diameter = 15; 
  uint8_t bpm = 220;
  static uint8_t pal_Index = 1;
  static uint8_t y = 0;
  static float shrink = 1;
  float rX = 0;
  int lX = 0;
  float colourFrac1, colourFrac2 = 0;
  static uint8_t startPoint = 2;
  static boolean started = false;
  
  //Lets build a double helix, make it run from bottom to top and reduce the amplitude as it reaches the top  
  // Dim every cell (x/256) each time 
  for (int i = 17; i< 142; i++) {
    if (leds[i].getLuma()<8) {
      leds[i] = CRGB(0,5,0);
    }
  }
  for (int i = 433; i<455; i++){
    if (leds[i].getLuma()<8) {
       leds[i] = CRGB(0,5,0);
    }
    if (leds[i-136].getLuma()<8) {
       leds[i-136] = CRGB(0,5,0);
    }
  }
  for (int i = 338; i <=416; i++){
    if (leds[i].getLuma()<8) {
       leds[i] = CRGB(0,5,0);
    }
  }
  
  if (y>12){
    shrink -= 0.032;  
  }
  
  float x = ((beatsin8(bpm, 0, diameter,0,0)- (diameter/2))* shrink)  + (diameter/2) ;
  
  if ((long)x == startPoint){
    started = true; 
  }
  
  if ((mod8(x, X_SCALE) ==0) || (mod8(x+1, X_SCALE) ==0 )) {
    rX = x/X_SCALE;
    lX = (int)rX;
    colourFrac2 = rX - (float)lX;
    colourFrac1 = 1.00f - colourFrac2;
    if (mod8(x, X_SCALE) == 0){ 
      leds[XY(lX,y)] += ColorFromPalette(palette, pal_Index, (long)(g_brightness*colourFrac1), LINEARBLEND);
      leds[XY(lX + 15, y)] += ColorFromPalette(palette, pal_Index, (long)(g_brightness*colourFrac1), LINEARBLEND);
    }
    if ((colourFrac2 > 0) && (mod8(x+1, X_SCALE) == 0) ) {
      leds[XY(lX+1,y)] += ColorFromPalette(palette, pal_Index, (long)(g_brightness*colourFrac1), LINEARBLEND);
      leds[XY(lX + 16, y)] += ColorFromPalette(palette, pal_Index, (long)(g_brightness*colourFrac1), LINEARBLEND);
    }
  }
  
  if (started) {
    y ++;
  }  
 
  if (y > 38) {
    y=0; 
    shrink=1; 
    started = false;
    startPoint = diameter - startPoint;
  }
  //Serial.println(x);
  /*
  Serial.println(y);
  Serial.println(rX);
  Serial.println(lX);
  Serial.println(colourFrac1);
  Serial.println(colourFrac2); 
  Serial.println();
  */
  /*
  Serial.println(y);
  Serial.println(rX);
  Serial.println(((long)x)/X_SCALE);
  Serial.println(colourFrac);
  Serial.println();
*/
}
