#pragma once

#include <memory>
#include <string>

namespace Engine {

enum class LogLevel { Info, Warning, Error };

class Logger {
public:
	static void Init();

	template <typename... Args>
	static void Log(LogLevel level, const char* message, Args... args);

	static void Info(const std::string& message);
	static void Info(const std::string& message, const std::string& attachment);

	static void Warn(const std::string& message);

	static void Error(const std::string& message);
	static void Error(const std::string& message, const std::string& errorMessage);

private:
	static void Print(const std::string& levelTag, const std::string& message, const char* colorCode);
};

} // namespace Engine