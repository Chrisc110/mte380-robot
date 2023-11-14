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

uint16_t whiteRedCalibration1 = 0;
uint16_t whiteGreenCalibration1 = 0;
uint16_t whiteBlueCalibration1 = 0;
uint16_t blackRedCalibration1 = 0;
uint16_t blackGreenCalibration1 = 0;
uint16_t blackBlueCalibration1 = 0;

uint16_t whiteRedCalibration2 = 0;
uint16_t whiteGreenCalibration2 = 0;
uint16_t whiteBlueCalibration2 = 0;
uint16_t blackRedCalibration2 = 0;
uint16_t blackGreenCalibration2 = 0;
uint16_t blackBlueCalibration2 = 0;

void calibrateColours(SFE_ISL29125* colSen, bool isLow, uint16_t* redCalibration, uint16_t* greenCalibration, uint16_t* blueCalibration)
{
  const uint8_t MAX_ITERATIONS = 200;
  uint16_t current_calibration_val = 0;
  uint16_t reset_val = 0;
  uint16_t intensity = 0;

  if (isLow)
  {
    reset_val = 65535;
  }

  //red
  current_calibration_val = reset_val;
  for (uint8_t i = 0; i < MAX_ITERATIONS; i++)
  {
    intensity = colSen->readRed();
    if (isLow) {current_calibration_val = current_calibration_val < intensity ? current_calibration_val : intensity;}
    else {current_calibration_val = current_calibration_val > intensity ? current_calibration_val : intensity;}
    delay(1);
  }
  *redCalibration = current_calibration_val;

  //green
  current_calibration_val = reset_val;
  for (uint8_t i = 0; i < MAX_ITERATIONS; i++)
  {
    intensity = colSen->readGreen();
    if (isLow) {current_calibration_val = current_calibration_val < intensity ? current_calibration_val : intensity;}
    else {current_calibration_val = current_calibration_val > intensity ? current_calibration_val : intensity;}
    delay(1);
  }
  *blueCalibration = current_calibration_val;

  //blue
  current_calibration_val = reset_val;
  for (uint8_t i = 0; i < MAX_ITERATIONS; i++)
  {
    intensity = colSen->readBlue();
    if (isLow) {current_calibration_val = current_calibration_val < intensity ? current_calibration_val : intensity;}
    else {current_calibration_val = current_calibration_val > intensity ? current_calibration_val : intensity;}
    delay(1);
  }
  *greenCalibration = current_calibration_val;
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
        calibrateColours(&colSen1, true, &whiteRedCalibration1, &whiteGreenCalibration1, &whiteBlueCalibration1);        
        calibrateColours(&colSen2, true, &whiteRedCalibration2, &whiteGreenCalibration2, &whiteBlueCalibration2);

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
        calibrateColours(&colSen1, false, &blackRedCalibration1, &blackGreenCalibration1, &blackBlueCalibration1);
        calibrateColours(&colSen2, false, &blackRedCalibration2, &blackGreenCalibration2, &blackBlueCalibration2);

        isSequenceTwoComplete = true;
      }
    }
  }

  Serial.println("Colour Sensor 1:");
  Serial.print("R min: ");
  Serial.println(blackRedCalibration1);
  Serial.print("R max: ");
  Serial.println(whiteRedCalibration1);

  Serial.print("G min: ");
  Serial.println(blackGreenCalibration1);
  Serial.print("G max: ");
  Serial.println(whiteGreenCalibration1);

  Serial.print("B min: ");
  Serial.println(blackBlueCalibration1);
  Serial.print("B max: ");
  Serial.println(whiteBlueCalibration1);

  Serial.println();

  Serial.println("Colour Sensor 2:");
  Serial.print("R min: ");
  Serial.println(blackRedCalibration2);
  Serial.print("R max: ");
  Serial.println(whiteRedCalibration2);

  Serial.print("G min: ");
  Serial.println(blackGreenCalibration2);
  Serial.print("G max: ");
  Serial.println(whiteGreenCalibration2);

  Serial.print("B min: ");
  Serial.println(blackBlueCalibration2);
  Serial.print("B max: ");
  Serial.println(whiteBlueCalibration2);
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
  Serial.println("Calibration Complete!");
}

// Read sensor values for each color and print them to serial monitor
void loop()
{
  int redIntensity1 = colSen1.readRed();
  int greenIntensity1 = colSen1.readGreen();
  int blueIntensity1 = colSen1.readBlue();

  int redConvert1 = map(redIntensity1, blackRedCalibration1, whiteRedCalibration1, 0, 255);
  int greenConvert1 = map(greenIntensity1, blackGreenCalibration1, whiteGreenCalibration1, 0, 255);
  int blueConvert1 = map(blueIntensity1, blackBlueCalibration1, whiteBlueCalibration1, 0, 255);

  Serial.print("Red1: ");
  Serial.println(constrain(redConvert1, 0, 255));
  Serial.print("Green1: ");
  Serial.println(constrain(greenConvert1, 0, 255));
  Serial.print("Blue1: ");
  Serial.println(constrain(blueConvert1, 0, 255));
  Serial.println();


  int redIntensity2 = colSen2.readRed();
  int greenIntensity2 = colSen2.readGreen();
  int blueIntensity2 = colSen2.readBlue();

  int redConvert2 = map(redIntensity2, blackRedCalibration2, whiteRedCalibration2, 0, 255);
  int greenConvert2 = map(greenIntensity2, blackGreenCalibration2, whiteGreenCalibration2, 0, 255);
  int blueConvert2 = map(blueIntensity2, blackBlueCalibration2, whiteBlueCalibration2, 0, 255);

  Serial.print("Red2: ");
  Serial.println(constrain(redConvert2, 0, 255));
  Serial.print("Green2: ");
  Serial.println(constrain(greenConvert2, 0, 255));
  Serial.print("Blue2: ");
  Serial.println(constrain(blueConvert2, 0, 255));
  Serial.println();

  delay(500);


}
