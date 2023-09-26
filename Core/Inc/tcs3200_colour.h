#ifndef TCS3200_COLOUR_H_
#define TCS3200_COLOUR_H_

#include "stm32f4xx_hal.h"
#include "stdint.h"

typedef struct{
    GPIO_TypeDef* s0Port;   //Output freq scaling selection bit 0
    uint16_t      s0Pin;

    GPIO_TypeDef* s1Port;   //Output freq scaling selection bit 1
    uint16_t      s0Pin;

    GPIO_TypeDef* s2Port;   //Photodiode type selection bit 0
    uint16_t      s0Pin;

    GPIO_TypeDef* s3Port;   //Photodiode type selection bit 1
    uint16_t      s0Pin;

    

}tcs3200_colour_t;

#endif /* TCS3200_COLOUR_H_ */
