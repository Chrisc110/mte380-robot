#include "stateMachine.h"
#include "helpers.h"
#include "PID.h"

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


#define PID_DELAY_MS 1

state_e state = IDLE;
uint32_t startTimeMs = 0;

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
    const uint32_t END_INITIAL_APPROACH_TIME = 3000;
    const float kp = 0;
    const float ki = 0;
    const float kd = 0;
    const float leftMaxSpeed = 75.0;
    const float rightMaxSpeed = 76.0f;

    /*
        NOTE: these variables are marked as static which means it retains
        its value between function calls, so the values do not reset to
        what it is intialized to below.  
    */
    static float leftBaseSpeed = 63.0f;
    static float rightBaseSpeed = 64.0f;
    
    //get error
    float error = getError(&leftColour, &rightColour);

    //run PID
    float controlSignal = runPID(error,  kp, ki, kd);

    //adjust motor speed
    updateMotorSpeed(&leftMotor, &rightMotor, leftBaseSpeed, rightBaseSpeed, controlSignal);

    //ramping of motor speed
    if (leftBaseSpeed < leftMaxSpeed) {leftBaseSpeed += 0.01;}
    if (rightBaseSpeed < rightMaxSpeed) {rightBaseSpeed += 0.01;}

    //delay 1ms
    if (millis() - startTimeMs > END_INITIAL_APPROACH_TIME)
    {
        state = FINAL_APPROACH;
    }

    delay(PID_DELAY_MS);
}

void finalApproachState()
{

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