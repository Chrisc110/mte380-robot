/******************************************************************************
ISL29125_basics.ino
Simple example for using the ISL29125 RGB sensor library.
Jordan McConnell @ SparkFun Electronics
11 Apr 2014
https://github.com/sparkfun/SparkFun_ISL29125_Breakout_Arduino_Library

This example declares an SFE_ISL29125 object called RGB_sensor. The 
object/sensor is initialized with a basic configuration so that it continuously
samples the light intensity of red, green and blue spectrums. These values are
read from the sensor every 2 seconds and printed to the Serial monitor.

Developed/Tested with:
Arduino Uno
Arduino IDE 1.0.5

Requires:
SparkFun_ISL29125_Arduino_Library

This code is beerware.
Distributed as-is; no warranty is given. 
******************************************************************************/

#include <Wire.h>
#include <ISL29125.h>
#include <drv8833.h>
#include "defines.h"

// Declare sensor object
// TwoWire colSenWire1(COL_SEN_SDA_1, COL_SEN_SCL_1);
// TwoWire colSenWire2(COL_SEN_SDA_2, COL_SEN_SCL_2);
// SFE_ISL29125 colSen1(ISL_I2C_ADDR, colSenWire1);
// SFE_ISL29125 colSen2(ISL_I2C_ADDR, colSenWire2);


// void setup()
// {
//   // Initialize serial communication
//   Serial.begin(9600);

//   pinMode(LED_BUILTIN, OUTPUT);

//   //initialize colour sensor
//   if (colSen1.init())
//   {
//     Serial.println("Sensor 1 Initialization Successful\n\r");
//   }
//   if (colSen2.init())
//   {
//     Serial.println("Sensor 2 Initialization Successful\n\r");
//   }
// }

// // Read sensor values for each color and print them to serial monitor
// void loop()
// {
//   digitalWrite(LED_BUILTIN, HIGH);
//   unsigned int red1 = colSen1.readRed();
//   unsigned int green1 = colSen1.readGreen();
//   unsigned int blue1 = colSen1.readBlue();

//   unsigned int red2 = colSen2.readRed();
//   unsigned int green2 = colSen2.readGreen();
//   unsigned int blue2 = colSen2.readBlue();
  
//   // Print out readings, change HEX to DEC if you prefer decimal output
//   Serial.print("Red1: "); Serial.println(red1,HEX);
//   Serial.print("Green1: "); Serial.println(green1,HEX);
//   Serial.print("Blue1: "); Serial.println(blue1,HEX);
//   Serial.print("Red2: "); Serial.println(red2,HEX);
//   Serial.print("Green2: "); Serial.println(green2,HEX);
//   Serial.print("Blue2: "); Serial.println(blue2,HEX);
//   Serial.println();
//   delay(2000);

// }

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  pinMode(COL_SEN_ADC_1, INPUT);
  pinMode(COL_SEN_ADC_2, INPUT);
  pinMode(COL_SEN_RED, OUTPUT);
  pinMode(COL_SEN_GREEN, OUTPUT);
  pinMode(COL_SEN_BLUE, OUTPUT);
  digitalWrite(COL_SEN_RED,LOW);
  digitalWrite(COL_SEN_GREEN,LOW);
  digitalWrite(COL_SEN_BLUE,LOW);

}

// Read sensor values for each color and print them to serial monitor
void loop()
{
  unsigned int red1 = 0;
  unsigned int red2 = 0;
  unsigned int blue1 = 0;
  unsigned int blue2 = 0;
  unsigned int green1 = 0;
  unsigned int green2 = 0;

  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(COL_SEN_BLUE,LOW);
  digitalWrite(COL_SEN_RED,HIGH);
  delay(1000);
  for(int i = 0; i < 10; i++)
  {
    red1 += analogRead(COL_SEN_ADC_1);
    red2 += analogRead(COL_SEN_ADC_2);
  }
  digitalWrite(COL_SEN_RED,LOW);
  digitalWrite(COL_SEN_GREEN,HIGH);
  delay(1000);
  for(int i = 0; i < 10; i++)
  {
    green1 += analogRead(COL_SEN_ADC_1);
    green2 += analogRead(COL_SEN_ADC_2);
  }

  digitalWrite(COL_SEN_GREEN,LOW);
  digitalWrite(COL_SEN_BLUE,HIGH);
  delay(1000);
  for(int i = 0; i < 10; i++)
  {
    blue1 += analogRead(COL_SEN_ADC_1);
    blue2 += analogRead(COL_SEN_ADC_2);
  }
  
  // Print out readings, change HEX to DEC if you prefer decimal output
  Serial.print("Red1: "); Serial.println(red1);
  Serial.print("Green1: "); Serial.println(green1);
  Serial.print("Blue1: "); Serial.println(blue1);
  Serial.print("Red2: "); Serial.println(red2);
  Serial.print("Green2: "); Serial.println(green2);
  Serial.print("Blue2: "); Serial.println(blue2);
  Serial.println();

}
