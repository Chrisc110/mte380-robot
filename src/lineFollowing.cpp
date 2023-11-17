#include "lineFollowing.h"
#include "Arduino.h"

#define LEFT_BASE_SPEED 61.0f
#define RIGHT_BASE_SPEED 61.0f
#define P_GAIN_RIGHT 0.4f
#define P_GAIN_LEFT 0.4f
#define M1_MAX_SPEED 70.0f
#define M2_MAX_SPEED 70.0f

#define RED_OFFSET 10.0f

#define LEFT_GREEN_THRESH 60
#define RIGHT_GREEN_THRESH 60

typedef enum{
    LEFT = 0,
    RIGHT,
    STRAIGHT
} dir_e;

void lineFollowing(DRV8833 leftMotor,
                   DRV8833 rightMotor,
                   SFE_ISL29125 *colSen1,
                   SFE_ISL29125 *colSen2)
{
    //start off by going the base speed
    dir_e state = STRAIGHT;

    //this is our control loop
    while(1)
    {
        //take colour sensor readings
        uint8_t leftRed = colSen1->readRedRGB();
        uint8_t leftGreen = colSen1->readGreenRGB();
        uint8_t rightRed = colSen2->readRedRGB();
        uint8_t rightGreen = colSen2->readGreenRGB();

        //determine error
        float error = leftRed - rightRed + RED_OFFSET;
        Serial.println(error);

        if (leftGreen > LEFT_GREEN_THRESH && rightGreen > RIGHT_GREEN_THRESH)
        {
            //do nothing
            state = state;
            digitalWrite(LED_BUILTIN, HIGH);
        }
        else if (error > 0)
        {
            state = LEFT;
            digitalWrite(LED_BUILTIN, LOW);

        }
        else if (error < 0)
        {
            state = RIGHT;
            digitalWrite(LED_BUILTIN, LOW);

        }
        else
        {
            state = STRAIGHT;
            digitalWrite(LED_BUILTIN, LOW);

        }

        //adjust motor speed        
        if (state == LEFT) //left motor off line
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED + P_GAIN_LEFT*error);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
        }
        else if (state == RIGHT)
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED - P_GAIN_RIGHT*error);
        }
        else
        {
            leftMotor.drive(DRV8833_FORWARD, LEFT_BASE_SPEED);
            rightMotor.drive(DRV8833_FORWARD, RIGHT_BASE_SPEED);
        }
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