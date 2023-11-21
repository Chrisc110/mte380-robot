#include "drv8833.h"

DRV8833::DRV8833(uint32_t in1, uint32_t in2)
{
    // save the pins
    _in1 = in1;
    _in2 = in2;

    currentSpeed = 0;

    // init the pins to output (PWM)
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);

    // set pins to low to start
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    analogWriteFrequency(PWM_CONTROL_FREQ);
}

DRV8833::~DRV8833() {}

void DRV8833::drive_forward(float speedPercent)
{
    analogWrite(_in1, MAX_DUTY_CYCLE * (speedPercent / 100.0f));
    analogWrite(_in2, 0);
}

void DRV8833::drive_reverse(float speedPercent)
{
    analogWrite(_in1, 0);
    analogWrite(_in2, MAX_DUTY_CYCLE * (speedPercent / 100.0f));
}

void DRV8833::stop()
{
    analogWrite(_in1, 0);
    analogWrite(_in2, 0);
    currentSpeed = 0;
}

void DRV8833::drive(drv8833_dir_e dir, float speedPercent)
{
    if (dir == DRV8833_FORWARD)
    {
        drive_forward(speedPercent);
    }
    else if (dir == DRV8833_REVERSE)
    {
        drive_reverse(speedPercent);
    }

    currentSpeed = speedPercent;
}

float DRV8833::getCurrentSpeed()
{
    return currentSpeed;
}