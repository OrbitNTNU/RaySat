#include "reactionWheel/rwController.h"

// defining pin settings
// TODO: get propper values here
#define RWON_OUTPUT LOW
#define RWOFF_OUTPUT HIGH

// defining different maximum values
#define KNEKKTEMP 50.0
#define KNEKKHEIGHT 4000.0
#define ASCENDEDHEIGHT 10000.0

void RWController::disablecheck_(const SensorData& data) {
    // disable is true if the RW should be disabled
    bool disable = false;
    disable = disable || (data.insideTemperature > KNEKKTEMP);
    disable = disable || ((data.height < KNEKKHEIGHT) && ascended_);
    state_ = !disable; // state is true if enabled and false if disabled
    return;
}

void RWController::init(int pin) {
    controllerPin_ = pin;
    pinMode(controllerPin_,OUTPUT);
}

void RWController::toggleRW() {
    if (manual_) {state_ = !state_;}
}
void RWController::toggleManual() {
    manual_ = !manual_;
}

void RWController::control(const SensorData& data) {
    if (data.height > ASCENDEDHEIGHT) {ascended_ = true;}
    if (!manual_) {disablecheck_(data);}
    if (state_) {
        digitalWrite(controllerPin_,RWON_OUTPUT);
    } else {
        digitalWrite(controllerPin_,RWOFF_OUTPUT);
    }
}

bool RWController::getState() {
    return state_;
}

String RWController::stateToString(bool state) {
    std::unordered_map<bool, String> map = {{true, "on"}, {false, "off"}};
    return map.at(state);
}

bool RWController::getManual() {
    return manual_;
}

String RWController::manualToString(bool manual) {
    std::unordered_map<bool, String> map = {{true, "on"}, {false, "off"}};
    return map.at(manual);
}

RWController::RWController() {
    state_ = true;
    ascended_ = false;
    manual_ = false;
}

