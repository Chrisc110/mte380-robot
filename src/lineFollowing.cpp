#include "lineFollowing.h"
#include "Arduino.h"

#define LEFT_BASE_SPEED 63.0f
#define RIGHT_BASE_SPEED 63.0f
#define P_GAIN_RIGHT 0.3f
#define P_GAIN_LEFT 0.3f
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
    float redL = 0;
    float redR = 0;
    for (int i = 0; i < 10; i++)
    {
        redL += 0.1*colSen1->readRedRGB();
        redR += 0.1*colSen2->readRedRGB();
    }
    float redAverageL = redL;
    float redAverageR = redR;
    //this is our control loop
    while(1)
    {
        //take colour sensor readings
        redL = colSen1->readRedRGB();
        redR = colSen2->readRedRGB();

        //determine error
        float redErrorL = redL-redAverageL;
        float redErrorR = redR - redAverageR;
        float error = redErrorL - redErrorR;
        Serial.println(error);
        

        // if (redErrorL > LEFT_GREEN_THRESH && redErrorR > RIGHT_GREEN_THRESH)
        // {
        //     //do nothing
        //     state = state;
        //     digitalWrite(LED_BUILTIN, HIGH);
        // }
        if (error > 0)
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
            redAverageL = redAverageL*0.95+redL*0.05;
            redAverageR = redAverageR*0.95+redR*0.05;

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