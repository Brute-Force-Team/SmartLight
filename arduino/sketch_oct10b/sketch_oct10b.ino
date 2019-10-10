#include <FastLED.h>
#define NUM_LEDS 14
#define DATA_PIN 6
CRGB  leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  int index = 0;
  char string[20];
  while(Serial.available()>0){
    char input_char = Serial.read();
    string[0] = input_char;
  }
  if(string[0]=='Y'){
    turn_on();
  }else if(string[0] == 'N'){
    turn_off();
  }
}

void turn_on(){
  for(int i = 0; i < NUM_LEDS; ++i){
    leds[i] = CRGB::White;
  }
  FastLED.show();
}

void turn_off(){
  for(int i = 0; i < NUM_LEDS; ++i){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void test(){
  // Turn the first led red for 1 second
  //leds[0] = CRGB::Red;
  //FastLED.show();
  //delay(1000);
  // Set the first led back to black for 1 second
  //leds[0] = CRGB::Black; FastLED.show();
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = CRGB::White;
    FastLED.show();
    delay(10);
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  //delay(1000);
}
