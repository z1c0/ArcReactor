#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LEDS 12
#define RING_LEDS 10
#define CORE_LED_1 10
#define CORE_LED_2 11

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);
#define CYAN_R 58
#define CYAN_G 209
#define CYAN_B 228
uint32_t cyan = strip.Color(CYAN_R, CYAN_B, CYAN_G);
uint32_t black = strip.Color(0, 0, 0);
uint32_t white = strip.Color(255, 255, 255);


void startUp()
{
  strip.setPixelColor(CORE_LED_1, cyan);
  strip.setPixelColor(CORE_LED_2, cyan);
  strip.show();

  for (int16_t j = 0; j < 3; j++)
  {  
    delay(1000);
    
    const uint32_t wait = 25;
    for (int16_t i = 0; i < RING_LEDS; i++)
    {
      strip.setPixelColor(i, cyan);
      strip.show();
      delay(wait);
    }  
    
    delay(1000);
    
    for (int16_t i = 0; i < RING_LEDS; i++)
    {
      strip.setPixelColor(i, black);
      strip.show();
      delay(wait);
    }
  }
}

void corePulse()
{
  const uint32_t WAIT = 15;  
  uint8_t r = CYAN_R;
  uint8_t g = CYAN_G;
  uint8_t b = CYAN_B;

  while (r != 255 || g != 255 || b != 255)
  { 
    auto c = strip.Color(r, g, b);
    strip.setPixelColor(CORE_LED_1, c);
    strip.setPixelColor(CORE_LED_2, c);
    strip.show();
    delay(WAIT);
    r = min(r + 1, 255);
    g = min(g + 1, 255);
    b = min(b + 1, 255);        
  }
  
  while (r != CYAN_R || g != CYAN_G || b != CYAN_B)
  { 
    auto c = strip.Color(r, g, b);
    strip.setPixelColor(CORE_LED_1, c);
    strip.setPixelColor(CORE_LED_2, c);
    strip.show();
    delay(WAIT);
    r = max(r - 1, CYAN_R);
    g = max(g - 1, CYAN_G);
    b = max(b - 1, CYAN_B);    
  }
}

void loop()
{
  //corePulse();

  // ringpulse

  // ringwander
}

void setup()
{
  //randomSeed(analogRead(0));
  //Serial.begin(9600);
  
  strip.begin();
  strip.show();

  //startUp();
}

