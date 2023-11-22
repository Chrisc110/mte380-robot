#ifndef HELPERS_H
#define HELPERS_H

#include "Adafruit_TCS34725.h"
#include <MPU6050.h>
#include <drv8833.h>

bool isButtonPressed();

bool isOverBullsEye(Adafruit_TCS34725* leftColour,
                    Adafruit_TCS34725* rightColour);
bool isOverHome(Adafruit_TCS34725* leftColour,
                    Adafruit_TCS34725* rightColour);
bool isOverSafezone(Adafruit_TCS34725* leftColour,
                    Adafruit_TCS34725* rightColour);
bool isOverLine(Adafruit_TCS34725* leftColour,
                    Adafruit_TCS34725* rightColour);

typedef enum{
  CLOCKWISE = 0,
  COUNTER_CLOCKWISE
} rotation_dir_e;

void rotateInPlace(rotation_dir_e dir,
                   float deg,
                   MPU6050* imu,
                   DRV8833* leftMotor,
                   DRV8833* rightMotor);
#endif