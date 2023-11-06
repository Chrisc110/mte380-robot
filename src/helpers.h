#ifndef HELPERS_H
#define HELPER_H
#include <drv8833.h>

void rampDrive(DRV8833 motor1,
               drv8833_dir_e dir1,
               float startingSpeed1,
               float finalSpeed1,
               DRV8833 motor2,
               drv8833_dir_e dir2,
               float startingSpeed2,
               float finalSpeed2);

#endif  