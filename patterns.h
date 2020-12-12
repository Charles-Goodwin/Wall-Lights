#include "define.h"
#include "palette.h"
#include "readFile.h"
#include "xy.h"
#include "font.h"
#include "transitions.h"
#include "timeSync.h"
#include "patNoise.h"

typedef struct Circle{
    int x = 0; //expressed as 6 times 
    int y  = 0; 
    int radius = 0;
    uint8_t maxRadius = 0;
    uint8_t hue = 0; 
    int x_shift = 0;
    int y_shift = 0;
    int shrinkExpand = 0;
  };

// My first stab at emulating the iconic raining code from the movie The Matrix
// The Palette parameter allows you to use an alternative to the traditional green monitor effect
void digitalRainPalette(CRGBPalette16 palette) {
  //Declare a Trail type
  // Trail comprises of x, y coords, governing throttle, life span and a palette index
  typedef struct Trail{
    uint8_t x =0;
    uint8_t y =0;
    uint8_t throttle = 0; //higher reduces speed, lower increases speed (timer reset value)
    uint8_t timer = 0;  //advance every time timer expires 
    uint8_t lifeSpan = 0; // determines if trail reaches the bottom
    uint8_t palIndex = 0;
  } ;

  const int NUM_TRAILS = 24;
  static int phase = 0;
  
  switch (phase) {
    case 0:
    //Render all the neopixels Black
    fill_solid(leds, NUM_LEDS, CRGB::Black);  
    phase =1;
    break;
    
    case 1:
    //Serial.println("codeFall");
    // Declare a list of Trails that we will track
    static Trail trailList[NUM_TRAILS];
    
    // Add entropy to random number generator; we use a lot of it.
    random16_add_entropy(random(256));
  
    // Dim every cell by 10% (20/256) each time
    for ( uint16_t i = 0; i < NUM_LEDS; i++) {
      leds[i].fadeToBlackBy(10);
    }
  
    //Go through all the trails
    for (uint8_t i = 0; i < NUM_TRAILS; i++) {
      
      //Check if Trail is active
      // Check that lifespan has not expired
      if (trailList[i].lifeSpan > 0) {
        //Continue countdown until it expires
        if (trailList[i].timer > 0) {
          //coontinue with countdown of waiting
          trailList[i].timer--;
        }
        else {
          //Assign the color to the head of the trail
          leds[XY(trailList[i].x,trailList[i].y)] = ColorFromPalette(palette, trailList[i].palIndex, BRIGHTNESS, NOBLEND);
          //Set the tail of the trail 
          leds[XY(trailList[i].x, trailList[i].y + 1)] = ColorFromPalette(palette, (trailList[i].palIndex+8), BRIGHTNESS, NOBLEND);
          leds[XY(trailList[i].x, trailList[i].y + 2)] = ColorFromPalette(palette, (trailList[i].palIndex+16), BRIGHTNESS, NOBLEND);
          leds[XY(trailList[i].x, trailList[i].y + 3)] = ColorFromPalette(palette, 200, BRIGHTNESS, NOBLEND);
          // The remaining part of the tail will fade as part of the general dimming
          
          //Advance trail down one
          trailList[i].y --;
          // Deplete the life span
          trailList[i].lifeSpan --;
          
          //Advance the palette index
          trailList[i].palIndex += 8;
          if (trailList[i].palIndex > 40) {
            trailList[i].palIndex = 0;
          }
             
          //Reset the timer
          trailList[i].timer = trailList[i].throttle;
          //Trail's life ends at reaching the bottom 
          if (trailList[i].y == 0) {trailList[i].lifeSpan = 0;}
        }
      }
      else {
        //Create a new Trail
        //Pick a random column
        trailList[i].x = random8(NUM_TOTAL_STRIPS);
        //trailList[i].x = 14;       
        //Built in random pause by placing starting height position beyond top led)
        trailList[i].y = random8(NUM_LEDS_PER_LONG_STRIP/2) + NUM_LEDS_PER_LONG_STRIP;
        
        trailList[i].throttle = random8(3); // Higher is slower; Lower is faster
      
        trailList[i].timer = 0;
        trailList[i].palIndex = 8* random8(5);
        //Default lifespan for Trail to reach the bottom
        trailList[i].lifeSpan = trailList[i].y;
      
        //  Once in a while shorten the lifespan so that the trail stops short
          if (!(random8(5)%5)) {trailList[i].lifeSpan += ((NUM_LEDS_PER_LONG_STRIP * random8(100) / 100)- NUM_LEDS_PER_LONG_STRIP);}
      }
    }
    break;
  }
}

