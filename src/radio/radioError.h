#pragma once
#include <Arduino.h>
#include <stdexcept>
#include <string>

class RadioError : public std::runtime_error
{
    public:
        RadioError(const String& msg) : runtime_error(msg.c_str()) {}
};