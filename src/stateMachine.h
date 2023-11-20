#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <drv8833.h>
#include "Adafruit_TCS34725.h"
#include <MPU6050.h>

typedef enum{
    IDLE = 0,
    INITIAL_APPROACH,
    FINAL_APPROACH,
    PICKUP,
    DROPOFF,
    RETURN_TO_HOME,
}state_e;

void runStateMachine();
void idleState();
void initialApproachState();
void finalApproachState();
void pickupState();
void dropoffState();
void returnToHomeState();


#endif