void digitalRain() {
  digitalRainPalette(palettes[paletteIndex].palette);
}


// My first go at flying the Union Jack flag
// Read csv file from SPIFFS to hold the colour anchors for each pixel and then poll through the colour
// gradients to give the impression the flag is waving in the wind
// Inputs:
// Filename refers to a csv file that holds a palette index for eaxh pixel you have in your matrix
// palette represents the colours referenced by the csv file
void waveFlag(char fileName[50], CRGBPalette32 palette) {
  static uint8_t strip[NUM_LEDS];
  static uint8_t firstTime = 1;
  const uint8_t freq = 2;  // wave frequency 
  const uint8_t slope = 4; //higher = milder
  uint8_t palletIndex;
  static uint8_t inc = 0;
  int serial;
  uint8_t waveShift;
  
  if (firstTime) {
    //load up strip with color indices
    FetchColorsFromFile(fileName, strip);
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
          leds[serial] = ColorFromPalette(palette, palletIndex, BRIGHTNESS, LINEARBLEND );
        }  
      }
    } 
  }
}

// We must have fire
void Fire2012WithPalette(CRGBPalette16 gPal)
{
// Array of temperature readings at each simulation cell
  const uint8_t COOLING = 80;
  const uint8_t SPARKING = 120;
  const uint8_t  NUM_SECTION = 39;
  static byte heat[NUM_SECTION];
  
  const boolean gReverseDirection = true;
   typedef struct flame{
    byte heat[NUM_SECTION];
  } ;

  static flame flames[19];
  for( int f = 0; f < 19; f++) {

    // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_SECTION; i++) {
      flames[f].heat[i] = qsub8( flames[f].heat[i],  random8(0, ((COOLING * 10) / NUM_SECTION) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_SECTION - 1; k >= 2; k--) {
      flames[f].heat[k] = (flames[f].heat[k - 1] + flames[f].heat[k - 2] + flames[f].heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      flames[f].heat[y] = qadd8( flames[f].heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_SECTION; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( flames[f].heat[j], 240);
      leds[XY(f,j)] = ColorFromPalette( gPal, colorindex);
    }
  }
}
void pong (){
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  static int paddleSteps = 30;

  displayText(fetchTime());
  for (int j =0; j < 19; j++) {
    //leds[XY(j,38)] = CRGB::Grey;
    leds[XY(j,0)] = CRGB::Grey;
  }
  for (int j =0; j < 39; j+=2) {
      leds[XY(0,j)] = CRGB::Grey;
      //leds[XY(9,j)] = CRGB::Grey;
      leds[XY(18,j)] = CRGB::Grey;
  }
  // Paddles

  int displacement = 0;
  if (paddleSteps > 0){
    if (paddleSteps >15){
      displacement = 30 - paddleSteps;
    }else{
      displacement = paddleSteps;
    }
    paddleSteps--;
  }
  for (int j =0; j < 7; j+=1) {
     leds[XY(1,j + 15 - displacement)] = CRGB::White;
     leds[XY(17,j+15 + displacement)] = CRGB::White;
  }
  
  EVERY_N_MILLISECONDS(15000) {
    paddleSteps =30;
  }
  
}


void drawCircle (Circle circle){
  CRGBPalette16 antialias_p;
  float antialiasRadius = circle.radius * 1.08;
  
  
  for (int x = -circle.radius ; x <=circle.radius; x++){  
    float result = sqrt16( (antialiasRadius * antialiasRadius) - (x * x));
    int y = (int)result;
    int x_pixel = circle.x + x;
    if (mod8(x_pixel,X_SCALE)==0){ 
      // used to ensure even for a negative number that
      // x_pixel rounds down
      if (x_pixel<0){x_pixel -= X_SCALE;}  
      x_pixel /= X_SCALE;
      
      for (int y_pixel = circle.y - y; y_pixel <= circle.y + y; y_pixel++){
        int i = XYwrap(x_pixel,y_pixel);
        if (i != -1) {
          uint8_t brightness = BRIGHTNESS;
          if (hues[i] == 0) {brightness = 0;}
          antialias_p[0] = CHSV(hues[i],255, brightness);
          antialias_p[255] = CHSV(hues[i] + circle.hue,255, BRIGHTNESS);
          //leds[i] = ColorFromPalette(antialias_p,127, BRIGHTNESS/5, LINEARBLEND);
          //leds[i] = CRGB::Red;
          leds[i] = CHSV(circle.hue,255, BRIGHTNESS/5);
        }
      }
    }
  }

  for (int x = -circle.radius ; x <=circle.radius; x++){  
    int y = sqrt16( (circle.radius * circle.radius) - (x * x));
    int x_pixel = circle.x + x;
    if (mod8(x_pixel,X_SCALE)==0){
      // used to ensure even for a negative number that
      // x_pixel rounds down
      if (x_pixel<0){x_pixel -= X_SCALE;}  
      x_pixel /= X_SCALE;
      /*
      Serial.println("Start of x loop");
      Serial.println (x);
      Serial.println (y);
      Serial.println (x_pixel);
      */
      for (int y_pixel = circle.y - y; y_pixel <= circle.y + y; y_pixel++){
        //Serial.println("Start of y_pixel loop");
        //Serial.println(y_pixel);
        int i = XYwrap(x_pixel,y_pixel);
        if (i != -1) {
          /*
          Serial.println(i);
          Serial.println(x_pixel);
          Serial.println(y_pixel);
          Serial.println ("End of y_pixel loop");  
          */
          hues[i] += circle.hue; 
          leds[i] = CHSV(hues[i],255, BRIGHTNESS);
        }
      }
    }
    //Serial.println("End of x loop");
  }
}

void displayCircles (CRGBPalette16 palette, boolean bump){
  uint8_t ballHues[5] = {245, // blue
                         224, // pink
                         110, // green
                         64,  // yellow
                         192  // purple
  };
  
  const uint8_t maxCircles = 5;
  const uint8_t maxRadius = 10;
  static Circle circles[maxCircles];
  //Clear down all the hues
  memset(hues,0,sizeof(hues));
  memset(leds, 0, NUM_LEDS * 3);
  for (int i =0; i < maxCircles; i++){
    //Adjust the size
    circles[i].radius +=  circles[i].shrinkExpand;
    //Check for new circle
    if (circles[i].radius <= 0) {
      circles[i].x = random8(X_SCALE * NUM_TOTAL_STRIPS);
      //circles[i].x = 6;
      circles[i].y = random8(39);
      //circles[i].y = 20;
      circles[i].radius = 8;
      circles[i].maxRadius = random8(maxRadius);
      circles[i].maxRadius = 15;
      circles[i].hue = ballHues[i];
      circles[i].x_shift = random8(3)-1;
      circles[i].y_shift = random8(3)-1;
      circles[i].shrinkExpand = random8(3) + 1;
      circles[i].shrinkExpand = 0;
    }
    //Start shrinking if too large
    if (circles[i].radius > circles[i].maxRadius ) {
       circles[i].shrinkExpand = 0 - random8(3); 
    }
    /*
    Serial.println("Before Move");
    Serial.println(i);
    Serial.println(circles[i].x);
    Serial.println(circles[i].y);
    Serial.println (circles[i].radius);
    Serial.println (circles[i].maxRadius);
    Serial.println (circles[i].hue);
    Serial.println (circles[i].x_shift);
    Serial.println (circles[i].y_shift);
    Serial.println (circles[i].shrinkExpand);
    Serial.println("End of circle content");
    */
    //delay(1000);
    // Move the circle
    circles[i].x += circles[i].x_shift;
    circles[i].y += circles[i].y_shift;
    //Check if a bounce is required
    if (bump && (circles[i].x - circles[i].radius < 0 || circles[i].x + circles[i].radius >= NUM_TOTAL_STRIPS * X_SCALE)){
      //Serial.println ("x bump detected");
      if (circles[i].x - circles[i].radius < 0 ) {
        circles[i].x_shift = abs8(circles[i].x_shift);
      } else {
        circles[i].x_shift = abs8(circles[i].x_shift) * -1;
      }
    }
    if (circles[i].x > NUM_TOTAL_STRIPS * X_SCALE) {circles[i].x -= (NUM_TOTAL_STRIPS * X_SCALE);}
    if (circles[i].x < 0) {circles[i].x += (NUM_TOTAL_STRIPS * X_SCALE);}
    
    if (bump && (circles[i].y - circles[i].radius < 0 || circles[i].y + circles[i].radius >= NUM_LEDS_PER_LONG_STRIP)){
      // Serial.println ("y bump detected");
      if (circles[i].y - circles[i].radius < 0 ) {
        circles[i].y_shift = abs8(circles[i].y_shift);
      } else {
        circles[i].y_shift = abs8(circles[i].y_shift) * -1;
      }
    }
    if (circles[i].y >= NUM_LEDS_PER_LONG_STRIP) {circles[i].y -= NUM_LEDS_PER_LONG_STRIP;}
    if (circles[i].y < 0) {circles[i].y += NUM_LEDS_PER_LONG_STRIP;}
    
    // increment the hue
    //circles[i].hue ++;
    /*
    Serial.println("After move");
    Serial.println(i);
    Serial.println(circles[i].x);
    Serial.println(circles[i].y);
    Serial.println (circles[i].radius);
    Serial.println (circles[i].maxRadius);
    Serial.println (circles[i].hue);
    Serial.println (circles[i].x_shift);
    Serial.println (circles[i].y_shift);
    Serial.println (circles[i].shrinkExpand);
    Serial.println("End of circle content");
    */
    //render the circle
    drawCircle(circles[i]);
  }
}

void rainbowCircles (){
  displayCircles(Rainbow_gp, true);
}

void displayColours(){
  leds[0] = CHSV(HUE_RED,100,100);
  Serial.print("First time leds[0]: ");
  Serial.println(leds[0]);
  leds[0] += CHSV(HUE_RED,10,10);
  Serial.print("Second time leds[0]: ");
  Serial.println(leds[0]);
  //delay(20000);
}



void fluorescent(CRGBPalette16 palette){
  int brightness;
  int palletIndex;
  static uint8_t firstTime = 1;   
  static uint8_t interval = 0;
  static uint8_t flipFlop = 0;
  
  for ( int i = 0; i < NUM_TOTAL_STRIPS ; i++) {
    for ( int j = 0; j < NUM_LEDS_PER_LONG_STRIP; j++) {
      int serial = XY(i,j);
      if (serial != - 1){
        brightness = j;
        palletIndex = map(j,0,38,240,0);
        leds[serial] = ColorFromPalette(palette, palletIndex,brightness,LINEARBLEND );
      }
    }
  }
  if (firstTime) {
    EVERY_N_MILLISECONDS(4000) {
     firstTime = 0; 
    }
    if (interval) {
      interval--;
      if (flipFlop) {
         fill_solid(leds,NUM_LEDS, 0); 
      }
    }
    else {
      interval = random8 (30);
      flipFlop = 1 - flipFlop;
    }
  }
}

void displayWeather(){
  
}

void displayInfo() {
  static int phase = 1;
  EVERY_N_MILLISECONDS(5000) {
    phase++;
  }
  switch (phase) {
    case 0:
      displayText(fetchTime());
      break;
    case 1:
      displayText(fetchDate());  
      break;
    case 2 ... 3:
      displayWeather();
      break;
  } 
}


void displayRain(CRGBPalette32 palette_cloud, CRGBPalette32 palette_rain){
  static int phase = 0;
  static uint8_t strip[NUM_LEDS];
  int index;
  
  switch (phase) {
  case 0: // Initialise leds
    for ( int i = 0; i < NUM_LEDS ; i++) {
      strip[i] = random8();
    }
    for ( int i = 0; i < 4 ; i++) {
      for ( int j = 25; j >= 0 ; j--) {
        strip[XY(i,j)] = (i*30) + (j*8);
        strip[XY((i+15),j)] = (i*60) + (j*8);
      }
    }
    phase = 1;
    break;
  case 1: 
    for ( int i = 0; i < 4 ; i++) {
      for ( int j = 0; j < NUM_LEDS_PER_LONG_STRIP ; j++) {
        index = XY(i,j);
        if (index != -1) {
          if (j < 26) {
            leds[index] = ColorFromPalette(palette_rain, strip[index], BRIGHTNESS, NOBLEND );
            strip[index]+= 8;
          } else {
            leds[index] = ColorFromPalette(palette_cloud, strip[index], BRIGHTNESS, LINEARBLEND );
            strip[index]+= 1;
          }
        }
      }
    }
    break;
  }
}

void displaySnow(int intensity){
  static uint8_t phase = 0;
  static uint8_t strip[NUM_LEDS];
  static uint8_t trailInfo[2][8][2]; //trailNo,flakeNo,Info where 0=height, 1=paletteIndex
  static uint8_t counter = 0;
  CRGBPalette16 Snow = Snow_gp; 
  CRGBPalette32 palette_cloud = Cloud_gp;
  
  switch (phase) {
  case 0: // Initialise leds
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < intensity; j++) {  
        trailInfo[i][j][0] = 26 + random8(12) ;
        trailInfo[i][j][1] = random8(255);
        }
    }
    for (int i = 0; i < 4; i++) { 
      for (int j = 26; j < 39; j++) {
          int index = XY(i,j);
          if (index != -1) {
            strip[index] = random8();  
          }
      }
    }
   
    phase = 1;
    break;
  case 1:
    fill_solid (leds, 156, CRGB :: Black);
    //Draw the snow flakes
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < intensity; j++) { 
        int leftIndex = XY((i*2),trailInfo[i][j][0]);
        int rightIndex = XY(((i*2)+1),trailInfo[i][j][0]);
        if (leftIndex != -1 && rightIndex != -1) {
          leds[leftIndex] = ColorFromPalette(Snow, trailInfo[i][j][1], BRIGHTNESS, LINEARBLEND );
          leds[rightIndex] = ColorFromPalette(Snow, (127 + trailInfo[i][j][1]), BRIGHTNESS, LINEARBLEND );
          
          if (!mod8(counter,4)) {
            trailInfo[i][j][0]--;
          }
          trailInfo[i][j][1] += 4;   
          if (trailInfo[i][j][0] == 0) {
            trailInfo[i][j][0] = random8(12) + 26 ;
          }
        }
      }
    }
     //Draw the cloud
    for (int i = 0; i < 4; i++) { 
      for (int j = 26; j < 39; j++) {
        int index = XY(i,j);
        if (index != -1) {
          leds[index] = ColorFromPalette(palette_cloud, strip[index], BRIGHTNESS, LINEARBLEND ); 
          strip[index]+= 1; 
        }
      }
    }
    counter++;
    break;
  }
}

