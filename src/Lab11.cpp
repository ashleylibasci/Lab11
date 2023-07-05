/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/ashleylibasci/IoTFolderLabs/Lab11/src/Lab11.ino"
#include "Particle.h"
#include "LIS3DH.h"
#include "oled-wing-adafruit.h"

void setup();
void loop();
#line 5 "/Users/ashleylibasci/IoTFolderLabs/Lab11/src/Lab11.ino"
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