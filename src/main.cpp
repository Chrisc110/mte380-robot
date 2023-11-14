#include <Wire.h>
#include <ISL29125.h>
#include <drv8833.h>
#include <MPU6050.h>
#include "defines.h"
#include "math.h"

// Instantiate colour sensors: Please match colSen1 and motor1 to the same side!
TwoWire colSenWire1(COL_SEN_SDA_1, COL_SEN_SCL_1);
TwoWire colSenWire2(COL_SEN_SDA_2, COL_SEN_SCL_2);
SFE_ISL29125 colSen1(ISL_I2C_ADDR, colSenWire1);
SFE_ISL29125 colSen2(ISL_I2C_ADDR, colSenWire2);

// Instantiate motors:
DRV8833 motor1(MOTOR1_IN1, MOTOR1_IN2);
DRV8833 motor2(MOTOR2_IN1, MOTOR2_IN2);

// Instantiate IMU
MPU6050 imu;

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(USER_BTN, INPUT);

  // Initialize the ISL29125 with simple configuration so it starts sampling
  if (colSen1.init(C1_R_MIN, C1_R_MAX, C1_G_MIN, C1_G_MAX, C1_B_MIN, C1_B_MAX))
  {
    Serial.println("Colour Sensor 1 Initialization: SUCCESSFUL");
  }
  else
  {
    Serial.println("Colour Sensor 1 Initialization: FAILED");
  }

  if (colSen2.init(C2_R_MIN, C2_R_MAX, C2_G_MIN, C2_G_MAX, C2_B_MIN, C2_B_MAX))
  {
    Serial.println("Colour Sensor 2 Initialization: SUCCESSFUL");
  }
  else
  {
    Serial.println("Colour Sensor 2 Initialization: FAILED");
  }

  imu.init();
  Serial.println("IMU Initialization: SUCCESSFUL");

  Serial.println("Motor 1 Initialization: SUCCESSFUL");
  Serial.println("Motor 2 Initialization: SUCCESSFUL");
}

// Read sensor values for each color and print them to serial monitor
void loop()
{
  
  // if (digitalRead(USER_BTN) == 0)
  // {
  //   delay(100);
  //   if (digitalRead(USER_BTN) == 0)
  //   {
  //     lineFollowing(motor1, motor2);
  //   }
  // }

  Serial.print("Red1: ");
  Serial.println(colSen1.readRedRGB());
  Serial.print("Green1: ");
  Serial.println(colSen1.readGreenRGB());
  Serial.print("Blue1: ");
  Serial.println(colSen1.readBlueRGB());
  Serial.print("Red2: ");
  Serial.println(colSen2.readRedRGB());
  Serial.print("Green2: ");
  Serial.println(colSen2.readGreenRGB());
  Serial.print("Blue2: ");
  Serial.println(colSen2.readBlueRGB());
  Serial.println();
  delay(500);

}
