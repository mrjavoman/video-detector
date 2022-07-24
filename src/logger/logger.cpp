#include <iostream>
#include "logger.hpp"

// Static metod for logging to the console
void Logger::Log(const std::string &message) {
    
    std::cout << message << std::endl;
}