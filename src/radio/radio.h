#include <SoftwareSerial.h>
#include <vector>
#include <string>
#pragma once

enum class RadioMode
{
    unknown,
    setting,
    transmit
}; // Modes that the radio can be in

class Radio
{


public:
    void setup(int aprsInterval = 20, bool _verbose = true);
    void loop();

    String readFromRadio(); // Reading from radio
    void transmit(String message);

private:
    HardwareSerial radioSerial{PC5, PC4}; // Uart pins to radio (D1=TX/D0=RX on CN9)
    RadioMode mode = RadioMode::unknown;  // Initial mode is unknown
    unsigned long previousMillis = 0;
    const long interval = 10000;
    void enterSettingMode();
    void enterTransmitMode();
    String getModeString(RadioMode mode);

    String sendSetupCommand(String command);
    void sendConfiguration(std::vector<String> commandsToSend);
    void sendCtrlC();

    void write(const String &message);

    bool verbose;
};
