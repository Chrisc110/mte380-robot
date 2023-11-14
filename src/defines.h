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

#define C1_R_MIN 135
#define C1_R_MAX 1404
#define C1_G_MIN 302
#define C1_G_MAX 2336
#define C1_B_MIN 340
#define C1_B_MAX 2741

#define C2_R_MIN 106
#define C2_R_MAX 1158
#define C2_G_MIN 260
#define C2_G_MAX 2126
#define C2_B_MIN 254
#define C2_B_MAX 2180


/******************** Motors ***********************/
#define MOTOR1_IN1 3
#define MOTOR1_IN2 6
#define MOTOR2_IN1 9
#define MOTOR2_IN2 10

/********************** IMU ************************/
#define YAW_SCALING_FACTOR 26.54

#endif