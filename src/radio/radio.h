#include <SoftwareSerial.h>
#include <vector>
#include <string>
#pragma once

#define BAUD_RATE 38400

enum class RadioMode {
    // Modes that the radio can be in
    unknown,
    setting,
    transmit
};

// String callSign = 

class Radio
{
public:
    RadioMode mode = RadioMode::unknown;

    std::pair<int, String> setup(int aprsInterval = 20, bool _verbose = true);
    std::pair<int, String> enterTransmitMode();
    void enterSettingMode();
    std::pair<int, String> transmit(String message);
    std::pair<int, String> checkGnssFix();

    String readFromRadio(); // Reading from radio
private:
    bool verbose;
    bool gnssFix = false;
    HardwareSerial radioSerial{PC5, PC4}; // Uart pins to radio (D1=TX/D0=RX on CN9)
    // HardwareSerial radioSerial{D0, D1};

    std::pair<int, String> sendSetupCommand(const String& command);
    std::pair<int, String> sendConfiguration(std::vector<String> commandsToSend);

    String getModeString(RadioMode mode);
    void sendCtrlC();

    void write(const String &message);
};
