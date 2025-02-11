#include "Adafruit_MPRLS.h"

#define RESET_PIN -1
#define EOC_PIN   -1

Adafruit_MPRLS mpr = Adafruit_MPRLS(RESET_PIN, EOC_PIN);

int setup_pressure() {
  if (!mpr.begin()) {
    Serial.println("Failed to communicate with MPRLS sensor, check wiring?");
    return 1;
  }
  Serial.println("Found MPRLS sensor");
  return 0;
}

float read_pressure() {
  float pressure_hPa = mpr.readPressure();
  // Serial.print("Pressure (hPa): "); Serial.println(pressure_hPa);
  return pressure_hPa;
}