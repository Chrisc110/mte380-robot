#ifndef PID_H
#define PID_H

#include "Adafruit_TCS34725.h"
#include <drv8833.h>

float getError(Adafruit_TCS34725* leftColour,
               Adafruit_TCS34725* rightColour);

float runPID(float error,
             float kp,
             float ki,
             float kd);

void updateMotorSpeed(DRV8833* leftMotor,
                       DRV8833* rightMotor,
                       float leftBaseSpeed,
                       float rightBaseSpeed,
                       float controlSignal);



#endif