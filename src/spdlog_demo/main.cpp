#include <iostream>
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

int main()
{
    try {
        // Create basic file logger (not rotated)
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");

        // change log pattern
        my_logger->set_pattern("[%H:%M:%S %z] [%n] [%^---%l---%$] [thread %t] %v");

        // Set global log level to debug
        my_logger->set_level(spdlog::level::trace);

        my_logger->trace("Trace the error message");
        my_logger->debug("This message should be displayed..");

        my_logger->info("Welcome to spdlog!");
        my_logger->info("Support for floats {:03.2f}", 1.23456);
        my_logger->info("Positional args are {1} {0}..", "too", "supported");
        my_logger->info("{:<30}", "left aligned");

        my_logger->warn("Easy padding in numbers like {:08d}", 12);

        my_logger->error("Some error message with arg: {}", 1);

        my_logger->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    }
    catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }

    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");
    SPDLOG_INFO("Some info message");
    SPDLOG_WARN("Some warn message");
    SPDLOG_ERROR("Some error message");
    SPDLOG_CRITICAL("Some critical message");
}
