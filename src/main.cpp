#include <Arduino.h>
#include <Wire.h>
#include "sensors/pressure.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing...");
  // Wire.begin();
  int result = myFunction(2, 3);
  setup_pressure();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  double pressure = read_pressure();
  Serial.print("Pressure: ");
  Serial.println(pressure);
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}