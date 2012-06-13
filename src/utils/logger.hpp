#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>
#include <auto_ptr.h>

#include "loggingadapter.hpp"
#include "consoleloggingadapter.hpp"
#include "config.h"

/**
 * This class should be used for logging in the whole program.
 * It can have different backends(adapters) and debug and info calls
 * should be optimized out at compile time if the
 * LOG_DEBUG and LOG_INFO defines are changed to 0. (In CMakeLists.txt)
 */
class Logger
{
public:
	inline static void debug(const std::string& message)
	{
#if LOG_DEBUG == 1
		adapter->debug(message);
#endif
	}

	inline static void info(const std::string& message)
	{
#if LOG_INFO == 1
		adapter->info(message);
#endif
	}

	inline static void warn(const std::string& message)
	{
		adapter->warn(message);
	}

	inline static void error(const std::string& message)
	{
		adapter->error(message);
	}

	inline static void setLoggingAdapter(LoggingAdapter * adapter)
	{
		Logger::adapter.reset(adapter);
	}

private:
	static std::auto_ptr<LoggingAdapter> adapter;

protected:
	Logger() {};
	virtual ~Logger() {};
};

#endif /* LOGGER_HPP_ */

