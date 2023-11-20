#include "stateMachine.h"
#include "helpers.h"
#include "PID.h"
#include "defines.h"

/***************Externed Variables****************/
// These variables are externed from main so we can use them here
extern Adafruit_TCS34725 leftColour;
extern Adafruit_TCS34725 rightColour;

// Instantiate motors:
extern DRV8833 leftMotor;
extern DRV8833 rightMotor;

// Instantiate IMU
extern MPU6050 imu;
/*************************************************/


#define LEFT_MIN_SPEED 63.0f
#define RIGHT_MIN_SPEED 64.0f
#define LEFT_MAX_SPEED 75.0f
#define RIGHT_MAX_SPEED 76.0f

state_e state = IDLE;
uint32_t startTimeMs = 0;
float leftBaseSpeed = LEFT_MIN_SPEED;
float rightBaseSpeed = RIGHT_MIN_SPEED;


void runStateMachine()
{
    switch(state)
    {
        case IDLE:
            idleState();
            break;

        case INITIAL_APPROACH:
            initialApproachState();
            break;

        case FINAL_APPROACH:
            finalApproachState();
            break;
        
        case PICKUP:
            pickupState();
            break;

        case DROPOFF:
            dropoffState();
            break;

        case RETURN_TO_HOME:
            returnToHomeState();
            break;
    }
    
}

void idleState()
{
    if (isButtonPressed())
    {
        delay(500);
        startTimeMs = millis();
        state = INITIAL_APPROACH;
    }
}

void initialApproachState()
{
    const uint32_t END_INITIAL_APPROACH_TIME_MS = 3000;
    const float KP = 0.22;
    const float KD = 0;
    const float KI = 0.0015;
    
    //get error
    float error = getError(&leftColour, &rightColour);

    //run PID
    float controlSignal = runPID(error,  KP, KI, KD);

    //adjust motor speed
    updateMotorSpeed(&leftMotor, &rightMotor, leftBaseSpeed, rightBaseSpeed, controlSignal);

    //ramping of motor speed
    if (leftBaseSpeed < LEFT_MAX_SPEED) {leftBaseSpeed += 0.1;}
    if (rightBaseSpeed < RIGHT_MAX_SPEED) {rightBaseSpeed += 0.1;}

    if (millis() - startTimeMs > END_INITIAL_APPROACH_TIME_MS)
    {   
        state = FINAL_APPROACH;
    }

    delay(PID_DELAY_MS);
}

void finalApproachState()
{
    const float KP = 0.22;
    const float KD = 0;
    const float KI = 0.0015;

    float error = getError(&leftColour, &rightColour);

    //run PID
    float controlSignal = runPID(error,  KP, KI, KD);

    //adjust motor speed
    updateMotorSpeed(&leftMotor, &rightMotor, leftBaseSpeed, rightBaseSpeed, controlSignal);
    
    if (leftBaseSpeed > LEFT_MIN_SPEED) {leftBaseSpeed -= 0.3;}
    if (rightBaseSpeed > RIGHT_MIN_SPEED) {rightBaseSpeed -= 0.3;}

    if (isOverBullsEye(&leftColour, &rightColour))
    {
        leftMotor.stop();
        rightMotor.stop();
        state = PICKUP;
    }

    delay(PID_DELAY_MS);
}

void pickupState()
{

}

void dropoffState()
{

}

void returnToHomeState()
{

}