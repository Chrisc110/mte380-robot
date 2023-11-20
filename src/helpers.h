#ifndef HELPERS_H
#define HELPERS_H

#include "Adafruit_TCS34725.h"

bool isButtonPressed();

bool isOverBullsEye(Adafruit_TCS34725* leftColour,
                    Adafruit_TCS34725* rightColour);



#endif