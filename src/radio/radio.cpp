#include "radio.h"

std::pair<int, String> Radio::setup(int aprsInterval /*= 20*/, bool _verbose /*= true*/)
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
        "power high",
        "mycall LA3JPA-11", // Må endres
        "path",
        "mice-cmt Orbit NTNU VHF test, \\vV \\tC HDOP\\h",
        "mice-cmtint 3",
        "mice-msg 7",
        "mice-symbol /O",
        "autoexec-cmd port-rf-mute 1\\nmode ax25-1k2\\nfreq 144800000\\nmice-tx\\nfreq 144700000\\nmode ngham\\nport-rf-mute 0",
        "autoexec-int 60", //+ aprsIntervalString,
        "baud1 9600",
        "port1 nmea",
        "p1-out none",
        "p1-rfilter none",
        "p1-pfilter none",
        "port0 ngham-spp" // bør endres
    };
    
    radioSerial.begin(38400);
    sendSetup();
    enterSettingMode(); // Entering settings
}

void Radio::write(const String &message)
{
    radioSerial.println(message);
}

void Radio::sendCtrlC()
{
    write("\x03\n"); // Prints Ctrl + C to radio
}

void Radio::enterSettingMode() // Function to enter configuration mode
{
    if (mode != RadioMode::setting)
    {
        sendCtrlC();
        delay(600);
        mode = RadioMode::setting; // Sets mode to settings
    }
}

std::pair<int, String> Radio::enterTransmitMode() // Function to enter transmit mode from settings mode (to recieve and send messages)
{
    if (mode != RadioMode::transmit)
    {
        if (mode == RadioMode::unknown) // If mode is unknown, enter settings mode
        {
            enterSettingMode();
        }

        auto results = sendSetupCommand("set"); // Prints "set" to radio to get back to transmit
        // radioSerial.println("set"); 
        delay(300);
        // String response = read();

        if (results.second.indexOf(">") >= 0) // Checks if radio gave correct response
        {
            mode = RadioMode::transmit;
            Serial.println("Radio set to transmit mode");
            return results;
        }
        
        Serial.println("Error: Radio did not respond correctly");
        return results;
    }
    else
    {
        Serial.println("Already in transmit mode");
    }
}

void Radio::setMode(RadioMode desiredMode)
{
    if (mode != desiredMode)
    {
        if (desiredMode == RadioMode::setting)
        {
            enterSettingMode();
        }
        else if (desiredMode == RadioMode::transmit)
        {
            enterTransmitMode();
        }
    }
}

// String Radio::setUserMode(String input) {
//     if (input == "setting")
// }

String Radio::read() // Function for reading String from radio, and clears the sending memory
{
    if (radioSerial.available()) // If the radio-port is available, read from it)
    {
        String response = radioSerial.readString();
        return response;
        // if (response.indexOf("cmd_inv") >= 0)
        // {
        //     Serial.println("cmd_inv: Radio is in the wrong mode or the commando is invalid.");
        //     return "";
        // }
    }

    Serial.println("Uart not available or no data to send"); // If not available, it is probably disconnected}
    return "";
}

void Radio::sendMessage(String message)
{
    enterTransmitMode();
    radioSerial.println(message);
}

// void Radio::sendSetup()
// {
//     radioSerial.println("freq 145500000");
//     radioSerial.println("access always")
//     radioSerial.println("")
// }

void Radio::sendSetup()
{
    write("freq 145500000"); // sets the frequency on the radio TX/RX
    write("mode ax25-1k2");  // sets the radio communication protocol
    write("access csma");    // sets access method, here carrier sense multiple access
    write("port0 text");     // sets port0 to be used for text TX/RX
}

std::pair<int, String> Radio::sendSetupCommand(String command)
{

    if (mode != RadioMode::setting)
    {
        return std::make_pair(-1, "Not in settings mode \n");
    }

    write(command);

    String response = read();

    if (verbose)
    {
        Serial.print("Sending command: (");
        Serial.print(command);
        Serial.print(") got response: ");
        Serial.println(response);
    }

    return std::make_pair(0, response);

    // Trenger noen errorgreier
}

std::pair<int, String> Radio::sendConfiguration(std::vector<String> commandsToSend)
{
    enterSettingMode();
    std::pair<int, String> results;

    for (int i = 0; i < commandsToSend.size(); i++)
    {
        results = sendSetupCommand(commandsToSend.at(i));
        if (results.first < 0) {
            return results;
        }
    }

    results = enterTransmitMode();
    if(results.first < 0){
        return results;
    }

    return std::make_pair(0, "");


}
/*
void Radio::menu() {
        while (1) {
            Serial.println("1. Enter settings mode");
            Serial.println("2. Enter transmit mode");
            Serial.println("3. Send message");
            Serial.println("4. Read message");
            Serial.println("5. Read from sensor")

        while (Serial.available() == 0) {
        }

        int menuChoice = Serial.parseInt();

        switch (menuChoice)
        {
        case 1:
            enterSettingMode();
            break;
        case 2:
            enterTransmitMode();
            break;
        case 3:
            String message =
            sendMessage();
            break;
        default:
            return;
            break;
        }

        }
    }
*/

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
    delay(100);

    String readString = read(); // Clearing the sending-memory, sending to PC
    enterTransmitMode();
    // Serial.println(readString);            //  Printing what is in the memory
    Serial.println(getModeString(mode));

    unsigned long currentMillis = millis();
    if ((currentMillis - Radio::previousMillis) >= Radio::interval)
    {
        Radio::previousMillis = currentMillis;
        Radio::read();
    }

    delay(5000);
}

// 1. Koble til radio
// 2. Sende til ctrl c for å hoppe til instillinger
// 3. Lese hva radio sender tilbake
// 4. Sende radiosignalet til terminalen vår (>)

// 0. Klassen må vite hvilken modus radioen er i
// 1. Sende innstillinger til radio fra OBC, radioSerial.println
// 2. Sende en melding.Først sende kommando set->sende meldingen med ny linje
// 3. Sjekke om noen har sendt noe til oss
// 4. Sjekke om radioen er koblet til OBC-en. (Hvis vi sender ctrl-c skal radioen enten svare med > eller cmd_inv >)

// Underveis er det sikert lurt å print ting til monitor.

// Ctrl-C: Sende/motta->Innstillinger
// set : Innstillinger->Sende/motta
