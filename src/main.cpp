/******************************************************************************
ISL29125_basics.ino
Simple example for using the ISL29125 RGB sensor library.
Jordan McConnell @ SparkFun Electronics
11 Apr 2014
https://github.com/sparkfun/SparkFun_ISL29125_Breakout_Arduino_Library

This example declares an SFE_ISL29125 object called RGB_sensor. The 
object/sensor is initialized with a basic configuration so that it continuously
samples the light intensity of red, green and blue spectrums. These values are
read from the sensor every 2 seconds and printed to the Serial monitor.

Developed/Tested with:
Arduino Uno
Arduino IDE 1.0.5

Requires:
SparkFun_ISL29125_Arduino_Library

This code is beerware.
Distributed as-is; no warranty is given. 
******************************************************************************/

#include <Wire.h>
#include <ISL29125.h>
#include <drv8833.h>
#include "defines.h"

// Declare sensor object
TwoWire colSenWire1(COL_SEN_SDA_1, COL_SEN_SCL_1);
TwoWire colSenWire2(COL_SEN_SDA_2, COL_SEN_SCL_2);
SFE_ISL29125 colSen1(ISL_I2C_ADDR, colSenWire1);
SFE_ISL29125 colSen2(ISL_I2C_ADDR, colSenWire2);


void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

}

// Read sensor values for each color and print them to serial monitor
void loop()
{


}
