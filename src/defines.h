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

#define C1_R_MIN 161
#define C1_R_MAX 1661
#define C1_G_MIN 315
#define C1_G_MAX 2660
#define C1_B_MIN 370
#define C1_B_MAX 3153

#define C2_R_MIN 147
#define C2_R_MAX 1512
#define C2_G_MIN 329
#define C2_G_MAX 2866
#define C2_B_MIN 342
#define C2_B_MAX 2972


/******************** Motors ***********************/
#define MOTOR1_IN1 3
#define MOTOR1_IN2 6
#define MOTOR2_IN1 9
#define MOTOR2_IN2 10

/********************** IMU ************************/
#define YAW_SCALING_FACTOR 26.54

#endif