void displayCloud2(int percentage, CRGBPalette32 palette_cloud){
  //We are going to have a go at using sin waves to show cloud
  int const maxWaves = 3;
  int const bpm = 30;
  memset(leds, 0, NUM_LEDS * 3);
  for (uint8_t wav = 0; wav < maxWaves; wav++){
    for (uint8_t i = 0; i <19; i++) {  
      uint8_t y = beatsin8(bpm + (wav*bpm/10), 0, 5 + (wav*2),0, i*30);
      int grey = 40 + (wav * 20);
      leds[XY(i,y+32-(wav*2))] = CRGB(grey, grey,grey);
      if (wav==0) {
        leds[XY(i,y+31-(wav*2))] = CRGB(grey, grey,grey);
      }
    }  
  }
}

void testPannel(){
  CRGBPalette16 blendPalette;
  blendPalette[0] = CHSV(HUE_GREEN,50,50);
  blendPalette[100] = CHSV(HUE_RED,50,50);

  for (int i = 0; i<NUM_LEDS_PER_LONG_STRIP; i++){
    leds[XY(0,i)] = ColorFromPalette(blendPalette, 0,BRIGHTNESS , LINEARBLEND);
    leds[XY(1,i)] = ColorFromPalette(blendPalette, 100,BRIGHTNESS , LINEARBLEND);
    leds[XY(2,i)] = ColorFromPalette(blendPalette, 50,BRIGHTNESS , LINEARBLEND);
  }
    
}



