#pragma once
#include "sensors/sensors.h"

class RWController {
private:
    bool ascended_;
    bool state_;
    void disablecheck_(const SensorData& data);
public:
    void control(const SensorData& data);
    RWController();
};