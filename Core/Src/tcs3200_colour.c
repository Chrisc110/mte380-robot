#include "tcs3200_colour.h"

/* Helper Function Definitions */
static tcs3200_status_e tcs3200_set_red(tcs3200_colour_handle_t* colSensor);
static tcs3200_status_e tcs3200_set_green(tcs3200_colour_handle_t* colSensor);
static tcs3200_status_e tcs3200_set_blue(tcs3200_colour_handle_t* colSensor);
static tcs3200_status_e tcs3200_set_clear(tcs3200_colour_handle_t* colSensor);

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


tcs3200_status_e tcs3200_init(tcs3200_colour_handle_t* colSensor)
{
    //cube ide should have already initalized all the gpios, timers, and interrupts
    return TCS3200_NO_ERROR;
}


tcs3200_status_e tsc3200_start(tcs3200_colour_handle_t* colSensor)
{
    //check if the timer channel input capture interrupt is already enabled?
    //enable the timer channel input capture interrupt
    return TCS3200_NO_ERROR;
}


tcs3200_status_e tsc3200_stop(tcs3200_colour_handle_t* colSensor)
{
    //check if the timer channel input capture interrupt is already disabled?
    //disable the timer channel input capture interrupt
    return TCS3200_NO_ERROR;

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
    //first rising edge
    if (colSensor->intData.isFirst)
    {
        colSensor->intData.t1 = colSensor->tim->Instance->CCR1;
    }
    else
    {

    } 


    return TCS3200_NO_ERROR;
}