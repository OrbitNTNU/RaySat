#include "radio.h"
#include "radioError.h"

void Radio::setup(int aprsInterval /*= 20*/, bool _verbose /*= true*/)
{
    verbose = _verbose;

    std::vector<String> GNSS_Commands = {
        "baud 9600",
        "port1 nmea",
        "p1-out none",
        "p1-rfilter none",
        "p1-pfilter none",
        "verbose 3"};

    std::vector<String> setupCommands = {
        "access always",
        "power hi",
        "mycall LA9ORB-11",
        "path",
        "freq 145500000", // sets the frequency on the radio TX/RX
        "mice-cmt Orbit NTNU VHF test, \\vV \\tC HDOP\\h",
        "mice-cmtint 3",
        "mice-msg 7",
        "mice-symbol /O",
        "autoexec-cmd port-rf-mute 1\\nmode ax25-1k2\\nfreq 144800000\\nmice-tx\\nfreq 144700000\\nmode ngham\\nport-rf-mute 0",
        "autoexec-int " + String(aprsInterval),
        "baud1 9600",
        "port1 nmea",
        "p1-out none",
        "p1-rfilter none",
        "p1-pfilter none",
        "port0 text",
        "mode ax25-1k2",  // sets the radio communication protocol
    };
    
    radioSerial.begin(38400);

    enterSettingMode(); // Entering settings

    sendConfiguration(setupCommands);
    // sendConfiguration(GNSS_Commands);

    // Itererer gjennom alt
}

void Radio::write(const String &message)
{
    radioSerial.println(message);
}

void Radio::transmit(String message)
{
    enterTransmitMode();
    // write(message);
    radioSerial.print(message);
    radioSerial.println("\r");
}

void Radio::sendCtrlC()
{
    write("\x03\n");    // Prints Ctrl + C to radio
}

void Radio::enterSettingMode() // Function to enter configuration mode
{
    if (mode == RadioMode::transmit)
    {
        sendCtrlC();
        delay(600);
        Serial.println("Entering settings mode");
        mode = RadioMode::setting; // Sets mode to settings
    }
    else if (mode == RadioMode::unknown){
        sendCtrlC();
        write("");
        delay(100);
        readFromRadio();
        Serial.println("Entering settings mode");
        mode = RadioMode::setting;
    }
}

void Radio::enterTransmitMode() // Function to enter transmit mode from settings mode (to recieve and send messages)
{
    if (mode != RadioMode::transmit)
    {
        if (mode == RadioMode::unknown) // If mode is unknown, enter settings mode
        {
            enterSettingMode();
        }

        sendSetupCommand("set"); // Prints "set" to radio to get back to transmit 
        delay(50);

        mode = RadioMode::transmit;
        if (verbose) {
            Serial.println("Radio set to transmit mode");
        }  
    }
}

String Radio::readFromRadio() // Function for reading String from radio, and clears the sending memory
{
    if (radioSerial.available()) // If the radio-port is available, read from it)
    {
        String response = radioSerial.readString();
        return response;
    }

    // Serial.println("Uart not available or no data to send"); // If not available, it is probably disconnected}
    return "";
}

String Radio::sendSetupCommand(String command)
{

    if (mode != RadioMode::setting)
    {
        throw RadioError("Not in settings mode");
    }

    write(command);

    delay(50);

    String response = readFromRadio();

    if (verbose)
    {
        Serial.print("Sending command: (");
        Serial.print(command);
        Serial.print(") got response: ");
        Serial.println(response);
    }

    // Hatlosning :))
    if (command == "path") {
        return "Path ok";
    }
    
    if (std::string(command.c_str()).compare(0, 9, "mice-cmt ") == 0) {
        return response;
    }

    if (std::string(command.c_str()).compare(0, 13, "autoexec-cmd ") == 0) {
        return response;
    }

    if (std::string(response.c_str()).find(std::string(command.c_str()) + " ok") == std::string::npos){
        throw RadioError("Error running: " + command + " -> " + response);
    }

    return response;
}

void Radio::sendConfiguration(std::vector<String> commandsToSend)
{
    enterSettingMode();
    for (int i = 0; i < commandsToSend.size(); i++)
    {
        sendSetupCommand(commandsToSend.at(i));
    }
    enterTransmitMode();
}

String Radio::getModeString(RadioMode mode)
{
    switch (mode)
    {
    case RadioMode::setting:
        return "Setting Mode";
    case RadioMode::transmit:
        return "Transmit Mode";
    case RadioMode::unknown:
        return "Unknown Mode";
    default:
        return "Invalid Mode";
    }
}

void Radio::loop() // What to loop
{
    if (mode == RadioMode::unknown)
    {
        enterSettingMode(); // Entering settings
    }

    String readString = readFromRadio(); // Clearing the sending-memory, sending to PC
    enterTransmitMode();
    // Serial.println(readString);            //  Printing what is in the memory
    Serial.println(getModeString(mode));

    Radio::readFromRadio();
    Serial.println("Transmitting...");
    Radio::transmit("hei");


    // unsigned long currentMillis = millis();
    // if ((currentMillis - Radio::previousMillis) >= Radio::interval)
    // {
    //     Radio::previousMillis = currentMillis;
    //     Radio::readFromRadio();
    //     Radio::transmit("hei");
    // }

    delay(5000);
}

// 0. Kunne koble til på Putty
// 1. Endre tilbake til pair
// 2. Sende sensordata
// 3. Koble gps slik som står på notion

/* Hvordan lese seriellporten til radioen via rasperry pi:
1. ssh inn (ssh orbit, nå)
2. ls -l /dev/serial/by-id (/dev/ttyUSB0)


Koble til rasperry pi: sudo minicom -b 38400 -o -D /dev/ttyUSB0
Ctrl + A og Q for å gå ut
Ctrl + A og Z, og O, serial port, skru av hardware flow control osv





*/