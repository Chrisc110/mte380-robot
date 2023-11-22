#ifndef DEFINES_H
#define DEFINES_H

/**************** Colour Sensors *****************/
#define COL_SEN_SDA_1 PC9
#define COL_SEN_SCL_1 PA8
#define COL_SEN_SDA_2 PB9
#define COL_SEN_SCL_2 PB8

#define COL_SEN_ADC_1 A0
#define COL_SEN_ADC_2 A1
#define COL_SEN_RED 11
#define COL_SEN_GREEN 12
#define COL_SEN_BLUE 13

/******************** Motors ***********************/
#define MOTOR1_IN1 3
#define MOTOR1_IN2 6
#define MOTOR2_IN1 9
#define MOTOR2_IN2 10

/********************** IMU ************************/
#define YAW_SCALING_FACTOR 26.54

#define PID_DELAY_MS 1

#define LEFT_MIN_SPEED 63.0f
#define RIGHT_MIN_SPEED 64.0f
#define LEFT_MAX_SPEED 74.0f
#define RIGHT_MAX_SPEED 75.0f

#endif