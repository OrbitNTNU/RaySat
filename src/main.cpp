#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sensors/pressure.h"
#include "sensors/temperature.h"
#include "sensors/uv.h"
#include "sensors/gyro.h"
#include "sd/datastorage.h"


// put function declarations here:
int myFunction(int, int);
DataObject temperature;
DataObject pressure;
DataObject ultraviolet;

float gyro_x; 
float gyro_y;
float gyro_z;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing...");
  sdSystemInit();
  Serial.println("----------------------");
  // setup_temperature();
  // temperature.init("temper",2);
  // setup_pressure();
  // pressure.init("pressu",2);
  // setup_uv();
  // ultraviolet.init("violet",2);
  calibrate_gyro(2000);

  // read_gyro(gyro_x,gyro_y,gyro_z);
}

void loop() {
  // put your main code here, to run repeatedly:
  // double pressure = read_pressure();
  // Serial.print("Pressure: ");
  // Serial.println(pressure);

  // --------------------- Sensor ----------------------
  // Temperature
  // float temp = read_temperature(); 
  // temperature.fileWrite(String(temp));
  //Serial.print("Temperature: ");Serial.println(temp);
  // Pressure
  // float pressu = read_pressure(); 
  // pressure.fileWrite(String(pressu));
  //Serial.print("Pressure: ");Serial.println(pressu);
  // UV
  // uint32_t uv = read_uv();
  // ultraviolet.fileWrite(String(uv));
  // Serial.print("UV: ");Serial.println(String(uv));
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}