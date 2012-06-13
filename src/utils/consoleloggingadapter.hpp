#ifndef CONSOLELOGGINGADAPTER_H_
#define CONSOLELOGGINGADAPTER_H_

#include "loggingadapter.hpp"
#include <iostream>
#include <string>
#include <time.h>

class ConsoleLoggingAdapter: public LoggingAdapter
{
public:
	ConsoleLoggingAdapter();
	virtual ~ConsoleLoggingAdapter();

	virtual void debug(const std::string& message) const;
	virtual void info(const std::string& message) const;
	virtual void warn(const std::string& message) const;
	virtual void error(const std::string& message) const;

protected:
	inline void writeToConsole(const std::string& message) const
	{
		time_t rawtime;
		struct tm * timeinfo;
		char timeBuffer[9];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(timeBuffer, 9, "%H:%M:%S", timeinfo);
		std::cout << timeBuffer << message << std::endl;
	}

};

#endif /* CONSOLELOGGINGADAPTER_H_ */
