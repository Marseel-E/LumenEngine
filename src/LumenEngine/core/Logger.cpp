#include "Logger.hpp"

#include <ctime>
#include <iostream>

namespace Engine {

constexpr const char* COLOR_GREEN = "\033[32m";
constexpr const char* COLOR_YELLOW = "\033[33m";
constexpr const char* COLOR_RED = "\033[31m";
constexpr const char* COLOR_RESET = "\033[0m";

void Logger::Init() {
	Info("Logger Initialized");
};

void Logger::Info(const std::string& message) {
	Print("[INFO]", message, COLOR_GREEN);
};

void Logger::Info(const std::string& message, const std::string& attachment) {
	Print("[INFO]", message + ": " + attachment, COLOR_GREEN);
};

void Logger::Warn(const std::string& message) {
	Print("[WARNING]", message, COLOR_YELLOW);
};

void Logger::Error(const std::string& message) {
	Print("[ERROR]", message, COLOR_RED);
};

void Logger::Error(const std::string& message, const std::string& errorMessage) {
	Print("[ERROR]", message + ": " + errorMessage, COLOR_RED);
};

void Logger::Print(const std::string& levelTag, const std::string& message, const char* colorCode) {
	std::time_t now = std::time(nullptr);

	char timestamp[20];

	std::strftime(timestamp, sizeof(timestamp), "%H:%M:%S", std::localtime(&now));

	std::cout << colorCode << levelTag << " [" << timestamp << "] " << message << COLOR_RESET << std::endl;
};

} // namespace Engine