void displayCloud(int percentage, CRGBPalette32 palette_cloud, CRGBPalette32 palette_sun){
  static int phase = 0;
  static uint8_t strip[NUM_LEDS];
  
  switch (phase) {
  case 0: 
    // Initialise Cloud
    for (int i = 0; i < 4; i++) { 
      for (int j = 26; j < 39; j++) {
        int index = XY(i,j);
        if (index != -1) {
          strip[index] = random8();  
        }
      }
    }
    //set up rays of sunshine
    for (int i = 0; i < 4; i++) { 
      for (int j = 0; j < 26; j++) {
        int index = XY(i,j);
        if (index != -1) {
          strip[index] = (i * 10) + (j/5);  
        }        
        
      }
    }
    phase = 1;
    break;
  case 1: 
    for (int i = 0; i < 4; i++) { 
      for (int j = 0; j < 39; j++) {
        int index = XY(i,j);
        if (index != -1) {
          //Animate Sunshine
          if (j <26){
            leds[index] = ColorFromPalette(palette_sun, strip[index], BRIGHTNESS, LINEARBLEND );  
          }
          //Animate Cloud
          else {
            leds[index] = ColorFromPalette(palette_cloud, strip[index], BRIGHTNESS, LINEARBLEND );
          }
          strip[index]+= 1;
        }
      }
    }
    break;
  }
}

