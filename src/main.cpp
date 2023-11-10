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

#include "stm32f4xx.h"

// PID Constants
float Kp = 1.0;  // Proportional gain
float Ki = 0.1;  // Integral gain
float Kd = 0.01; // Derivative gain

// Variables
float error = 0;
float integral = 0;
float previous_error = 0;

// Setpoint (target sensor value)
float setpoint = 500; // Adjust this to your desired setpoint

// Sample time (adjust as needed)
float dt = 0.01; // 10ms sample time

// Function to compute control output
float PID_Controller(float sensor_value)
{
  error = setpoint - sensor_value;

  integral += error * dt;

  float derivative = (error - previous_error) / dt;

  float control_signal = Kp * error + Ki * integral + Kd * derivative;

  // Update previous error for the next iteration
  previous_error = error;

  return control_signal;
}

// Function to read the sensor value (replace with your sensor reading code)
float ReadSensor()
{
  // Read the sensor value and return it
  // Replace this with your sensor reading code
  // Example: return analogRead(A0);
  // temporaility 
  return 1.0f;
}

// Function to adjust the motor speed (replace with your motor control code)
void AdjustMotorSpeed(float control_output)
{
  // Adjust the motor speed based on the control output
  // Replace this with your motor control code
  // Example: motorSpeed = baseSpeed + control_output * scaling_factor;
}


int main(void)
{
  // Initialize the STM32F4 hardware here

  // Main control loop
  while (1)
  {
    float sensor_value = ReadSensor();

    float control_output = PID_Controller(sensor_value);

    AdjustMotorSpeed(control_output);

    // Add a delay for the sample time
    HAL_Delay(dt);
  }
}

