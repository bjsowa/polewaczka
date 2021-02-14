#ifndef INCLUDE_LOGGING_H_
#define INCLUDE_LOGGING_H_

#include <events.h>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };
const char *const log_level_str[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

void logEvent(Event e);
void log(LogLevel lvl, const char *fmt, ...);
void log(LogLevel lvl, const __FlashStringHelper *fmt, ...);

#endif // INCLUDE_LOGGING_H_