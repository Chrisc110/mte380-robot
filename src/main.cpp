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

#define YAW_SCALING_FACTOR 26.54

// Instantiate colour sensors
TwoWire colSenWire1(COL_SEN_SDA_1, COL_SEN_SCL_1);
TwoWire colSenWire2(COL_SEN_SDA_2, COL_SEN_SCL_2);
SFE_ISL29125 colSen1(ISL_I2C_ADDR, colSenWire1);
SFE_ISL29125 colSen2(ISL_I2C_ADDR, colSenWire2);

// Instantiate motors
DRV8833 motor1(MOTOR1_IN1, MOTOR1_IN2);
DRV8833 motor2(MOTOR2_IN1, MOTOR2_IN2);

// Instantiate IMU
MPU6050 imu;

bool isStop = true;

void turn(float degrees, float speed1, float speed2)
{
  MPU6050Data data;
  float theta = 0;
  uint32_t lastReadTime = 0;
  drv8833_dir_e dir1 = degrees > 0 ? DRV8833_FORWARD : DRV8833_REVERSE;
  drv8833_dir_e dir2 = degrees > 0 ? DRV8833_REVERSE : DRV8833_FORWARD;
  motor1.drive(dir1, speed1);
  motor2.drive(dir2, speed2);

  while (abs(theta) * YAW_SCALING_FACTOR < abs(degrees))
  {
    imu.getAll(&data);
    theta = (theta + data.gyroZ * 100.0f / 1000000.0f);
    if (millis() - lastReadTime > 100)
    {
      Serial.print("theta ");
      Serial.println(abs(theta * YAW_SCALING_FACTOR));

      lastReadTime = millis();
    }
    delayMicroseconds(100);
  }

  // motor1.stop();
  // motor2.stop();
}

void demoSequence()
{
  // 1 - 78, 2- 80
  // rampDrive(motor1, DRV8833_FORWARD, 0.0f, 68.0f, motor2, DRV8833_FORWARD, 0.0f, 70.0f);
  // delay(2000);

  // detect red

  // Do 360 turn
  turn(90.0f, 68.0f, 70.0f);
  motor1.stop();
  motor2.stop();

  // drive backwards
  // rampDrive(motor1, DRV8833_REVERSE, 0.0f, 68.0f, motor2, DRV8833_REVERSE, 0.0f, 70.0f);
}

void check_red()
{
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

  imu.init();

  Serial.println("Motor 1 Initialization: SUCCESSFUL");
  Serial.println("Motor 2 Initialization: SUCCESSFUL");
}

// Read sensor values for each color and print them to serial monitor
void loop()
{

  if (digitalRead(USER_BTN) == 0)
  {
    delay(100);
    if (digitalRead(USER_BTN) == 0)
    {
      if (isStop == true)
      {
        isStop = false;
        delay(1000);
        demoSequence();
      }
      else
      {
        // isStop = true;
        // motor1.stop();
        // motor2.stop();
      }
    }
  }

  digitalToggle(LED_BUILTIN);
}
