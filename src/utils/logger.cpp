#include "logger.hpp"

std::auto_ptr<LoggingAdapter> Logger::adapter(new ConsoleLoggingAdapter());
