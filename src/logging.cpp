#include <Arduino.h>

#include <configuration.h>
#include <logging.h>
#include <state.h>
#include <terminal.h>

extern Terminal terminal;

void printLog(const LogLevel lvl, const char *msg) {

  if (terminal.prompt_active) {
    if (kFormattedLogs) {
      Serial.print("\r");
      Serial.print("\033[K");
    }
    else {
      Serial.println();
    }
  }

  if (kFormattedLogs) {
    // Set Color depending on the log level
    switch (lvl) {
    case LogLevel::DEBUG:
      Serial.print("\033[32m"); // Green
      break;
    case LogLevel::INFO:
      Serial.print("\033[34m"); // Blue
      break;
    case LogLevel::WARNING:
      Serial.print("\033[33m"); // Yellow
      break;
    case LogLevel::ERROR:
      Serial.print("\033[31m"); // Red
    }
  } else {
    // Print a string indicating the log level
    Serial.print("[");
    Serial.print(log_level_str[static_cast<size_t>(lvl)]);
    Serial.print("]: ");
  }

  // Print the actual log message
  Serial.println(msg);

  if (kFormattedLogs) {
    // Reset graphic attributes
    Serial.print("\033[0m");
  }

  if (terminal.prompt_active) {
    // Reprint the prompt and the current buffer
    terminal.printPrompt();
  }
}

void log(const LogLevel lvl, const char *fmt, ...) {
  char buf[kLogBufferSize];
  va_list ap;

  if (lvl < kLogVerbosityLevel)
    return;

  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);

  printLog(lvl, buf);

  va_end(ap);
}

void log(const LogLevel lvl, const __FlashStringHelper *fmt, ...) {
  char buf[kLogBufferSize];
  va_list ap;

  if (lvl < kLogVerbosityLevel)
    return;

  va_start(ap, fmt);
  vsnprintf_P(buf, sizeof(buf), (const char *)fmt, ap);

  printLog(lvl, buf);

  va_end(ap);
}