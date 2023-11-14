#include "lineFollowing.h"
#include "Arduino.h"

#define LEFT_BASE_SPEED 60.0f
#define RIGHT_BASE_SPEED 62.0f
#define P_GAIN 8.0f
#define M1_MAX_SPEED 70.0f
#define M2_MAX_SPEED 70.0f

#define OFFSET 5.0f

void lineFollowing(DRV8833 leftMotor,
                   DRV8833 rightMotor,
                   SFE_ISL29125 colSen1,
                   SFE_ISL29125 colSen2)
{
    //start off by going the base speed
    leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
    rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);

    //this is our control loop
    while(1)
    {
        //take colour sensor readings
         uint8_t left = colSen1.readRedRGB();
         uint8_t right = colSen2.readRedRGB();

        //determine error
        float error = left - right + OFFSET;

        //adjust motor speed        
        if (error < -5.0f) //left motor off line
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED + P_GAIN);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
        }
        else if (error > 5.0f)
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED + P_GAIN);
        }
        else
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
        }
    }

}