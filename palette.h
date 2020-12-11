#ifndef PALETTE_H
#define PALETTE_H

// red white and blue shades to fly the Union Jack
// Shade numbers run from dark to light for the colours
// Blue   0  - 32  
// Red    48 - 80
// White  96 - 128


DEFINE_GRADIENT_PALETTE( UnionJack_pink_gp ) {
  0,    0,    0,    255,
  8,    0,    255,  255,
  16,   0,    0,    255,
  32,   0,    0,    255,
  48,   255,  0,    0,
  56,   255,  0,    255,
  64,   255,  0,    0,
  80,   255,  0 ,   0, 
  96,   200,  200,  200,
  104,  0,    255,  0,
  112,  200,  200,  200, 
  255,  200,  200,  200};

DEFINE_GRADIENT_PALETTE( UnionJack_grey_gp ) {
  0,    80,  80,  80,
  8,    0,   0,   255,
  16,   80,  80,  80,
  32,   80,  80,  80,
  48,   20,  20,  20,
  56,   255,  0,  0,
  64,   20,   20,   20,
  80,   20,   20,   20,
  96,   150,  150,  150,
  104,  255,  255,  255,
  112,  150,  150,  150,
  255,  150,  150,  150};

DEFINE_GRADIENT_PALETTE( digitalRain_gp ) {
  0,    90,  100,  100,
  8,    20,  150,  30,
  16,   40,  120,  50,
  24,   90, 150,  100,
  32,   10,  100,  20,
  40,   40,  100,   50,
  48,   90, 150,  100,
  56,   60,  120,  70,  
  64,   10,  150,  20, 
  80,   0,   150,  0,
  255,  0,   150,  0};

  
DEFINE_GRADIENT_PALETTE( Cloud_gp ) {
  0,    100, 130, 130,
  64,   90,  100, 100,
  128,  40,  50,  50,
  160,  100, 140, 140,
  192,  30,  40,  40,
  255,  100, 130, 130};

DEFINE_GRADIENT_PALETTE( HeavyFreezingRain_gp ) {
  0,    0,   0,   0, 
  15,   0,   20,  120,
  23,   0,   100, 100,
  31,   0,   0,   100,
  47,   0,   25,  100,
  63,   50,  100, 100,
  71,   0,   50,  150,
  79,   0,   0,   0,
  195,  0,   10,  100,
  111,  0,   0,   0,
  127,  0,   0,   100,
  143,  0,   50,  100,
  159,  50,  100, 100,
  167,  0,   0,   0, 
  175,  0,   20,  100,
  191,  0,   50,  120,
  207,  0,   0,   0,
  223,  0,   0,   100,
  231,  0,   0,   0,
  239,  0,   50,  100,
  255,  0,   0,   0};

  DEFINE_GRADIENT_PALETTE( FreezingRain_gp ) {
  0,    50,  100, 100, 
  15,   0,   0,   100,
  23,   0,   0,   0,
  31,   0,   0,   0,
  47,   0,   50,  100,
  63,   50,  100, 100,
  71,   0,   0,   0,
  79,   0,   60,  100,
  195,  0,   10,  100,
  111,  0,   0,   0,
  143,  0,   0,   0,
  159,  50,  100, 100,
  167,  0,   0,   0, 
  175,  0,   0,   0,
  191,  0,   0,   100,
  207,  0,   100, 100,
  223,  0,   0,   0,
  231,  0,   50,  100,
  239,  0,   0,   0,
  255,  0,   0,   0};

DEFINE_GRADIENT_PALETTE( LightFreezingRain_gp ) {
  0,    0,   0,   0, 
  15,   0,   0,   0,
  23,   0,   0,   0,
  31,   0,   0,   0,
  47,   0,   0,   100,
  63,   60,  100, 100,
  71,   0,   0,   0,
  79,   0,   0,   0,
  195,  0,   0,   0,
  111,  0,   0,   0,
  143,  0,   50,  100,
  159,  60,  100, 100,
  167,  0,   0,   0, 
  175,  0,   0,   0,
  191,  0,   0,   0,
  207,  0,   0,   100,
  223,  0,   0,   0,
  231,  0,   0,   0,
  239,  0,   0,   0,
  255,  0,   0,   0};

