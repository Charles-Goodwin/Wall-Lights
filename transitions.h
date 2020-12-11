#include "define.h"
#include "palette.h"


int cursorX = 0;

typedef struct{
    int x;
    int y;
} coord;

void setPixel(int x, int y, int paletteIndex, int brightness){
  int serial = XY(x,y);
  if (serial!=-1){
    leds[serial] =  ColorFromPalette(Text_p, paletteIndex, brightness,LINEARBLEND );
  }
}

void blockColour(coord A, coord B, int colourInd, int brightness){
  int hiX, lowX, hiY, lowY;
  
  if (A.x > B.x) {
    hiX = A.x;
    lowX = B.x; 
  }
  else{
    hiX = B.x;
    lowX = A.x; 
  }
  if (A.y > B.y) {
    hiY = A.y;
    lowY = B.y; 
  }
  else{
    hiY = B.y;
    lowY = A.y; 
  }
  
  for (int i = lowX; i<=hiX; i++) {
    for (int j=lowY; j<=hiY; j++) {
      setPixel(i,j, colourInd, brightness);
    }
  }
}

void clearDisplay(){
  coord topLeft = {0,37};
  coord bottomRight = {18,25};
  blockColour(topLeft, bottomRight, 144, 0);
}

void displaySymbol (char symbol) {
  CRGB colour; 
  int cursorY;
  int serial;
  int ascii = symbol - 37;
  int i = asciiMap[ascii];
  if (i<10){
    colour= CRGB::NUMERAL_COLOUR;
    cursorX ++; //Add spacing between characters
  }
  else{
    colour = CRGB::SYMBOL_COLOUR;
  }
  
  for (int j = 0; j <= 2; j++) {
    if (font_10[i][j]){
      for (int k = 0; k < 10; k++) {
        cursorY = NUM_LEDS_PER_LONG_STRIP -k -1;
        if (bitRead(font_10[i][j], k)) {
          setPixel(cursorX,cursorY, 0X34EBDE, BRIGHTNESS);
        }  
      }
      cursorX ++;
    } 
  }
}

void displayText(String text) {
  cursorX = 1;
  if (text[0] == '1') 
    {cursorX+=2;}
  if (text[1] == '1')
    {cursorX+=2;}
  
  for (int i = 0; i <= text.length()-1; i++) {
    displaySymbol(text[i]);
  }
}

int exitLaser(String message) {
  static int frame = 0;
  static int phase = 0;
  CRGB colour;
  if (phase==0) { 
    //display.clearDisplay();
    for (int k=frame; k <= 5; k++) {   
      int cursorY = k*2;
      cursorX =0;
      for (int pos =0; pos<= message.length()-1; pos++) {
        int ascii = message[pos] - 37;
        int i = asciiMap[ascii];
        if (i<10){
            colour= CRGB::NUMERAL_COLOUR;
            cursorX ++; //Add spacing between characters
        }
        else{
          colour = CRGB::SYMBOL_COLOUR;
        }
        for (int j = 0; j <=2; j++) {
          if (bitRead(font_10[i][j], k)) {
            setPixel(cursorX,cursorY,colour, BRIGHTNESS);
          }
          if (k==6&frame>2) 
            {setPixel(cursorX, 5, colour, BRIGHTNESS);}
          else if (bitRead(font_10[i][j], (12-k))) {
            setPixel(cursorX,(18-k),colour, BRIGHTNESS);  
          }
          if (font_10[i][j]) {cursorX += 3;}
        }
        cursorX += 3;
      }
      frame++;
      if (frame <=5) {
        frame = 0;
        phase++; 
      }
    }
  }
  else {
    
  }
  for (int frame = 0; frame<=(cursorX/2); frame++) {
    //display.clearDisplay();
    //display.drawLine(frame, 12, (cursorX-frame), 12, SSD1306_WHITE);
    //display.display();
  }
  clearDisplay();
}


int enterLaser(String message) {
  CRGB colour;
  for (int frame =6; frame >=0; frame--) {
    //display.clearDisplay();
    CRGB colour;
    for (int k=6; k >= frame; k--) {   
      int cursorY = k*2;
      cursorX =0;
      for (int pos =0; pos<= message.length()-1; pos++) {
        int ascii = message[pos] - 37;
        int i = asciiMap[ascii];
        if (i<10){
          colour= CRGB::NUMERAL_COLOUR;
          cursorX ++; //Add spacing between characters
        }
        else{
          colour = CRGB::SYMBOL_COLOUR;
        }
        for (int j = 0; j <=2; j++) {
          if (bitRead(font_10[i][j], k)) {
            setPixel(cursorX,cursorY, colour, BRIGHTNESS);
          }
          if (k==6&frame>3) 
            {setPixel(cursorX,5, colour, BRIGHTNESS);}
          else if (bitRead(font_10[i][j], (12-k))) {
            setPixel(cursorX,(18-k), colour, BRIGHTNESS);  
          }
          
          if (font_10[i][j]) {cursorX += 3;}
        }
        cursorX += 3;
      }     
    }
  }
}



