#include <SoftwareSerial.h>
#include <vector>
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
    std::pair<int, String> Radio::setup(int aprsInterval = 20, bool _verbose = true);
    void loop();

    String read(); // Reading from radio


private:
    HardwareSerial radioSerial{PC5, PC4}; // Uart pins to radio (D1=TX/D0=RX on CN9)
    RadioMode mode = RadioMode::unknown;  // Initial mode is unknown
    unsigned long previousMillis = 0;
    const long interval = 10000;

    void setMode(RadioMode desiredMode);
    void enterSettingMode();
    std::pair<int, String> enterTransmitMode();
    String getModeString(RadioMode mode);

    void sendSetup();
    std::pair<int, String> sendSetupCommand(String command);
    std::pair<int, String> sendConfiguration(std::vector<String> commandsToSend);
    void sendMessage(String message);
    void sendCtrlC();

    void write(const String &message);
    void transmit(String message);
    String read();

    void menu();
    bool verbose;
};
