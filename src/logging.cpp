#include <Arduino.h>

#include <configuration.h>
#include <logging.h>
#include <state.h>

void printLogLevel(LogLevel lvl) {
  Serial.print(log_level_str[static_cast<int8_t>(lvl)]);
  Serial.print(": ");
}

void preLog() {
  if (state.prompt_active) {
    Serial.println();
  }
}

void postLog() {
  if (state.prompt_active) {
    Serial.print("> ");
    Serial.print(state.serial_buffer);
  }
}

void logEvent(Event e) {
  int length;
  char buf[kLogBufferSize];

  length = sprintf(buf, "Received Event: ");
  switch (e.type) {
  case Event::DEBUG:
    snprintf(buf + length, kLogBufferSize - length, "DEBUG");
    break;
  }

  preLog();
  printLogLevel(LogLevel::DEBUG);
  Serial.println(buf);
  postLog();
}

void log(LogLevel lvl, const char *fmt, ...) {
  char buf[kLogBufferSize];
  va_list ap;

  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);

  preLog();
  printLogLevel(lvl);
  Serial.println(buf);
  postLog();

  va_end(ap);
}

void log(LogLevel lvl, const __FlashStringHelper *fmt, ...) {
  char buf[kLogBufferSize];
  va_list ap;

  va_start(ap, fmt);
  vsnprintf_P(buf, sizeof(buf), (const char *)fmt, ap);

  preLog();
  printLogLevel(lvl);
  Serial.println(buf);
  postLog();

  va_end(ap);
}