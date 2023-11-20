#include "helpers.h"
#include "Arduino.h"
#include "Adafruit_TCS34725.h"

bool isButtonPressed()
{
  if (digitalRead(USER_BTN) == 0)
  {
    delay(75);
    if (digitalRead(USER_BTN) == 0)
    {
      return true;
    }
  }
  else
  {
    return false;
  }
}

bool isOverBullsEye(Adafruit_TCS34725* leftColour,
                    Adafruit_TCS34725* rightColour)
{
    float r1, g1, b1;
    float r2, g2, b2;

    leftColour->getRGB(&r1, &g1, &b1);
    rightColour->getRGB(&r2, &g2, &b2);

    if (110 < r1 && r1 < 130 && 70 < g1 && g1 < 85 && 50 < b1 && b1 < 80)
    {
        return true;
    }

    return false;
}