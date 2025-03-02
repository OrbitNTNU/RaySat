#include "reactionWheel/rwController.h"

// defining pin settings
// TODO: get propper values here
#define RWPIN A12
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

void RWController::control(const SensorData& data) {
    if (data.height > ASCENDEDHEIGHT) {ascended_ = true;}
    disablecheck_(data);
    digitalWrite(RWPIN,RWON_OUTPUT*(state_)+RWOFF_OUTPUT*(!state_));
}
RWController::RWController() {
    state_ = true;
    ascended_ = false;
}