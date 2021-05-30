#pragma once

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };
const char *const log_level_str[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

void log(const LogLevel lvl, const char *fmt, ...);
void log(const LogLevel lvl, const __FlashStringHelper *fmt, ...);
