#include "lineFollowing.h"
#include "Arduino.h"
#include <Wire.h>
#include <ISL29125.h>
#include <drv8833.h>
#include <MPU6050.h>
#include "defines.h"
#include "math.h"
#include "stm32f4xx.h"

#define LEFT_START_SPEED 76.0f
#define RIGHT_START_SPEED 75.0f
float LEFT_BASE_SPEED = 63.0;
float RIGHT_BASE_SPEED = 64.0;
#define OFFSET 10
#define OFFSETG -5

// PID Constants
float Kp = 0.22;   // Proportional gain
float Ki = 0;      // Integral gain
float Kd = 0.0015; // Derivative gain

float KpGreen = 0.0007;
float errorGreen = 0;

// Variables
float error = 0;
float integral = 0;
float previous_error = 0;
float control_output = 0;
bool isBullsEyeDetected = 0;
bool first = 0;

// Sample time (adjust as needed)
float dt = 0.001; // 10ms sample time

// Function to compute control output
void PID_Controller()
{
    integral += error * dt;

    float derivative = (error - previous_error) / dt;

    control_output = Kp * error + Ki * integral + Kd * derivative;
    // Serial.print("Control Output: ");
    // Serial.print(control_output);
    // Serial.print(" Error: ");
    // Serial.println(error);

    // Update previous error for the next iteration
    previous_error = error;
}

// Function to read the sensor value (replace with your sensor reading code)
void ReadSensor(Adafruit_TCS34725 *colSen1,
                Adafruit_TCS34725 *colSen2)
{
    // take colour sensor readings
    float r1, g1, b1;
    float r2, g2, b2;

    colSen1->getRGB(&r1, &g1, &b1);
    colSen2->getRGB(&r2, &g2, &b2);

    float leftR = r1;
    float rightR = r2;

    Serial.println(g1-g2);

    if (110 < r1 && r1 < 130 && 70 < g1 && g1 < 85 && 50 < b1 && b1 < 80)
    {
        Serial.print("BULLSEYE DETECTED");
        Serial.print("      ");
        Serial.print(r1);
        isBullsEyeDetected = 1;
    }

    error = leftR - rightR + OFFSET;
    errorGreen = g1 - g2 + OFFSETG;
}

void BackwardMotorAdjustment(DRV8833 leftMotor,
                             DRV8833 rightMotor)
{

    //Adjust motor speed
    if (control_output > 0.0f) // left motor off line
    {
        leftMotor.drive(DRV8833_REVERSE, LEFT_BASE_SPEED + 1.1 * abs(control_output));
        rightMotor.drive(DRV8833_REVERSE, RIGHT_BASE_SPEED);
    }
    else if (control_output < 0.0f)
    {
        leftMotor.drive(DRV8833_REVERSE, LEFT_BASE_SPEED);
        rightMotor.drive(DRV8833_REVERSE, RIGHT_BASE_SPEED + abs(control_output));
    }
    else
    {
        leftMotor.drive(DRV8833_REVERSE, LEFT_BASE_SPEED);
        rightMotor.drive(DRV8833_REVERSE, RIGHT_BASE_SPEED);
    }
}

// Function to adjust the motor speed (replace with your motor control code)
void AdjustMotorSpeed(DRV8833 leftMotor,
                      DRV8833 rightMotor)
{
    // ramp up motor speed
    if (LEFT_BASE_SPEED < LEFT_START_SPEED)
    {
        LEFT_BASE_SPEED += 0.1f;
    }
    if (RIGHT_BASE_SPEED < RIGHT_START_SPEED)
    {
        RIGHT_BASE_SPEED += 0.1f;
    }

    // adjust motor speed
    if (control_output < 0.0f) // left motor off line
    {
        leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED + 1.1 * abs(control_output));
        rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
    }
    else if (control_output > 0.0f)
    {
        leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
        rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED + abs(control_output));
    }
    else
    {
        leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
        rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
    }
}
