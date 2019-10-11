#include <FastLED.h>
#define NUM_LEDS 6
#define DATA_PIN 6

CRGB leds[NUM_LEDS];
byte string[20];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  int index = 0;
  string[0] = '0';string[1]=0;string[2]=0;string[3]=0;string[4]=0;
  bool flag = false;
  while(Serial.available()>0){
    string[index] = Serial.read();
    index++;
    flag = true;
    delay(5);
  }
  if(flag){
    if(string[0]=='Y'){
      Serial.write(string[0]);
      turn_on();
    }else if(string[0] == 'N'){
      Serial.write(string[0]);
      turn_off();
    }else if(string[0] == 'C'){
      for(int i = 0; i<5; ++i){
        // unsigned char chr = string[i];
        Serial.write(string[i]);
      }
      setColor(string[1]-1,string[2]-1,string[3]-1,string[4]);
    }
  }
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
void setColor(char red,char green,char blue,char id){

  if(id == 'F'){
    for(int i = 0; i<NUM_LEDS; ++i){
      leds[i].setRGB(red,green,blue);
      FastLED.show();
    }
  }else{
    while(id>NUM_LEDS){
      id = id - NUM_LEDS;
    }
    leds[id].setRGB(red,green,blue);
    FastLED.show();
  }
}
