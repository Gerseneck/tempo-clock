#include <Arduino.h>

#include "Logger.hpp"

Logger::Logger() {}

void Logger::init() {
    Serial.begin(9600);
    log("Logger Ready!");
}

void Logger::log(std::string message) {
    log(message, INFO);
}

void Logger::log(std::string message, LogLevel level) {
    arduino::String msg = (_get_log_level_string(level) + "[" + std::to_string(millis() / 1000.0) + "] " + message).c_str();
    Serial.println(msg);
}

std::string Logger::_get_log_level_string(LogLevel level) {
    switch (level) {
        case INFO:
            return std::string("[INFO]");
        case WARNING:
            return std::string("[WARNING]");
        case ERROR:
            return std::string("[ERROR]");
    }
}
