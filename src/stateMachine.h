#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <drv8833.h>
#include "Adafruit_TCS34725.h"
#include <MPU6050.h>

typedef enum{
    INIT = 0,
    INITIAL_APPROACH,
    FINAL_APPROACH,
    PICKUP,
    DROPOFF,
    RETURN_TO_HOME,
}state_e;

void runStateMachine(DRV8833* leftMotor,
                     DRV8833* rightMotor,
                     Adafruit_TCS34725* leftColour,
                     Adafruit_TCS34725* rightColour,
                     MPU6050* imu);


#endif