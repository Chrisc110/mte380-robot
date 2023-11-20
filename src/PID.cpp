#include "PID.h"

float getError(Adafruit_TCS34725* leftColour,
               Adafruit_TCS34725* rightColour)
{

}

float runPID(float error,
             float kp,
             float ki,
             float kd)
{

}

void updateMotorSpeed(DRV8833* leftMotor,
                       DRV8833* rightMotor,
                       float leftBaseSpeed,
                       float rightBaseSpeed,
                       float controlSignal)
{
    if (controlSignal < 0.0f) // left motor off line
    {
        leftMotor->drive(DRV8833_FORWARD, leftBaseSpeed + 1.1 * abs(controlSignal));
        rightMotor->drive(DRV8833_FORWARD, rightBaseSpeed);
    }
    else //right motor off line
    {
        leftMotor->drive(DRV8833_FORWARD, leftBaseSpeed);
        rightMotor->drive(DRV8833_FORWARD, rightBaseSpeed + abs(controlSignal));
    }
}