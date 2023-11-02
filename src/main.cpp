#include <Arduino.h>
#include <ISL29125.h>
#include <drv8833.h>

DRV8833 motor(5,6);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);


}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(50);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(50);

  motor.drive(DRV8833_FORWARD, 100.0f);

  Serial.print("Hello\n");
  } 