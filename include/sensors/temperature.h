#pragma once
#include "Adafruit_ADT7410.h"

class TempSensor {
    public:
        float read();
        int init(uint8_t addr);
    private:
        Adafruit_ADT7410 sensor;
        uint8_t addr;
};
