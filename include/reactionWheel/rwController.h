#pragma once
#include "sensors/sensors.h"

class RWController {
private:
    bool ascended_;
    bool state_;
    bool manual_;
    int controllerPin_;
    void disablecheck_(const SensorData& data);
public:
    void control(const SensorData& data);
    void init(int pin);
    void toggleManual();
    void toggleRW();
    RWController();
};