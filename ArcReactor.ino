#include <Adafruit_NeoPixel.h>
#include "ColorPulser.h"

#define PIN 6
#define LEDS 12
#define RING_LEDS 10
#define CORE_LED_1 10
#define CORE_LED_2 11

#define CYAN_R 58
#define CYAN_G 209
#define CYAN_B 228

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t black = strip.Color(0, 0, 0);
uint32_t cyan = strip.Color(CYAN_R, CYAN_B, CYAN_G);
uint32_t halfWhite = strip.Color(150, 255, 255);
uint32_t white = strip.Color(255, 255, 255);


void core(uint32_t color)
{
  strip.setPixelColor(CORE_LED_1, color);
  strip.setPixelColor(CORE_LED_2, color);
  strip.show();
}

void ring(uint32_t color, uint32_t wait = 0)
{
  for (int16_t i = 0; i < RING_LEDS; i++)
  {
    strip.setPixelColor(i, color);
    if (wait != 0)
    {
      strip.show();
      delay(wait);
    }
  } 
  strip.show();
}

void corePulse()
{
  const uint32_t WAIT = 15; 
  int16_t count = 0;

  ring(cyan);
  
  ColorPulser pulser(Color(CYAN_R, CYAN_G, CYAN_B), Color(255, 255, 255));  
  while (count < 10)
  { 
    auto& c = pulser.Value();
    core(strip.Color(c.R, c.G, c.B));
    delay(WAIT);
    if (!pulser.Animate())
    {
      count++;
    }
  }
}

void ringPulse()
{
  const uint32_t WAIT = 15; 
  int16_t count = 0;

  core(cyan);
  
  ColorPulser pulser(Color(CYAN_R, CYAN_G, CYAN_B), Color(255, 255, 255));  
  while (count < 10)
  { 
    auto& c = pulser.Value();
    ring(strip.Color(c.R, c.G, c.B));
    delay(WAIT);
    if (!pulser.Animate())
    {
      count++;
    }
  }
}

void ringWander()
{
  int16_t wanderPos = 0;
  
  for (int32_t j = 0; j < RING_LEDS * 10; j++)
  {  
    for (int16_t i = 0; i < RING_LEDS; i++)
    {    
      strip.setPixelColor(i, cyan);
    }
    strip.setPixelColor((wanderPos - 1) % RING_LEDS, halfWhite);
    strip.setPixelColor(wanderPos, white);
    strip.setPixelColor((wanderPos + 1) % RING_LEDS, halfWhite);
    strip.show();

    delay(500);

    wanderPos = (wanderPos + 1) % RING_LEDS; 
  }
}

void startUp()
{
  core(cyan);

  for (int16_t j = 0; j < 3; j++)
  {  
    delay(1000);
    
    const uint32_t wait = 25;
    
    ring(cyan, wait);
    delay(1000);
    
    ring(black, wait);
  }
}

void loop()
{
  corePulse();

  ringPulse();

  ringWander();
}

void setup()
{
  //randomSeed(analogRead(0));
  //Serial.begin(9600);
  
  strip.begin();
  strip.show();

  //startUp();
}

