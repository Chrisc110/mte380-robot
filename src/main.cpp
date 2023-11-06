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

DRV8833 motor1(MOTOR1_IN1, MOTOR1_IN2);
DRV8833 motor2(MOTOR2_IN1, MOTOR2_IN2);

bool isStop = true;
void rampDrive(drv8833_dir_e dir, float finalSpeed1, float finalSpeed2)
{
  float step1 = finalSpeed1 / 50.0f;
  float step2 = finalSpeed2 / 50.0f;

  for(float i = 0.0; i < 50.0; i++)
  {
    motor1.drive(dir, step1*i);
    motor2.drive(dir, step2*i);
    delay(10);
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

  Serial.println("Motor 1 Initialization: SUCCESSFUL");
  Serial.println("Motor 2 Initialization: SUCCESSFUL");

}

// Read sensor values for each color and print them to serial monitor
void loop()
{

  if (digitalRead(USER_BTN) == 0)
  {
    delay(25);
    if (digitalRead(USER_BTN) == 0)
    {
      if(isStop == true)
      {
        isStop = false;
        delay(1000);
        rampDrive(DRV8833_FORWARD, 78.0f, 80.0f);
      }
      else
      {
        isStop = true;
        motor1.stop();
        motor2.stop();
        delay(750);
      }
    }
  }

  digitalToggle(LED_BUILTIN);

}
