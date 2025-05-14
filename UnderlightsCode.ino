/// @file    Blink.ino
/// @brief   Blink the first LED of an LED strip
/// @example Blink.ino

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 115
#define HALF_LEDS 56
#define QUART_LEDS 28

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 6
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

#define nw_purple CRGB(55, 0, 148)
#define b_orange CRGB(255,69,0)


CHSV lightPurple = CHSV(240, 100, 54);
CHSV midPurple   = CHSV(290, 90, 24);
CHSV darkPurple  = CHSV(0, 0, 100);

uint8_t blendAmount = 0;       // 0 to 255
int8_t direction = 1;          // Forward or backward

CHSV blendCHSV(CHSV color1, CHSV color2, uint8_t blendAmount) {
  uint8_t h = lerp8by8(color1.h, color2.h, blendAmount);
  uint8_t s = lerp8by8(color1.s, color2.s, blendAmount);
  uint8_t v = lerp8by8(color1.v, color2.v, blendAmount);
  return CHSV(h, s, v);
}

void setup() { 
    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    // FastLED.addLeds<SM16703, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1829, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1812, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1904, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS2903, DATA_PIN, RGB>(leds, NUM_LEDS);
     FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2852, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<GS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<APA106, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<PL9823, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2813, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GE8822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD1886, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD1886_8BIT, DATA_PIN, RGB>(leds, NUM_LEDS);
    // ## Clocked (SPI) types ##
    // FastLED.addLeds<LPD6803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
    FastLED.clear();

}

void loop() { 
  
  all_purple();
  delay(5000);
  
  all_orange();
  delay(5000);
  chasing_orange();
  
  chasing_purple();
  
  gay_fade();
  chasing_white();
  water_purple();
  white_flashing();
  delay(500);
  
  water_orange();
  

  //chasing();

  //white_flashing();

}

void all_orange() {
  fill_solid(leds, NUM_LEDS, b_orange);
  FastLED.show();
  //delay(500);
}

void all_purple() {
  fill_solid(leds, NUM_LEDS, nw_purple);
  FastLED.show();
  //delay(500);
}

void all_off() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void white_flashing() {
  int i = 30; //num of flashes
  while(i > 0) {
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
    delay(50);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(50);
    fill_solid(leds, NUM_LEDS, CRGB(b_orange));
    FastLED.show();
    delay(50);  
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(50);
    fill_solid(leds, NUM_LEDS, CRGB(nw_purple));
    FastLED.show();
    delay(50);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(50);
    i--;
  }
}

void chasing_purple() {
  int pulsewidth = 10;
  for(int j = 0; j < 8; j++) {
  int i = 0;
  while(i < HALF_LEDS){
    leds[i] = CRGB(nw_purple);
    FastLED.show();
    leds[NUM_LEDS - i - 1] = CRGB(nw_purple);
    FastLED.show();
    if(i >= pulsewidth) {
      leds[i - pulsewidth] = CRGB::Black;
      FastLED.show();
      leds[NUM_LEDS - i + pulsewidth - 1] = CRGB::Black;
      FastLED.show();
    }
    i++;
  }

  for(int k = pulsewidth; k > 0; k--) {
    leds[HALF_LEDS - k] = CRGB::Black;
    FastLED.show();
    leds[HALF_LEDS + k + 2] = CRGB::Black;     //jank
    FastLED.show();
  }
}
}

void chasing_orange() {
  int pulsewidth = 10;
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  for(int j = 0; j < 8; j++) {
  int i = 0;
  while(i < HALF_LEDS){
    leds[i] = CRGB(b_orange);
    FastLED.show();
    leds[NUM_LEDS - i - 1] = CRGB(b_orange);
    FastLED.show();
    if(i >= pulsewidth) {
      leds[i - pulsewidth] = CRGB::Black;
      FastLED.show();
      leds[NUM_LEDS - i + pulsewidth - 1] = CRGB::Black;
      FastLED.show();
    }
    i++;
  }

  for(int k = pulsewidth; k > 0; k--) {
    leds[HALF_LEDS - k] = CRGB::Black;
    FastLED.show();
    leds[HALF_LEDS + k +2] = CRGB::Black;
    FastLED.show();
  }
}
}

