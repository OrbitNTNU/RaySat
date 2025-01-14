#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sensors/pressure.h"
#include "sd/datastorage.h"

// put function declarations here:
int myFunction(int, int);
DataObject tester;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing...");
  sdSystemInit();
  Serial.println("----------------------");
  tester.init("testma",2);
  // tester.fileWrite("TESTER");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(tester.name);
  delay(10);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}