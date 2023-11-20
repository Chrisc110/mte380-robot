#include "stateMachine.h"

state_e state = INIT;

void runStateMachine(DRV8833* leftMotor,
                     DRV8833* rightMotor,
                     Adafruit_TCS34725* leftColour,
                     Adafruit_TCS34725* rightColour,
                     MPU6050* imu)
{
    switch(state)
    {
        case INIT:
            break;

        case INITIAL_APPROACH:
            break;

        case FINAL_APPROACH:
            break;
        
        case PICKUP:
            break;

        case DROPOFF:
            break;

        case RETURN_TO_HOME:
            break;
    }
    
}