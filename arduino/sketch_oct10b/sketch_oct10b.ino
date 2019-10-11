#include <FastLED.h>
#define NUM_LEDS 6
#define DATA_PIN_RIGHT 5
#define DATA_PIN_LEFT 6
#define SENSOR1 12
#define SENSOR2 13

bool night = true;
bool deepnight = false;


CRGB leds_left[NUM_LEDS];
CRGB leds_right[NUM_LEDS];
byte string[20];
bool sensor_controll = false;
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_LEFT>(leds_left, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_RIGHT>(leds_right, NUM_LEDS);
  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
}

void loop() {
  int index = 0;
  string[0] = 'L';string[1]=0;string[2]=0;string[3]=0;string[4]=0;
  bool flag = false;

  while(Serial.available()>0){
    string[index] = Serial.read();
    index++;
    flag = true;
    delay(5);
  }

  if(flag){
    if(string[1]=='Y'){
      turn_on('L');
      turn_on('R');
    }else if(string[1] == 'N'){
      turn_off('L');
      turn_off('R');
    }else if(string[1] == 'C'){
      setColor(string[0], string[2]-1,string[3]-1,string[4]-1,string[5]);
    }else if(string[0] == 'D'){
      sensor_controll = true;
    }
  }
  if(sensor_controll){
    digital_sensor();
  }
}
void test(){
  // Turn the first led red for 1 second
  //leds_left[0] = CRGB::Red;
  //FastLED.show();
  //delay(1000);
  // Set the first led back to black for 1 second
  //leds_left[0] = CRGB::Black; FastLED.show();
  for(int i = 0; i<NUM_LEDS; i++){
    leds_left[i] = CRGB::White;
    FastLED.show();
    delay(10);
    leds_left[i] = CRGB::Black;
    FastLED.show();
  }
  //delay(1000);
}

void turn_on(char dirr){
  if(dirr == 'L'){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds_left[i] = CRGB::White;
    }
  }else if(dirr == 'R'){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds_left[i] = CRGB::White;
    }
  }

  FastLED.show();
}
void turn_off(char dirr){
  if(dirr == 'L'){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds_left[i] = CRGB::Black;
    }
  }else if(dirr == 'R'){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds_left[i] = CRGB::Black;
    }
  }

  FastLED.show();
}
void setColor(char dirr, char red,char green,char blue,char id){
  if(dirr == 'L'){
    if(id == 'F'){
      for(int i = 0; i<NUM_LEDS; ++i){
        leds_left[i].setRGB(red,green,blue);
        FastLED.show();
      }
    }else{
      while(id>NUM_LEDS){
        id = id - NUM_LEDS;
      }
      leds_left[id].setRGB(red,green,blue);
      FastLED.show();
    }
  }else if(dirr == 'R'){
    if(id == 'F'){
      for(int i = 0; i<NUM_LEDS; ++i){
        leds_right[i].setRGB(red,green,blue);
        FastLED.show();
      }
    }else{
      while(id>NUM_LEDS){
        id = id - NUM_LEDS;
      }
      leds_right[id].setRGB(red,green,blue);
      FastLED.show();
    }
  }


}
void set_temp_brightness(int brightness, int end_brightness){
  for(int i = 0; i<NUM_LEDS; ++i){
    for(int j = brightness; j<end_brightness; ++j){
      leds_left[i].setRGB(j,j,j);
      leds_right[i].setRGB(j,j,j);
      FastLED.show();
      delay(10);
    }
  }
  delay(5000);
  for(int i = 0; i < NUM_LEDS; ++i){
    for(int j = end_brightness; j<brightness; --j){
      leds_left[i].setRGB(j,j,j);
      leds_right[i].setRGB(j,j,j);
      FastLED.show();
      delay(10);
    }
  }
}
void set_brightness(int brightness){
  for(int i = 0; i < NUM_LEDS; ++i){
    leds_left[i].setRGB(brightness,brightness,brightness);
    leds_right[i].setRGB(brightness,brightness,brightness);
  }
  FastLED.show();
}

void digital_sensor(){
  bool state = digitalRead(SENSOR1);
  if(night){
    if(deepnight){
      set_brightness(25500/40);
      if(state){
        set_temp_brightness(25500/40,25500/90);
      }
    }else{
      set_brightness(25500/70);
      if(state){
        set_temp_brightness(25500/70,25500/90);
      }
    }
  }else{
    turn_off('L');
    turn_off('R');
  }

}
