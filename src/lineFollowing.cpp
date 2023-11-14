#include "lineFollowing.h"
#include "Arduino.h"

#define M1_BASE_SPEED 60.0f
#define M2_BASE_SPEED 62.0f
#define P_GAIN 8.0f
#define M1_MAX_SPEED 70.0f
#define M2_MAX_SPEED 70.0f

void lineFollowing(DRV8833 motor1,
                   DRV8833 motor2)
{
    //start off by going the base speed
    motor1.drive(DRV8833_FORWARD, M1_BASE_SPEED);
    motor2.drive(DRV8833_FORWARD, M1_BASE_SPEED);

    //this is our control loop
    while(1)
    {
        //take colour sensor readings
         


        //determine error

        //determine which motor to increase speed

        //multiply error by gain

        //add error*gain to proper motor output
    }

}