#ifndef LINE_FOLLOWING_H
#define LINE_FOLLOWING_H
#include <drv8833.h>
#include <ISL29125.h>

void lineFollowing(DRV8833 motor1,
                   DRV8833 motor2,
                   SFE_ISL29125 colSen1,
                   SFE_ISL29125 colSen2);

#endif