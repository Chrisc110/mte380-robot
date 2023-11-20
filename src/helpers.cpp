#include "helpers.h"
#include "Arduino.h"

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
