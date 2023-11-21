#include "PID.h"
#include "defines.h"

float previousError = 0;
float integral = 0;

float getError(Adafruit_TCS34725* leftColour,
               Adafruit_TCS34725* rightColour)
{
    const float OFFSET = 8;

    float r1, g1, b1;
    float r2, g2, b2;

    leftColour->getRGB(&r1, &g1, &b1);
    rightColour->getRGB(&r2, &g2, &b2);

    return r1 - r2 + OFFSET;
}

float runPID(float error,
             float kp,
             float ki,
             float kd)
{   
    integral += error * (PID_DELAY_MS /1000.0f);

    float derivative = (error - previousError) / (PID_DELAY_MS / 1000.0f);

    float controlSignal = kp * error + ki * integral + kd * derivative;

    // Update previous error for the next iteration
    previousError = error;

    return controlSignal;
}

void updateMotorSpeed(DRV8833* leftMotor,
                       DRV8833* rightMotor,
                       float leftBaseSpeed,
                       float rightBaseSpeed,
                       float controlSignal)
{
    if (controlSignal < 0.0f) // left motor off line
    {
        leftMotor->drive(DRV8833_FORWARD, leftBaseSpeed + 1.1*abs(controlSignal));
        rightMotor->drive(DRV8833_FORWARD, rightBaseSpeed);
    }
    else //right motor off line
    {
        leftMotor->drive(DRV8833_FORWARD, leftBaseSpeed);
        rightMotor->drive(DRV8833_FORWARD, rightBaseSpeed + abs(controlSignal));
    }
}