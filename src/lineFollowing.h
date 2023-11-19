#ifndef LINE_FOLLOWING_H
#define LINE_FOLLOWING_H
#include <drv8833.h>
#include <ISL29125.h>
#include "Adafruit_TCS34725.h"

void lineFollowing(DRV8833 motor1,
                   DRV8833 motor2,
                   Adafruit_TCS34725 *colSen1,
                   Adafruit_TCS34725 *colSen2);

void ReadSensor(Adafruit_TCS34725 *colSen1,
                Adafruit_TCS34725 *colSen2);

void AdjustMotorSpeed(DRV8833 leftMotor,
                      DRV8833 rightMotor);

void PID_Controller();


#endif