void displaySunshine(){
  static int phase = 0;
  static int count = 0;
  CRGBPalette16 sunshine = Sunshine_gp;
  static uint8_t matrix[39][4] = {
    {10, 11, 16, 20},
    {9, 10, 15, 20},
    {8, 10, 14, 20},
    {7, 9,  14, 19},
    {6, 9,  13, 19},
    {5, 8,  13, 19},
    {4, 7,  13, 18},
    {3, 7, 12, 18},
    {2, 6, 12, 18},
    {1, 6, 12, 18},
    {0, 6, 12, 18},
    {1, 6, 12, 18},
    {2, 6, 12, 18},
    {3, 7, 12, 18},
    {4, 7, 13, 18},
    {5, 8, 13, 19},
    {6, 9, 13, 19},
    {7, 9, 14, 19},
    {8, 10, 14, 20},
    {9, 10, 15, 20},
    {10, 11, 16, 20},
    {11, 12, 16, 21},
    {12, 13, 17, 22},
    {13, 15, 18, 23},
    {14, 16, 18, 23},
    {15, 16, 19, 23},
    {16, 17, 20, 24},
    {17, 18, 21, 25},
    {18, 19, 22, 25},
    {19, 20, 22, 26},
    {20, 21, 23, 0},
    {21, 22, 24, 0},
    {22, 23, 25, 0},
    {23, 24, 26, 0},
    {24, 25, 0,  0},
    {25, 26, 0,  0},
    {26, 0,  0,  0},
    {0,  0,  0,  0},
    {0,  0,  0,  0}
    };
  switch (phase) {
  case 0: 
    // Initialise Sun
    for (int j = 38; j <= 0; j--) { 
      for (int i = 0; i < 4; i++) {
        int index = XY(i,j);
        if (index != -1) {
          leds[index] = 5*matrix[38-j][i];  
        }
      }
    }
   
    phase = 1;
    break;
  case 1: 
    //radiate the sun
    for (int i = 0; i < 4; i++) { 
      for (int j = 0; j <= 38; j++) {
        int index = XY(i,j);
        if (index != -1) {
          if (matrix[38-j][i] != 0) {
            leds[index] = ColorFromPalette(sunshine, (count + matrix[38-j][i]), BRIGHTNESS, LINEARBLEND) ;  
          }
        }        
      }
    }
    count--;
    break;
  }
}

