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

bool isOverBullsEye(Adafruit_TCS34725 *leftColour,
                    Adafruit_TCS34725 *rightColour)
{
  float r1, g1, b1;
  float r2, g2, b2;

  leftColour->getRGB(&r1, &g1, &b1);
  rightColour->getRGB(&r2, &g2, &b2);

  if (85< r1 && r1 < 130 && 70 < g1 && g1 < 85 && 60 < b1 && b1 < 100)
  {
    return true;
  }

  return false;
}

bool isOverSafezone(Adafruit_TCS34725 *leftColour,
                    Adafruit_TCS34725 *rightColour)
{
  float r1, g1, b1;
  float r2, g2, b2;

  leftColour->getRGB(&r1, &g1, &b1);
  rightColour->getRGB(&r2, &g2, &b2);

  if (95 < r1 && r1 < 110 && 85 < g1 && g1 < 95)
  {
    return true;
  }

  return false;
}

bool isOverHome(Adafruit_TCS34725 *leftColour,
                Adafruit_TCS34725 *rightColour)
{
  float r1, g1, b1;
  float r2, g2, b2;

  leftColour->getRGB(&r1, &g1, &b1);
  rightColour->getRGB(&r2, &g2, &b2);

  if (165 < r1 && r1 < 185 && 165 < r2 && r2 < 185 && g1 < 65 && g2 < 55)
  {
    return true;
  }

  return false;
}

bool isOverLine(Adafruit_TCS34725 *leftColour,
                Adafruit_TCS34725 *rightColour)
{
  float r1, g1, b1;
  float r2, g2, b2;

  leftColour->getRGB(&r1, &g1, &b1);
  rightColour->getRGB(&r2, &g2, &b2);

  if (r1 < 145 && r2 > 155 && g1 < 75 && g2 < 75)
  {
    return true;
  }

  return false;
}

void rotateInPlace(rotation_dir_e dir,
                   float deg,
                   MPU6050 *imu,
                   DRV8833 *leftMotor,
                   DRV8833 *rightMotor)
{
  const float LEFT_MOTOR_SPEED = 66.0f;
  const float RIGHT_MOTOR_SPEED = 66.0f;

  if (dir == CLOCKWISE)
  {
    leftMotor->drive(DRV8833_FORWARD, LEFT_MOTOR_SPEED);
    rightMotor->drive(DRV8833_REVERSE, RIGHT_MOTOR_SPEED);
  }
  else
  {
    leftMotor->drive(DRV8833_REVERSE, LEFT_MOTOR_SPEED);
    rightMotor->drive(DRV8833_FORWARD, RIGHT_MOTOR_SPEED);
  }

  const float TIME_STEP = 0.001;
  uint32_t timer = 0;
  float yaw = 0;

  while (abs(yaw) < deg)
  {
    timer = millis();
    Vector norm = imu->readNormalizeGyro();

    yaw = yaw + norm.ZAxis * TIME_STEP;

    delay((TIME_STEP * 1000) - (millis() - timer));
  }

  leftMotor->stop();
  rightMotor->stop();
}