DEFINE_GRADIENT_PALETTE( HeavyRain_gp ) {
  0,    0,   0,   0, 
  15,   0,   0,   100,
  23,   0,   100, 100,
  31,   0,   0,   100,
  47,   0,   25,  100,
  63,   0,   0,   100,
  71,   0,   50,  100,
  79,   0,   0,   0,
  195,  0,   10,  100,
  111,  0,   0,   0,
  127,  0,   0,   100,
  143,  0,   50,  100,
  159,  0,   0,   100,
  167,  0,   0,   0, 
  175,  0,   20,  100,
  191,  0,   0,   0,
  207,  0,   50,  100,
  223,  0,   0,   100,
  231,  0,   0,   0,
  239,  0,   50,  100,
  255,  0,   0,   0};

DEFINE_GRADIENT_PALETTE( Rain_gp ) {
  0,    0,   20,  100, 
  15,   0,   0,   100,
  23,   0,   0,   0,
  31,   0,   0,   0,
  47,   0,   50,  100,
  63,   0,   0,   100,
  71,   0,   0,   0,
  79,   0,   0,   0,
  195,  0,   10,  100,
  111,  0,   0,   0,
  143,  0,   0,   0,
  159,  0,   0,   100,
  167,  0,   0,   0, 
  175,  0,   0,   0,
  191,  0,   0,   100,
  207,  0,   100, 100,
  223,  0,   0,   0,
  231,  0,   20,  100,
  239,  0,   0,   0,
  255,  0,   0,   0};

DEFINE_GRADIENT_PALETTE( LightRain_gp ) {
  0,    0,   0,   0, 
  15,   0,   0,   0,
  23,   0,   0,   0,
  31,   0,   0,   0,
  47,   0,   0,   100,
  63,   0,   20,  100,
  71,   0,   0,   0,
  79,   0,   0,   0,
  195,  0,   0,   0,
  111,  0,   0,   0,
  143,  0,   50,  100,
  159,  0,   0,   0,
  167,  0,   0,   0, 
  175,  0,   0,   0,
  191,  0,   0,   0,
  207,  0,   40,  100,
  223,  0,   0,   0,
  231,  0,   0,   0,
  239,  0,   0,   0,
  255,  0,   0,   0};

  DEFINE_GRADIENT_PALETTE( HeavyHail_gp ) {
  0,    0,   0,   0, 
  15,   0,   0,   0,
  23,   70,  100, 100,
  31,   0,   0,   0,
  47,   70,  100, 100,
  55,   0,   0,   0,
  71,   0,   0,   0,
  79,   0,   0,   0,
  195,  70,  100, 100,
  103,  0,   0,   0,
  127,  70,  100, 100,
  135,  0,   0,   0,
  159,  0,   0,   0,
  167,  0,   0,   0, 
  175,  70,  100, 100,
  183,  0,   0,   0,
  207,  0,   0,   0,
  223,  70,  100, 100,
  231,  0,   0,   0,
  239,  0,   0,   0,
  255,  70,  100, 100};

DEFINE_GRADIENT_PALETTE( Hail_gp ) {
  0,    0,   0,   0, 
  15,   0,   0,   0,
  23,   0,   0,   0,
  31,   0,   0,   0,
  47,   70,  100, 100,
  55,   0,   0,   0,
  71,   0,   0,   0,
  79,   0,   0,   0,
  195,  70,  100, 100,
  103,  0,   0,   0,
  127,  70,  100, 100,
  135,  0,   0,   0,
  159,  0,   0,   0,
  167,  0,   0,   0, 
  175,  0,   0,   0,
  183,  0,   0,   0,
  207,  0,   0,   0,
  223,  70,  100, 100,
  231,  0,   0,   0,
  239,  0,   0,   0,
  255,  0,   0,   0};

DEFINE_GRADIENT_PALETTE( LightHail_gp ) {
  0,    0,   0,   0, 
  15,   0,   0,   0,
  23,   0,   0,   0,
  31,   0,   0,   0,
  47,   70,  100, 100,
  63,   0,   0,   0,
  71,   0,   0,   0,
  79,   0,   0,   0,
  195,  0,   0,   0,
  111,  0,   0,   0,
  143,  0,   0,   0,
  159,  0,   0,   0,
  167,  70,  100, 100, 
  175,  0,   0,   0,
  191,  0,   0,   0,
  207,  70,  100, 100,
  215,  0,   0,   0,
  231,  0,   0,   0,
  239,  0,   0,   0,
  255,  0,   0,   0};


DEFINE_GRADIENT_PALETTE( Snow_gp ) {
  0,    0,    0,    0, 
//  15,   0,    0,    0,
//  31,   0,    0,    0,
  47,   0,    0,    0,
  63,    50,   70,    70,
//  79,   0,    0,    0,
//  95,   0,    0,    0,
  111,  130,  150,  150,
  127,  130,  150,  150,
  143,  130,  150,  150,
//  159,  0,    0,    0,
//  175,  0,    0,    0,
  191,  50,    70,    70,
  207,  0,    0,    0,
//  223,  0,    0,    0,
//  239,  0,    0,    0,
  255,  0,    0,    0};

