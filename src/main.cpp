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
#include <MPU6050.h>
#include "defines.h"
#include "helpers.h"
#include "math.h"

// Instantiate colour sensors
TwoWire colSenWire1(COL_SEN_SDA_1, COL_SEN_SCL_1);
TwoWire colSenWire2(COL_SEN_SDA_2, COL_SEN_SCL_2);
SFE_ISL29125 colSen1(ISL_I2C_ADDR, colSenWire1);
SFE_ISL29125 colSen2(ISL_I2C_ADDR, colSenWire2);

void calibrateColours(SFE_ISL29125 colSen, bool isLow)
{
  const float MAX_ITERATIONS = 200;
  uint16_t current_calibration_val = 0;
  uint16_t intensity = 0;

  //red
  for (uint8_t i = 0; i < MAX_ITERATIONS; i++)
  {
    intensity = colSen.readRed();
    if (isLow) {current_calibration_val = current_calibration_val < intensity ? current_calibration_val : intensity;}
    else {current_calibration_val = current_calibration_val > intensity ? current_calibration_val : intensity;}
    delay(1);
  }
  Serial.print("Red: ");
  Serial.println(current_calibration_val);

  //green
  current_calibration_val = 0;
  for (uint8_t i = 0; i < MAX_ITERATIONS; i++)
  {
    intensity = colSen.readGreen();
    if (isLow) {current_calibration_val = current_calibration_val < intensity ? current_calibration_val : intensity;}
    else {current_calibration_val = current_calibration_val > intensity ? current_calibration_val : intensity;}
    delay(1);
  }
  Serial.print("Green: ");
  Serial.println(current_calibration_val);

  //blue
  current_calibration_val = 0;
  for (uint8_t i = 0; i < MAX_ITERATIONS; i++)
  {
    intensity = colSen.readBlue();
    if (isLow) {current_calibration_val = current_calibration_val < intensity ? current_calibration_val : intensity;}
    else {current_calibration_val = current_calibration_val > intensity ? current_calibration_val : intensity;}
    delay(1);
  }
  Serial.print("Blue: ");
  Serial.println(current_calibration_val);
}

void colourCalibrationSequence()
{
  bool isSequenceOneComplete = false;
  bool isSequenceTwoComplete = false;

  Serial.println("Press button to start WHITE calibration...");
  while (!isSequenceOneComplete)
  {
    if (digitalRead(USER_BTN) == 0)
    {
      delay(100);
      if (digitalRead(USER_BTN) == 0)
      {
        Serial.println("Colour Sensor 1:");
        calibrateColours(colSen1, true);

        Serial.println();
        
        Serial.println("Colour Sensor 2:");
        calibrateColours(colSen2, true);

        isSequenceOneComplete = true;
      }
    }
  }

  Serial.println("Press button to start BLACK calibration...");
  while (!isSequenceTwoComplete)
  {
    if (digitalRead(USER_BTN) == 0)
    {
      delay(100);
      if (digitalRead(USER_BTN) == 0)
      {
        Serial.println("Colour Sensor 1:");
        calibrateColours(colSen1, false);

        Serial.println();
        
        Serial.println("Colour Sensor 2:");
        calibrateColours(colSen2, false);

        isSequenceOneComplete = true;
      }
    }
  }
}

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(USER_BTN, INPUT);

  // Initialize the ISL29125 with simple configuration so it starts sampling
  if (colSen1.init())
  {
    Serial.println("Colour Sensor 1 Initialization: SUCCESSFUL");
  }
  else
  {
    Serial.println("Colour Sensor 1 Initialization: FAILED");
  }

  if (colSen2.init())
  {
    Serial.println("Colour Sensor 2 Initialization: SUCCESSFUL");
  }
  else
  {
    Serial.println("Colour Sensor 2 Initialization: FAILED");
  }
  Serial.println();

  colourCalibrationSequence();
  
}

// Read sensor values for each color and print them to serial monitor
void loop()
{
  digitalToggle(LED_BUILTIN);
  delay(250);
}
