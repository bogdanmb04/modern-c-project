#include "logging.h"
import <format>;


std::string_view LogLevelToString(Logger::Level level)
{
	switch (level)
	{
		using enum Logger::Level;
	case Info:
		return "Info";
	case Warning:
		return "Warning";
	case Error:
		return "Error";
	default:
		return "";
	}
}

Logger::Logger(std::ostream& os, Logger::Level minimumLevel) :
	m_os{ os },
	m_minimumLevel{ minimumLevel }
{
	// Empty
}

void Logger::Log(std::string_view message, Level level)
{
	if (static_cast<int>(level) < static_cast<int>(m_minimumLevel))
		return;

	m_os << std::format("[{}] {}\n", LogLevelToString(level), message);
}

void Logger::SetMinimumLogLevel(Level level)
{
	m_minimumLevel = level;
}