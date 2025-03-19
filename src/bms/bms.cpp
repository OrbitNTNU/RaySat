#include "bms/bms.h"
#include "Arduino.h"
#define IGN_pin D6
#define PS_pin  D5
#define IGN_PWRL_pin  D4
#define SS_EN_pin  D3

void bmsInit() {
    pinMode(IGN_pin, OUTPUT);
    digitalWrite(IGN_pin, HIGH);
    pinMode(PS_pin, OUTPUT);
    digitalWrite(PS_pin, HIGH);
    pinMode(IGN_PWRL_pin, OUTPUT);
    digitalWrite(IGN_PWRL_pin, HIGH);
    pinMode(SS_EN_pin, OUTPUT);
    digitalWrite(SS_EN_pin, HIGH);
}