#include "sensors/temperature.h"

Adafruit_ADT7410 tempsensor = Adafruit_ADT7410();

int TempSensor::init(uint8_t addr,bool debugMode) {
    Serial.print("Initialising temperature sensor at addr: "); Serial.println(addr);
    sensor = Adafruit_ADT7410();
    if (!sensor.begin(addr)) {
        Serial.print("Couldn't find ADT7410 at addr: "); Serial.println(addr);
        while (debugMode);
        return 1;
    }
    // Sensor takes 250 ms to get first readings
    delay(250);
    sensor.setResolution(ADT7410_16BIT);
    Serial.print("Resolution = ");
    switch (sensor.getResolution()) {
        case ADT7410_13BIT:
            Serial.print("13");
        case ADT7410_16BIT:
            Serial.print("16");
        default:
            Serial.print("??");
    }
    Serial.println(" bits");
    Serial.print("Successfully set up temperature sensor at addr: "); Serial.println(addr);
    return 0;
}
float TempSensor::read() {
    return sensor.readTempC();
}