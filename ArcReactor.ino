#include <Adafruit_NeoPixel.h>

#define PIN 6

#define LEDS 10
#define CORE_LED_1 10
#define CORE_LED_2 11

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

uint32_t blue = strip.Color(0, 0, 255);
uint32_t cyan1 = strip.Color(58, 209, 228);
uint32_t white = strip.Color(0, 0, 255);

void turnOn()
{
  const unsigned long wait = 50;
  for (uint16_t j = 0; j < 3; j++) 
  {  
    for (uint16_t i = 0; i < LEDS; i++) 
    {
      strip.setPixelColor(i, blue);
      strip.show();
      delay(wait);
    }
    
    // core glow white
    strip.setPixelColor(CORE_LED_1, white);
    strip.setPixelColor(CORE_LED_2, white);
    delay(2000);
    
    for (uint16_t i = LEDS - 1; i >= 0; i--) 
    {
      strip.setPixelColor(i, blue);
      strip.show();
      delay(wait);
    }

    delay(1000);
  }
}

void loop()
{ 
  // pulse (white, light blue, dark blue)

  // white led wander in ring

  // random ring color pulse

  // core glow white
}

void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to off
  
  turnOn();
}

