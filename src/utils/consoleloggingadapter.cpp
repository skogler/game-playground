#include "consoleloggingadapter.hpp"

ConsoleLoggingAdapter::ConsoleLoggingAdapter()
{
}

ConsoleLoggingAdapter::~ConsoleLoggingAdapter()
{
}

void ConsoleLoggingAdapter::debug(const std::string& message) const
{
    writeToConsole(" - DEBUG: " + message);
}

void ConsoleLoggingAdapter::info(const std::string& message) const
{
    writeToConsole(" - INFO: " + message);
}

void ConsoleLoggingAdapter::warn(const std::string& message) const
{
    writeToConsole(" - WARNING: " + message);
}

void ConsoleLoggingAdapter::error(const std::string& message) const
{
    writeToConsole(" - ERROR: " + message);
}
