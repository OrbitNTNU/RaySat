#include "Adafruit_ADT7410.h"

Adafruit_ADT7410 tempsensor = Adafruit_ADT7410();

int setup_temperature() {
    if (!tempsensor.begin()) {
        Serial.println("Couldn't find ADT7410");
        return 1;
    }
    // Sensor takes 250 ms to get first readings
    delay(250);
    tempsensor.setResolution(ADT7410_13BIT);
    Serial.print("Resolution = ");
    switch (tempsensor.getResolution()) {
        case ADT7410_13BIT:
            Serial.print("13");
        case ADT7410_16BIT:
            Serial.print("16");
        default:
            Serial.print("??");
    }
    Serial.println(" bits");
    return 0;
}

float read_temperature() {
    float c = tempsensor.readTempC();
    Serial.println(c);
    return c;
}