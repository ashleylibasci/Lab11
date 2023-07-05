/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/ashleylibasci/IoTFolderLabs/Lab11/src/try.ino"
#include "Particle.h"
#include "LIS3DH.h"
#include "oled-wing-adafruit.h"

void setup();
void loop();
#line 5 "/Users/ashleylibasci/IoTFolderLabs/Lab11/src/try.ino"
LIS3DH accelerometer;
OledWingAdafruit display;

SYSTEM_THREAD(ENABLED);

LIS3DHSPI accel(SPI, D3, WKP);

void setup()
{
    Serial.begin(9600);
    display.setup();
    accelerometer.setup();
    accelerometer.setRange(LIS3DH_RANGE_4_G); // Set accelerometer range to +/-4g
}

void loop()
{
    float x = accelerometer.getAccelerationX();
    float y = accelerometer.getAccelerationY();
    float z = accelerometer.getAccelerationZ();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Accelerometer Data:");

    display.setTextSize(2);
    display.setCursor(0, 16);
    display.print("X: ");
    display.print(x);
    display.println(" G");

    display.setCursor(0, 40);
    display.print("Y: ");
    display.print(y);
    display.println(" G");

    display.setCursor(0, 64);
    display.print("Z: ");
    display.print(z);
    display.println(" G");

    display.display();

    delay(500); // Read accelerometer data every 500 milliseconds
}
