#include <Wire.h>
#include <drv8833.h>
#include <MPU6050.h>
#include "defines.h"
#include "math.h"
#include "Adafruit_TCS34725.h"
#include "stateMachine.h"
#include "Servo.h"

// Instantiate colour sensors: Please match colSen1 and motor1 to the same side!
TwoWire leftWire(COL_SEN_SDA_1, COL_SEN_SCL_1);
// TwoWire colSenWire2(COL_SEN_SDA_2, COL_SEN_SCL_2); keep this uncommented bec the colour sensor and IMU will use "Wire"

Adafruit_TCS34725 leftColour = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_60X);
Adafruit_TCS34725 rightColour = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_60X);

// Instantiate motors:
DRV8833 leftMotor(MOTOR1_IN1, MOTOR1_IN2);
DRV8833 rightMotor(MOTOR2_IN1, MOTOR2_IN2);

// Instantiate IMU
MPU6050 imu;

// Gripper Servo
Servo servo;

void setup()
{
  bool success = true;
  
  // Initialize serial communication
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(USER_BTN, INPUT);

  // Initialize the TCS34725 with simple configuration so it starts sampling
  if (leftColour.begin(TCS34725_ADDRESS, &leftWire))
  {
    Serial.println("Colour Sensor 1 Initialization: SUCCESSFUL");
  }
  else
  {
    success = false;
    Serial.println("Colour Sensor 1 Initialization: FAILED");
  }
  if (rightColour.begin(TCS34725_ADDRESS, &Wire))
  {
    Serial.println("Colour Sensor 2 Initialization: SUCCESSFUL");
  }
  else
  {
    success = false;
    Serial.println("Colour Sensor 2 Initialization: FAILED");
  }

  //NOTE: IMU must be initialized AFTER colour sensor
  if (imu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  { 
    imu.calibrateGyro();
    Serial.println("IMU Initialization: SUCCESSFUL");
    
  }
  else
  {
    success = false;
    Serial.println("IMU Initialization: FAILED");
  }

  servo.attach(11);
  Serial.println("Servo Motor Initialization: SUCCESSFUL");

  Serial.println("Motor 1 Initialization: SUCCESSFUL");
  Serial.println("Motor 2 Initialization: SUCCESSFUL");

  // Check the if the init was successful
  if (success)
  {
    // solid green means SUCCESS
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    while(1)
    {
      // Toggling light means FAILED
      digitalToggle(LED_BUILTIN);
      delay(250);
    }
  }
}

// Read sensor values for each color and print them to serial monitor
void loop()
{
  runStateMachine();
}
