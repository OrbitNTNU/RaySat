#pragma once

class EdvinClock {
public:
    EdvinClock();
    void init(int pin);
    int getTime();
private:
    void updateTime_();
    bool state_;
    int time_;
    int pin_;
};