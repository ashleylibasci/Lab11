#include "Particle.h"
#include "LIS3DH.h"
#include "oled-wing-adafruit.h"

SYSTEM_THREAD(ENABLED);

LIS3DHSPI accel(SPI, D3, WKP);

OledWingAdafruit display;

const unsigned long PRINT_SAMPLE_PERIOD = 100;

void positionInterruptHandler();

unsigned long lastPrintSample = 0;

volatile bool positionInterrupt = false;
uint8_t lastPos = 0;

void setup()
{
  Serial.begin(9600);
  display.setup();
  display.clearDisplay();
  display.display();

  attachInterrupt(WKP, positionInterruptHandler, RISING);

  delay(5000);

  // Initialize sensors
  LIS3DHConfig config;
  config.setPositionInterrupt(16);

  bool setupSuccess = accel.setup(config);
  Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void loop()
{
  display.loop();

  LIS3DHSample sample;

  if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD)
  {
    lastPrintSample = millis();
    if (accel.getSample(sample))
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("%d,%d,%d");
      display.setCursor(0, 15);
      display.println(sample.x);
      display.setCursor(30, 15);
      display.println(sample.y);
      display.setCursor(60, 15);
      display.println(sample.z);
      display.display();
      Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
    }
    else
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("no sample");
      display.display();
      Serial.println("no sample");
    }
  }
  if (positionInterrupt)
  {
    positionInterrupt = false;

    // Test the position interrupt support. Normal result is 5.
    // 5: normal position, with the accerometer facing up
    // 4: upside down
    // 1 - 3: other orientations
    uint8_t pos = accel.readPositionInterrupt();
    if (pos != 0 && pos != lastPos)
    {
      Serial.printlnf("pos=%d", pos);
      lastPos = pos;
    }
  }
}

void positionInterruptHandler()
{
  positionInterrupt = true;
}
