#include "sensors/edvinclock.h"
#include "Arduino.h"

EdvinClock::EdvinClock() {
    state_ = false;
    time_ = 0;
}

void EdvinClock::init(int pin) {
    Serial.println("Initialising Edvin mode");
    pinMode(pin,INPUT);
    pin_ = pin;
}

void EdvinClock::updateTime_() {
    int value = digitalRead(pin_);
    Serial.print("state: "); Serial.print(state_); Serial.print(" Value: "); Serial.println(value);
    if (value && !state_) {
        time_++;
        state_ = true;
    }
    else if (!value && state_){
        state_ = false;
    }
    
}

int EdvinClock::getTime() {
    updateTime_();
    return time_;
}