void showPallet(CRGBPalette32 palette){
  for ( int i = 0; i < 256 ; i++) {
    leds[i] = ColorFromPalette(palette, i, BRIGHTNESS, NOBLEND );
  }
}
void showTestPalette(){
  showPallet(digitalRain_gp);
}


void displayMist(){
  displayCloud2(50, Cloud_gp);
}



void UnionJack_Pink() {
   waveFlag("/unionJack.csv", UnionJack_pink_gp);
};

void UnionJack_Grey() {
   waveFlag("/unionJack.csv", UnionJack_grey_gp);
}

void UnionJack() {
   waveFlag("/unionJack.csv", palettes[paletteIndex].palette);
}

void Fluorescent_Red() {
  fluorescent(palettes[paletteIndex].palette);
}

void displayMessage() {
  displayText("1.2:3%");
}

void displayHeavyFreezingRain() {
   displayRain(Cloud_gp,HeavyFreezingRain_gp);
}

void displayFreezingRain() {
   displayRain(Cloud_gp,FreezingRain_gp);
}

void displayLightFreezingRain() {
   displayRain(Cloud_gp,LightFreezingRain_gp);
}

void displayHeavyRain() {
   displayRain(Cloud_gp,HeavyRain_gp);
}

void displayRain() {
   displayRain(Cloud_gp,Rain_gp);
}