int exitDown(String message) {
  CRGB colour;
  int frame = 9;
  clearDisplay();
  if (frame >=0) {
    int cursorY = 29 + frame;
    for (int k=0; k <= frame; k++) {   
      cursorX =0;
      for (int pos =0; pos<= message.length()-1; pos++) {
        int ascii = message[pos] - 37;
        int i = asciiMap[ascii];
        if (i<10){
          colour= CRGB::NUMERAL_COLOUR;
        }else{
          colour = CRGB::SYMBOL_COLOUR;
        }
        //Serial.print ("pos: ");
        //Serial.println (pos);
        //Serial.print ("i: ");
        //Serial.println (i);
        for (int j = 0; j <=2; j++) {
          //Serial.print ("j: ");
          //Serial.println (j);
          if (bitRead(font_10[i][j], k)) {
            //Serial.print ("cursorX: ");
            //Serial.println (cursorX);
            //Serial.print ("cursorY: ");
            //Serial.println (cursorY);
            setPixel(cursorX,cursorY, colour, BRIGHTNESS);
          }  
          if (font_10[i][j]) {cursorX++;}
        }
        cursorX++;
      }
      cursorY--;
    }
    frame--;
  }else{
    clearDisplay();
    frame = 9;
    return -1;
  }
}

int enterDown(String message) {
  CRGB colour;
  int frame = 0;
  if (frame <=9) {
    clearDisplay();
    int cursorY = 38-frame;
    for (int k=9; k >= 9-frame; k--) {   
      cursorX =0;
      for (int pos =0; pos<= message.length()-1; pos++) {
        int ascii = message[pos] - 37;
        int i = asciiMap[ascii];
        if (i<10){
          colour= CRGB::NUMERAL_COLOUR;
        }
        else{
          colour = CRGB::SYMBOL_COLOUR;
        }
        Serial.print ("pos: ");
        Serial.println (pos);
        Serial.print ("i: ");
        Serial.println (i);
        for (int j = 0; j <=2; j++) {
          Serial.print ("j: ");
          Serial.println (j);
          if (bitRead(font_10[i][j], k)) {
            Serial.print ("cursorX: ");
            Serial.println (cursorX);
            Serial.print ("cursorY: ");
            Serial.println (cursorY);
            setPixel(cursorX,cursorY,colour, BRIGHTNESS);
          }  
          if (font_10[i][j]) {cursorX++;}
        }
        if (i<10){cursorX++;} // Add a space if we have just displayed a numeral
      }
      cursorY--;
    }
    frame++;
  } else{
    frame = 0;
    return -1;
  }
}

int enterUp(String message) {
  CRGB colour;
  int frame = 0;
  if (frame<=9) {
    Serial.print ("Frame: ");
    Serial.println (frame);
    clearDisplay();
    int cursorY = 29 + frame;
    for (int k=0; k <= frame; k++) {
      Serial.print ("k: ");
      Serial.println (k);
      cursorX =0;
      for (int pos =0; pos<= message.length()-1; pos++) {
        int ascii = message[pos] - 37;
        int i = asciiMap[ascii];
        if (i<10){
          colour= CRGB::NUMERAL_COLOUR;
        }else{
          colour = CRGB::SYMBOL_COLOUR;
        }
        Serial.print ("pos: ");
        Serial.println (pos);
        Serial.print ("i: ");
        Serial.println (i);
        for (int j = 0; j <=2; j++) {
          Serial.print ("j: ");
          Serial.println (j);
          if (bitRead(font_10[i][j], k)) {
            Serial.print ("cursorX: ");
            Serial.println (cursorX);
            Serial.print ("cursorY: ");
            Serial.println (cursorY);
            setPixel(cursorX,cursorY,colour, BRIGHTNESS);
          }  
          if (font_10[i][j]) {cursorX++;}
        }
        if (i<10){cursorX++;} // Add a space if we have just displayed a numeral
      }
      cursorY--;
    }
    frame++;
  }else{
    frame = 0;
    return -1;
  }
}

int exitUp(String message) {
  CRGB colour;
  int frame = 0;
  if (frame <=9) {
    //Serial.print ("Frame: ");
    //Serial.println (frame);
    //display.clearDisplay();
    int cursorY = 38;
    for (int k=frame; k <= 9; k++) {
      //Serial.print ("k: ");
      //Serial.println (k);
      cursorX =0;
      for (int pos =0; pos<= message.length()-1; pos++) {
        int ascii = message[pos] - 37;
        int i = asciiMap[ascii];
        if (i<10){
          colour= CRGB::NUMERAL_COLOUR;
        }else{
          colour = CRGB::SYMBOL_COLOUR;
        }
        //Serial.print ("pos: ");
        //Serial.println (pos);
        //Serial.print ("i: ");
        //Serial.println (i);
        for (int j = 0; j <=2; j++) {
          //Serial.print ("j: ");
          //Serial.println (j);
          if (bitRead(font_10[i][j], k)) {
            //Serial.print ("cursorX: ");
            //Serial.println (cursorX);
            //Serial.print ("cursorY: ");
            //Serial.println (cursorY);
            setPixel(cursorX,cursorY,colour,BRIGHTNESS);
          }  
          if (font_10[i][j]) {cursorX++;}
        }
        if (i<10){cursorX++;} // Add a space if we have just displayed a numeral
      }
      cursorY--;
    }
    frame++;
  }else{
    clearDisplay();
    frame=0;
    return -1;
  }
}

//Lets set up an array with each element pointing to a transition function

typedef int (*Transition)(String);  // creates a type named Transition for a pointer to a function that accepts a String argument and returns an int 
typedef Transition TransitionList[]; // creates a type named TransitionList that is an array of Transition function pointers
//Populate Transition List
TransitionList transitionList {enterLaser, exitLaser,
                               enterUp, exitUp,
                               enterDown, exitDown}; 
                               
// And here is a neat way to refer to the Transition Functions within the list
enum TransitionName { enterLASER, exitLASER,
                      enterUP,    exitUP,
                      enterDOWN,  exitDOWN}; 
                      
// e.g result = transitionList[enterLASER](myString)  
