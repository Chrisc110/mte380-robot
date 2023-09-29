#include "tcs3200_colour.h"

/* Helper Function Definitions */
static tcs3200_status_e tcs3200_set_red(tcs3200_colour_handle_t* colSensor);
static tcs3200_status_e tcs3200_set_green(tcs3200_colour_handle_t* colSensor);
static tcs3200_status_e tcs3200_set_blue(tcs3200_colour_handle_t* colSensor);
static tcs3200_status_e tcs3200_set_clear(tcs3200_colour_handle_t* colSensor);

static tcs3200_status_e get_ccr_register(TIM_HandleTypeDef* tim, uint32_t timChannel, uint32_t* crrVal);

/********************************/

static tcs3200_status_e tcs3200_set_red(tcs3200_colour_handle_t* colSensor)
{
    HAL_GPIO_WritePin(colSensor->s2Port, colSensor->s2Pin, 0);
    HAL_GPIO_WritePin(colSensor->s3Port, colSensor->s3Pin, 0);

    return TCS3200_NO_ERROR;
}

static tcs3200_status_e tcs3200_set_green(tcs3200_colour_handle_t* colSensor)
{
    HAL_GPIO_WritePin(colSensor->s2Port, colSensor->s2Pin, 1);
    HAL_GPIO_WritePin(colSensor->s3Port, colSensor->s3Pin, 1);

    return TCS3200_NO_ERROR;
}

static tcs3200_status_e tcs3200_set_blue(tcs3200_colour_handle_t* colSensor)
{
    HAL_GPIO_WritePin(colSensor->s2Port, colSensor->s2Pin, 0);
    HAL_GPIO_WritePin(colSensor->s3Port, colSensor->s3Pin, 1);

    return TCS3200_NO_ERROR;
}

static tcs3200_status_e tcs3200_set_clear(tcs3200_colour_handle_t* colSensor)
{
    HAL_GPIO_WritePin(colSensor->s2Port, colSensor->s2Pin, 1);
    HAL_GPIO_WritePin(colSensor->s3Port, colSensor->s3Pin, 0);

    return TCS3200_NO_ERROR;
}

static tcs3200_status_e get_ccr_register(TIM_HandleTypeDef* tim, uint32_t timChannel, uint32_t* ccrVal)
{
    tcs3200_status_e status = TCS3200_NO_ERROR;

    switch (timChannel) {
        case TIM_CHANNEL_1:
            ccrVal = (uint32_t)&tim->Instance->CCR1;
            break;
        case TIM_CHANNEL_2:
            ccrVal = (uint32_t)&tim->Instance->CCR2;
            break;
        case TIM_CHANNEL_3:
            ccrVal = (uint32_t)&tim->Instance->CCR3;
            break;
        case TIM_CHANNEL_4:
            ccrVal = (uint32_t)&tim->Instance->CCR4;
            break;
        default:
            status = TCS3200_INVALID_PARAMETER;
            break;
    }

    return status;
}


tcs3200_status_e tcs3200_init(tcs3200_colour_handle_t* colSensor)
{
    //cube ide should have already initalized all the gpios, timers, and interrupts
    return tsc3200_start(colSensor);
}


tcs3200_status_e tsc3200_start(tcs3200_colour_handle_t* colSensor)
{
    tcs3200_status_e status = TCS3200_NO_ERROR;

    if (HAL_TIM_IC_Start_IT(colSensor->tim, colSensor->timChannel) != HAL_OK)
    {
        //print that we have an error
        status = TCS3200_ERROR;
    }

    return status;
}


tcs3200_status_e tsc3200_stop(tcs3200_colour_handle_t* colSensor)
{
    tcs3200_status_e status = TCS3200_NO_ERROR;

    if (HAL_TIM_IC_Stop_IT(colSensor->tim, colSensor->timChannel) != HAL_OK)
    {
        //print that we have an error
        status = TCS3200_ERROR;
    }

    return status;

}

tcs3200_status_e tcs3200_select_colour(tcs3200_colour_handle_t* colSensor, tcs3200_colour_e colour)
{
    tcs3200_status_e status = TCS3200_NO_ERROR;

    switch (colour)
    {
        case RED:
            tcs3200_set_red(colSensor);
            break;

        case GREEN:
            tcs3200_set_green(colSensor);
            break;

        case BLUE:
            tcs3200_set_blue(colSensor);
            break;

        case CLEAR:
            tcs3200_set_clear(colSensor);
            break;

        default:
            status = TCS3200_INVALID_PARAMETER;
    }

    return status;
}

tcs3200_status_e tcs3200_read(tcs3200_colour_handle_t* colSensor, uint16_t* freq)
{
    *freq = colSensor->intData.freq;
    return TCS3200_NO_ERROR;
}

tcs3200_status_e tcs3200_interrupt_handler(tcs3200_colour_handle_t* colSensor)
{
    TIM_HandleTypeDef* tim = colSensor->tim;
    uint32_t timChannel = colSensor->timChannel;

    //the first rising edge
    if (colSensor->intData.isFirst)
    {
        //save the ticks of the first rising edge
        get_ccr_register(tim, timChannel, &colSensor->intData.t1);
        colSensor->intData.isFirst = false;
    }
    else
    {
        //save the ticks of the second rising edge
        get_ccr_register(tim, timChannel, &colSensor->intData.t2);
        
        uint32_t ticks = 0;
        //if there is NO overflow
        if (colSensor->intData.t2 > colSensor->intData.t1)
        {
            ticks = colSensor->intData.t2 - colSensor->intData.t1;
        }
        else
        {
            //account for overflow
            ticks = (colSensor->intData.t2 + 65535) -  colSensor->intData.t2;
        }

        //based on the clock frequency and the number of ticks, calculate the square wave freqs
        colSensor->intData.freq = (double)CLK_FREQ / (double)ticks;
    } 

    return TCS3200_NO_ERROR;
}