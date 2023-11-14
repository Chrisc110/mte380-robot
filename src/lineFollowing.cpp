#include "lineFollowing.h"
#include "Arduino.h"

#define M1_BASE_SPEED 50.0f
#define M2_BASE_SPEED 50.0
#define P_GAIN 0.5f
#define M1_MAX_SPEED 60.0f
#define M2_MAX_SPEED

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