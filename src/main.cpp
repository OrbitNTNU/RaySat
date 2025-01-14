#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sensors/pressure.h"
#include "sensors/temperature.h"
#include "sd/datastorage.h"

// put function declarations here:
int myFunction(int, int);
DataObject temperature;
DataObject pressure;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing...");
  sdSystemInit();
  Serial.println("----------------------");
  // tester.fileWrite("TESTER");
  setup_temperature();
  temperature.init("temper",2);
  setup_pressure();
  pressure.init("pressu",2);
}

void loop() {
  // put your main code here, to run repeatedly:
  // double pressure = read_pressure();
  // Serial.print("Pressure: ");
  // Serial.println(pressure);
  float temp = read_temperature();
  temperature.fileWrite(String(temp));
  float pressu = read_pressure();
  Serial.println(pressu);
  pressure.fileWrite(String(pressu));
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}