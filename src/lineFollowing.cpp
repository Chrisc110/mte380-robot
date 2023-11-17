#include "lineFollowing.h"
#include "Arduino.h"
#include <Wire.h>
#include <ISL29125.h>
#include <drv8833.h>
#include <MPU6050.h>
#include "defines.h"
#include "math.h"
#include "stm32f4xx.h"

#define LEFT_BASE_SPEED 63.0f
#define RIGHT_BASE_SPEED 64.0f
#define OFFSET -5

// PID Constants
float Kp = 0.13;  // Proportional gain
float Ki = 0;  // Integral gain
float Kd = 0.0005; // Derivative gain

// Variables
float error = 0;
float integral = 0;
float previous_error = 0;
float control_output = 0;

// Setpoint (target sensor value)
float setpoint = 500; // Adjust this to your desired setpoint

// Sample time (adjust as needed)
float dt = 0.001; // 10ms sample time

// Function to compute control output
void PID_Controller()
{
    integral += error * dt;

    float derivative = (error - previous_error) / dt;

    control_output = Kp * error + Ki * integral + Kd * derivative;
    Serial.print("Control Output: ");
    Serial.print(control_output);
    Serial.print(" Error: ");
    Serial.println(error);

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
    // if(right > 100 && left > 100) {
    //     error = -previous_error;
    // } else {
        error = left - right + OFFSET;
    // }
}

// Function to adjust the motor speed (replace with your motor control code)
void AdjustMotorSpeed(DRV8833 leftMotor,
                      DRV8833 rightMotor)
{
    // adjust motor speed
    if (control_output > 0.0f) // left motor off line
    {
        leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED + abs(control_output));
        rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
    }
    else if (control_output < 0.0f)
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
