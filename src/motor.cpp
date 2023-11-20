#include "motor.h"
#include "Arduino.h"

void rampDrive(DRV8833 motor1,
               drv8833_dir_e dir1,
               float startingSpeed1,
               float finalSpeed1,
               DRV8833 motor2,
               drv8833_dir_e dir2,
               float startingSpeed2,
               float finalSpeed2)
{
    float step1 = finalSpeed1 / 50.0f;
    float step2 = finalSpeed2 / 50.0f;
    const uint32_t ITERATION_DELAY_MS = 10;

    for(float i = 0.0; i < 50.0; i++)
    {
        motor1.drive(dir1, step1*i);
        motor2.drive(dir2, step2*i);
        delay(ITERATION_DELAY_MS);
    }
}