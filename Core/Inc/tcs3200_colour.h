#ifndef TCS3200_COLOUR_H_
#define TCS3200_COLOUR_H_

#include "stm32f4xx_hal.h"
#include "stdint.h"

typedef struct{
    uint16_t t1;
    uint16_t t2;
    uint16_t isFirst;
    uint16_t freq;
} tcs3200_int_data_t;

typedef struct{
    GPIO_TypeDef* s0Port;       //Output freq scaling selection bit 0
    uint16_t      s0Pin;

    GPIO_TypeDef* s1Port;       //Output freq scaling selection bit 1
    uint16_t      s1Pin;

    GPIO_TypeDef* s2Port;       //Photodiode type selection bit 0
    uint16_t      s2Pin;

    GPIO_TypeDef* s3Port;       //Photodiode type selection bit 1
    uint16_t      s3Pin;

    TIM_HandleTypeDef* tim;     //Timer used to measure the square wave frequency
    uint32_t timChannel;        //Timer channel

    tcs3200_int_data_t intData; //Data type to hold the interrupt timer data, USER DO NOT MODIFY

} tcs3200_colour_handle_t;

typedef enum{
    RED = 0,
    GREEN,
    BLUE,
    CLEAR
} tcs3200_colour_e;

typedef enum{
    TCS3200_NO_ERROR = 0,
    TCS3200_ERROR,
    TCS3200_INVALID_PARAMETER
} tcs3200_status_e;

/// @brief do some initialization
/// @param colSensor colour sensor handle
/// @return tcs3200 status code
tcs3200_status_e tcs3200_init(tcs3200_colour_handle_t* colSensor);

/// @brief enable the timer input capture interrupt
/// @param colSensor colour sensor handle
/// @return tcs3200 status code
tcs3200_status_e tsc3200_start(tcs3200_colour_handle_t* colSensor);

/// @brief disable the timer input capture interrupt
/// @param colSensor colour sensor handle
/// @return tcs3200 status code
tcs3200_status_e tsc3200_stop(tcs3200_colour_handle_t* colSensor);

/// @brief sets the s2 and s3 control bits to set the colour to read
/// @param colSensor colour sensor handle
/// @param colour desired colour to read
/// @return tcs3200 status code
tcs3200_status_e tcs3200_select_colour(tcs3200_colour_handle_t* colSensor, tcs3200_colour_e colour);

/// @brief reads the most recent colour reading
/// @param colSensor colour sensor handle
/// @return frequency of the square wave, in Hz, through "freq"
/// @return tcs3200 status code
tcs3200_status_e tcs3200_read(tcs3200_colour_handle_t* colSensor, uint16_t* freq);

/// @brief implementation of the interrupt handler
/// @param colSensor colour sensor handle
/// @return tcs3200 status code
tcs3200_status_e tcs3200_interrupt_handler(tcs3200_colour_handle_t* colSensor);

#endif /* TCS3200_COLOUR_H_ */
