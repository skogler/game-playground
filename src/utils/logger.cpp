#include "logger.hpp"

boost::scoped_ptr<LoggingAdapter> Logger::adapter(new ConsoleLoggingAdapter());
