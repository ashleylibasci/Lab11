#include "Particle.h"
#include "LIS3DH.h"
#include "oled-wing-adafruit.h"

SYSTEM_THREAD(ENABLED);

LIS3DHSPI accel(SPI, D3, WKP);

OledWingAdafruit display;

void setup()
{
  Serial.begin(9600);
  display.setup();
  display.clearDisplay();
  display.display();
}

void loop()
{
  display.loop();
}