DEFINE_GRADIENT_PALETTE( Sunshine_gp ) {
  0,    90,    50,     0, 
  16,   150,    50,     0, 
  32,   60,    60,     0,   
  48,   100,   50,     0,
  64,   80,    80,     0,
  80,   150,   150,    0,
  96,   100,   50,     0,
  112,  40,    40,     0, 
  128,  100,   50,     0,
  144,  70,    70,     0,
  160,  100,   100,    0,
  176,  150,   150,    0,
  192,  100,   60,     0,
  208,  50,    50,     0,
  224,  150,   100,    0,
  240,  100,   100,    0,
  255,  90,    50,     0};

  
DEFINE_GRADIENT_PALETTE( RGB_Test_gp ) {
  0,    255,  0,    0,
  75,   0,    255,  0,
  150,  0,    0,    255,
  255,  0,    0,    255
  } ;   


  
DEFINE_GRADIENT_PALETTE( Fluorescent_red_gp ) {
  0,    255,  0,  0,
  240,  15,   5,  20,
  255,  15,   5,  20
  } ; 


DEFINE_GRADIENT_PALETTE( Thermal_gp ) {
  0,  85, 85, 85,  // white
  127, 85, 85, 85,  // white 
  143, 0, 0, 255,      // blue
  159, 0, 255, 0,      // green
  175, 171, 171, 0,    // yellow
  191, 171, 85, 0,    // orange
  207, 255, 0, 0,     // red
  255, 255, 0, 0      // red    
};

const TProgmemRGBPalette16 Text_p FL_PROGMEM =
{ 0x34ebde, 0x34ebde, 0x34ebde, 0x34ebde, //red, orange, yellow, green
  0x34ebde, 0x34ebde, 0x34ebde, 0x34ebde, // aqua, blue, purple, pink 
  0x34ebde, 0x34ebde, 0x34ebde, 0x34ebde, // red, black, white, red
  0x34ebde, 0x34ebde, 0x34ebde, 0x34ebde  //red, red, red, red
};

// This function generates a random palette that's a gradient
// between four different colors.  The first is a dim hue, the second is 
// a bright hue, the third is a bright pastel, and the last is 
// another bright hue.  This gives some visual bright/dark variation
// which is more interesting than just a gradient of different hues.
void SetupRandomPalette(CRGBPalette16& palette )
{
  palette = CRGBPalette16( 
                      CHSV( random8(), 255, 32), 
                      CHSV( random8(), 255, 255), 
                      CHSV( random8(), 128, 255), 
                      CHSV( random8(), 255, 255)); 
}

void SetupMyPalette(CRGBPalette16& palette )
{
  palette = CRGBPalette16( 
                      CHSV( 145, 255, 225), 
                      CHSV( 160, 255, 255), 
                      CHSV( 192, 255, 128), 
                      CHSV( 160, 128, 255)); 
}
void SetupLavaRedPalette(CRGBPalette16& palette )
{
  palette = CRGBPalette16( 
                      CHSV( 64, 255,  255), 
                      CHSV( 0,  255,  100), 
                      CHSV( 32, 255,  128), 
                      CHSV( 32, 128,  255)); 
}
void SetupLavaBluePalette(CRGBPalette16& palette )
{
  palette = CRGBPalette16( 
                      CHSV( 160, 255,  255), 
                      CHSV( 145,  255, 100), 
                      CHSV( 128, 255,  255), 
                      CHSV( 100, 180,  255)); 
}

void SetupLavaPurplePalette(CRGBPalette16& palette )
{
  palette = CRGBPalette16( 
                      CRGB(0,   0,  0 ), 
                      CRGB(88,  0,  150), 
                      CRGB(163, 0,  101), 
                      CRGB(255, 79, 161)); 
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette(CRGBPalette16& palette )
{
  // 'black out' all 16 palette entries...
  fill_solid( palette, 16, CRGB::Black);
  // and set every fourth one to white.
  palette[0] = CRGB::White;
  palette[4] = CRGB::White;
  palette[8] = CRGB::White;
  palette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette(CRGBPalette16& palette )
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;
  
  palette = CRGBPalette16( 
    green,  green,  black,  black,
    purple, purple, black,  black,
    green,  green,  black,  black,
    purple, purple, black,  black );
}

const CRGBPalette32 palettes[] = {
  UnionJack_grey_gp,
  UnionJack_pink_gp,
  Cloud_gp
};

#endif