void displayLightRain() {
   displayRain(Cloud_gp,LightRain_gp);
}

void displayHeavyHail() {
   displayRain(Cloud_gp,HeavyHail_gp);
}

void displayHail() {
   displayRain(Cloud_gp,Hail_gp);
}

void displayLightHail() {
   displayRain(Cloud_gp,LightHail_gp);
}

void displayHeavySnow() {
   displaySnow(4);
}

void displaySnow() {
   displaySnow(3);
}

void displayLightSnow() {
   displaySnow(2);
}

void displayFlurries() {
   displaySnow(1);
}

void fire2012() {
  Fire2012WithPalette(palettes[paletteIndex].palette);
}

//Lets sort out a play list
//First lets define its structure
typedef void (*Pattern)();
typedef Pattern PatternList[];
typedef struct {
  Pattern pattern;
  String name;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];

//Now lets populate it
PatternAndNameList patterns = {
 {displayNoise,                   "lava lamp"},
 {fire2012,                       "Fire"},
 {digitalRain,                    "Matrix Digital Rain"} ,
 {UnionJack,                      "Union Jack"},
 {rainbowCircles,                 "Bouncing circles"},
 {Fluorescent_Red,                "Florescent Tube" },
 {pong,                           "Pong clock"},
 {displaySunshine,                "Sunshine"},
 {displayHeavySnow,               "Heavy Snow" }, 
 {displayFreezingRain,            "Freezing Rain" }, 
// {displayMist,                    "Wavey clouds"},
//  { displaySnow,                "Display Snow" }, 
//  { displayLightSnow,           "Display Light Snow" }, 
//  { displayFlurries,            "Display Flurries" }, 
//  { displayHeavyFreezingRain,   "Display Heavy Freezing Rain" }, 
 
//  { displayLightFreezingRain,   "Display Light Freezing Rain" }, 
//  { displayHeavyRain,           "Display Heavy Freezing Rain" }, 
  { displayRain,                "Display Freezing Rain" }, 
//  { displayLightRain,           "Display Light Freezing Rain" }, 
//  { displayHeavyHail,           "Display Heavy Freezing Rain" }, 
  { displayHail,                "Display Freezing Rain" }, 
//  { displayLightHail,           "Display Light Freezing Rain" }, 
  { displayInfo,                "Display Date and Time" }
  
};
