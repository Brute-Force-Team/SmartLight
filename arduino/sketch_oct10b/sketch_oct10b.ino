#include <FastLED.h>
#define NUM_LEDS 14
#define DATA_PIN 6
CRGB  leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  // int index = 0;
  // char string[20];
  // while(Serial.available()>0){
  //   char input_char = Serial.read();
  //   string[0] = input_char;
  // }
  test();
}

void test(){
  // Turn the first led red for 1 second
  //leds[0] = CRGB::Red;
  //FastLED.show();
  //delay(1000);
  // Set the first led back to black for 1 second
  //leds[0] = CRGB::Black; FastLED.show();
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(100);
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  //delay(1000);
}
