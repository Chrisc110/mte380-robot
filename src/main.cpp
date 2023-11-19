#include <Wire.h>
#include <ISL29125.h>
#include <drv8833.h>
#include <MPU6050.h>
#include "defines.h"
#include "math.h"
#include "lineFollowing.h"
#include "Adafruit_TCS34725.h"

// Instantiate colour sensors: Please match colSen1 and motor1 to the same side!
TwoWire colSenWire1(COL_SEN_SDA_1, COL_SEN_SCL_1);
TwoWire colSenWire2(COL_SEN_SDA_2, COL_SEN_SCL_2);
Adafruit_TCS34725 colSen1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_60X);
Adafruit_TCS34725 colSen2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_60X);

// Instantiate motors:
DRV8833 motor1(MOTOR1_IN1, MOTOR1_IN2);
DRV8833 motor2(MOTOR2_IN1, MOTOR2_IN2);

// Instantiate IMU
// MPU6050 imu;

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(USER_BTN, INPUT);

  // Initialize the TCS34725 with simple configuration so it starts sampling
  if (colSen1.begin(TCS34725_ADDRESS, &colSenWire1))
  {
    Serial.println("Colour Sensor 1 Initialization: SUCCESSFUL");
  }
  else
  {
    Serial.println("Colour Sensor 1 Initialization: FAILED");
  }

  if (colSen2.begin(TCS34725_ADDRESS, &colSenWire2))
  {
    Serial.println("Colour Sensor 2 Initialization: SUCCESSFUL");
  }
  else
  {
    Serial.println("Colour Sensor 2 Initialization: FAILED");
  }

  // imu.init();
  // Serial.println("IMU Initialization: SUCCESSFUL");

  Serial.println("Motor 1 Initialization: SUCCESSFUL");
  Serial.println("Motor 2 Initialization: SUCCESSFUL");
}

// Read sensor values for each color and print them to serial monitor
void loop()
{

  float r1, g1, b1;
  float r2, g2, b2;

  colSen1.getRGB(&r1, &g1, &b1);
  colSen2.getRGB(&r2, &g2, &b2);

  Serial.print("Red 1: ");
  Serial.println(r1);
  Serial.print("Green 1: ");
  Serial.println(g1);
  Serial.print("Blue 1: ");
  Serial.println(b1);
  Serial.print("Red 2: ");
  Serial.println(r2);
  Serial.print("Green 2: ");
  Serial.println(g2);
  Serial.print("Blue 2: ");
  Serial.println(b2);
  Serial.println();
  delay(500);

  if (digitalRead(USER_BTN) == 0)
  {
    delay(100);
    if (digitalRead(USER_BTN) == 0)
    {
      while (1)
      {
        ReadSensor(&colSen1, &colSen2);

        PID_Controller();

        AdjustMotorSpeed(motor1, motor2);

        // Add a delay for the sample time
        // needs to be the same as the value in linefollowing.cpp
        delay(1);
      }
    }
  }
}
