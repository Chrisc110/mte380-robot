#ifndef DRV8833_H
#define DRV8833_H

#include <Arduino.h>
#include <stdint.h>


#define PWM_CONTROL_FREQ 50000
#define MAX_DUTY_CYCLE 255

typedef enum{
    DRV8833_FORWARD = 0,
    DRV8833_REVERSE
} drv8833_dir_e;

class DRV8833
{
    public:
    DRV8833(uint32_t in1, uint32_t in2);
    ~DRV8833();

    void drive(drv8833_dir_e dir, float speedPercent);

    void stop();

    float getCurrentSpeed();

    private:
    uint32_t _in1;
    uint32_t _in2;

    float currentSpeed;
    
    void drive_forward(float speedPercent);
    void drive_reverse(float speedPercent);


};

#endif