void chasing_white() {
  int pulsewidth = 10;
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  for(int j = 0; j < 8; j++) {
  int i = 0;
  while(i < HALF_LEDS){
    leds[i] = CRGB::White;
    FastLED.show();
    leds[NUM_LEDS - i - 1] = CRGB::White;
    FastLED.show();
    if(i >= pulsewidth) {
      leds[i - pulsewidth] = CRGB::Black;
      FastLED.show();
      leds[NUM_LEDS - i + pulsewidth - 1] = CRGB::Black;
      FastLED.show();
    }
    i++;
  }

  for(int k = pulsewidth; k > 0; k--) {
    leds[HALF_LEDS - k] = CRGB::Black;
    FastLED.show();
    leds[HALF_LEDS + k +2] = CRGB::Black;
    FastLED.show();
  }
}
}


void gay_fade() {
  int i = 350; //about 10s
  while(i > 0){
    blendAmount += direction;
    if (blendAmount >= 255 || blendAmount <= 0) {
      direction *= -1;  // Reverse direction when hitting limits
    }

    // Interpolate between light → mid → dark → mid
    CHSV a = blendCHSV(lightPurple, midPurple, blendAmount);
    CHSV b = blendCHSV(midPurple, darkPurple, blendAmount);


    fill_gradient_HSV(leds, NUM_LEDS, a, b, SHORTEST_HUES);

    FastLED.show();
    delay(20);  // Controls animation speed
    i--;
  }
}

void water_purple() {
  for(int i = 0; i < 7; i++) {
    FastLED.show();
    FastLED.show();
    for(int i = 0; i < QUART_LEDS; i++) {
      leds[QUART_LEDS + i] = CRGB(nw_purple);
      FastLED.show();
      leds[QUART_LEDS - i] = CRGB(nw_purple);
      FastLED.show();
      leds[HALF_LEDS + QUART_LEDS + i] = CRGB(nw_purple);
      FastLED.show();
      leds[HALF_LEDS + QUART_LEDS - i] = CRGB(nw_purple);
      FastLED.show();
    }
    for(int i = QUART_LEDS; i > 0; i--) {
      leds[NUM_LEDS - QUART_LEDS + i] = CRGB::White;
      FastLED.show();
      leds[NUM_LEDS - QUART_LEDS - i - 1] = CRGB::White;
      FastLED.show();
      leds[QUART_LEDS + i ]= CRGB::White;
      FastLED.show();
      leds[QUART_LEDS - i ]= CRGB::White;
      FastLED.show();
    }
    fill_solid(leds, NUM_LEDS, CRGB::Wheat);
    FastLED.show();
  }
}

void water_orange() {
  for(int i = 0; i < 7; i++) {
    FastLED.show();
    FastLED.show();
    for(int i = 0; i < QUART_LEDS; i++) {
      leds[QUART_LEDS + i] = CRGB(b_orange);
      FastLED.show();
      leds[QUART_LEDS - i] = CRGB(b_orange);
      FastLED.show();
      leds[HALF_LEDS + QUART_LEDS + i] = CRGB(b_orange);
      FastLED.show();
      leds[HALF_LEDS + QUART_LEDS - i] = CRGB(b_orange);
      FastLED.show();
    }
    for(int i = QUART_LEDS; i > 0; i--) {
      leds[NUM_LEDS - QUART_LEDS + i] = CRGB::White;
      FastLED.show();
      leds[NUM_LEDS - QUART_LEDS - i - 1] = CRGB::White;
      FastLED.show();
      leds[QUART_LEDS + i ]= CRGB::White;
      FastLED.show();
      leds[QUART_LEDS - i ]= CRGB::White;
      FastLED.show();
    }
    fill_solid(leds, NUM_LEDS, CRGB::Wheat);
    FastLED.show();
  }
}

