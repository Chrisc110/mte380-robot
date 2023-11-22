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
    
    /*
        NOTE: keep in mind we are using the RIGHT_MAX_SPEED for both motors bec it is
        the larger of the two bec it would be messy to make a max for both and right
        now it is only 1 off.
    */
    const float MAX_CONTROL_SIGNAL = 100.0f - RIGHT_MAX_SPEED;
    
    float counterControl = 0.0f;

    // check to make sure we do not go over 100% motor signal
    if (abs(controlSignal) > MAX_CONTROL_SIGNAL)
    {
        // counter control equals the differnce between oversized control signal and max
        counterControl = abs(controlSignal) - MAX_CONTROL_SIGNAL;
        // the control signal is now set to the max, mutiplied by the sign of the original control signal
        controlSignal = MAX_CONTROL_SIGNAL * (controlSignal/abs(controlSignal));
    }


    if (controlSignal < 0.0f) // left motor off line
    {
        leftMotor->drive(DRV8833_FORWARD, leftBaseSpeed + 1.1*abs(controlSignal));
        rightMotor->drive(DRV8833_FORWARD, rightBaseSpeed - counterControl);
    }
    else //right motor off line
    {
        leftMotor->drive(DRV8833_FORWARD, leftBaseSpeed - counterControl);
        rightMotor->drive(DRV8833_FORWARD, rightBaseSpeed + abs(controlSignal));
    }
}