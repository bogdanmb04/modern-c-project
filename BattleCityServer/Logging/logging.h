#include <iostream>
#include <string_view>


class __declspec(dllexport) Logger
{
public:
	enum class Level : char
	{
		Info,
		Warning,
		Error
	};

public:
	Logger(std::ostream& os, Level minimumLevel = Level::Info);

	void Log(std::string_view message, Level level);

	void SetMinimumLogLevel(Level level);

private:
	std::ostream& m_os;
	Level m_minimumLevel;
};