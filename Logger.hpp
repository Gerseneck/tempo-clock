#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <Arduino.h>

enum LogLevel : int {
    INFO,
    WARNING,
    ERROR,
};

class Logger {
    public:
        Logger();
        void init();
        void log(std::string message);
        void log(std::string message, LogLevel level);
    private:
        std::string _get_log_level_string(LogLevel level);
};

#endif
