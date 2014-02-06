#ifndef LOGGINGADAPTER_H_
#define LOGGINGADAPTER_H_

#include <string>

class LoggingAdapter
{
	public:
		LoggingAdapter();
		virtual ~LoggingAdapter();

		virtual void debug(const std::string & message) const = 0;
		virtual void info(const std::string & message) const = 0;
		virtual void warn(const std::string & message) const = 0;
		virtual void error(const std::string & message) const = 0;
};

#endif /* LOGGINGADAPTER_H_ */
