#include <FastLED.h>
#define NUM_LEDS 6
#define DATA_PIN_RIGHT 5
#define DATA_PIN_LEFT 6
#define SENSOR1 12
#define SENSOR2 13
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 20

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

CRGB leds[NUM_LEDS];

bool night = true;
bool deepnight = true;

byte string[20];
bool sensor_controll = false;
void setup() {
  Serial.begin(115200);
  delay( 3000 );
  FastLED.addLeds<LED_TYPE, DATA_PIN_LEFT, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN_RIGHT, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  //FastLED.addLeds<NEOPIXEL, DATA_PIN_LEFT>(leds, NUM_LEDS);
  //FastLED.addLeds<NEOPIXEL, DATA_PIN_RIGHT>(leds, NUM_LEDS);
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
    if(string[0]=='Y'){
      sensor_controll = false;
      turn_on('L');
      turn_on('R');
    }else if(string[0] == 'N'){
      sensor_controll = false;
      turn_off('L');
      turn_off('R');
    }else if(string[1] == 'C'){
      sensor_controll = false;
      setColor(string[0], string[2]-1,string[3]-1,string[4]-1,string[5]);
    }else if(string[0] == 'D'){
      sensor_controll = true;
    }else if(string[0] == 'A'){
      sensor_controll = false;
      automode();
    }
  }
  if(sensor_controll){
    digital_sensor();
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
void turn_on(char dirr){
  if(dirr == 'L'){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds[i] = CRGB::White;
    }
  }else if(dirr == 'R'){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds[i] = CRGB::White;
    }
  }

  FastLED.show();
}
void turn_off(char dirr){
  if(dirr == 'L'){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds[i] = CRGB::Black;
    }
  }else if(dirr == 'R'){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
}
void setColor(char dirr, char red,char green,char blue,char id){
  if(dirr == 'L'){
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
  }else if(dirr == 'R'){
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


}
void set_temp_brightness(int brightness, int end_brightness){
  Serial.write("new fix; state = true\n");
  for(int j = brightness; j<end_brightness; ++j){
    for(int i = 0; i<NUM_LEDS; ++i){
      leds[i].setRGB(j,j,j);
      leds[i].setRGB(j,j,j);
      FastLED.show();
    }
    delay(10);
  }
  delay(5000);
  while(night && digitalRead(SENSOR2)){delay(5000); Serial.write("state = true\n");}
  Serial.write("state = false\n");
  for(int j = end_brightness; j>brightness; --j){
    for(int i = 0; i < NUM_LEDS; ++i){
      leds[i].setRGB(j,j,j);
      leds[i].setRGB(j,j,j);
      FastLED.show();
    }
    delay(10);
  }
  delay(500);
}
void set_brightness(int brightness){
  for(int i = 0; i < NUM_LEDS; ++i){
    leds[i].setRGB(brightness,brightness,brightness);
    leds[i].setRGB(brightness,brightness,brightness);
  }
  FastLED.show();
}
void digital_sensor(){
  bool state = digitalRead(SENSOR2);
  delay(100);
  if(night){
    if(deepnight){
      set_brightness(102);
      if(state){
        set_temp_brightness(102,230);
      }
    }else{
      set_brightness(179);
      if(state){
        set_temp_brightness(179,230);
      }
    }
  }else{
    turn_off('L');
    turn_off('R');
  }
  delay(100);
}
void automode(){
  while(true){
    ChangePalettePeriodically();
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    if(Serial.available()>0)return;
  }
}



void FillLEDsFromPaletteColors( uint8_t colorIndex){
    uint8_t brightness = 255;

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
void ChangePalettePeriodically(){
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;

    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}
void SetupTotallyRandomPalette(){
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}
void SetupBlackAndWhiteStripedPalette(){
    fill_solid( currentPalette, 16, CRGB::Black);
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;

}
void SetupPurpleAndGreenPalette(){
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;

    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM ={
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,

    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,

    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
