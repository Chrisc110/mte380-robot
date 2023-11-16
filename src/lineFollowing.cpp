#include "lineFollowing.h"
#include "Arduino.h"

#define LEFT_BASE_SPEED 68.0f
#define RIGHT_BASE_SPEED 68.0f
#define P_GAIN 15.0f
#define M1_MAX_SPEED 70.0f
#define M2_MAX_SPEED 70.0f

#define OFFSET -5.0f

void lineFollowing(DRV8833 leftMotor,
                   DRV8833 rightMotor,
                   SFE_ISL29125 *colSen1,
                   SFE_ISL29125 *colSen2)
{
    //start off by going the base speed
    leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
    rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);

    //this is our control loop
    while(1)
    {
        //take colour sensor readings
        uint32_t first = micros();
        uint8_t left = colSen1->readRedRGB();
        uint8_t right = colSen2->readRedRGB();

        //determine error
        float error = left - right + OFFSET;
        // Serial.println(error);

        //adjust motor speed        
        if (error > 3.0f) //left motor off line
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED + P_GAIN);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
        }
        else if (error < -3.0f)
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED + P_GAIN);
        }
        else
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
        }
        uint32_t second = micros();
        Serial.println(second-first);
    }

}

// off the line
// Red 1: 109
// Green 1: 92
// Blue 1: 35
// Red 2: 109
// Green 2: 80
// Blue 2: 51

// on the line
// Red 1: 95
// Green 1: 69
// Blue 1: 22
// Red 2: 80
// Green 2: 36
// Blue 2: 22

//colour sensor: 976 us
//entire loop: 1026 us