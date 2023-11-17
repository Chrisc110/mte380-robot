#include "lineFollowing.h"
#include "Arduino.h"
#include <Wire.h>
#include <ISL29125.h>
#include <drv8833.h>
#include <MPU6050.h>
#include "defines.h"
#include "math.h"
#include "stm32f4xx.h"

#define LEFT_BASE_SPEED 67.0f
#define RIGHT_BASE_SPEED 66.0f
#define OFFSET 5

// PID Constants
float Kp = 1.0;  // Proportional gain
float Ki = 0.1;  // Integral gain
float Kd = 0.01; // Derivative gain

// Variables
float error = 0;
float integral = 0;
float previous_error = 0;
float control_output = 0;

// Setpoint (target sensor value)
float setpoint = 500; // Adjust this to your desired setpoint

// Sample time (adjust as needed)
float dt = 0.01; // 10ms sample time

// Function to compute control output
void PID_Controller()
{
    integral += error * dt;

    float derivative = (error - previous_error) / dt;

    control_output = Kp * error + Ki * integral + Kd * derivative;

    // Update previous error for the next iteration
    previous_error = error;
}

// Function to read the sensor value (replace with your sensor reading code)
void ReadSensor(SFE_ISL29125 *colSen1,
                 SFE_ISL29125 *colSen2)
{
    // take colour sensor readings
    uint8_t left = colSen1->readRedRGB();
    uint8_t right = colSen2->readRedRGB();
    error = left - right + OFFSET;
}

// Function to adjust the motor speed (replace with your motor control code)
void AdjustMotorSpeed(DRV8833 leftMotor,
                      DRV8833 rightMotor)
{
    // adjust motor speed
    if (error > 1.0f) // left motor off line
    {
        leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED + control_output);
        rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
    }
    else if (error < -1.0f)
    {
        leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
        rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED + control_output);
    }
    else
    {
        leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
        rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
    }
}
