#include <Arduino.h>

#include <configuration.h>
#include <logging.h>

void printLogLevel(LogLevel lvl) {
  Serial.print(log_level_str[static_cast<int8_t>(lvl)]);
  Serial.print(": ");
}

void logEvent(Event e) {
  printLogLevel(LogLevel::DEBUG);
  Serial.print(F("Received event: "));
  switch (e.type) {
  case Event::DEBUG:
    Serial.println(F("DEBUG"));
    break;
  }
}

void log(LogLevel lvl, const char *fmt, ...) {
  char buf[kLogBufferSize];
  va_list ap;

  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);

  printLogLevel(lvl);
  Serial.println(buf);

  va_end(ap);
}

void log(LogLevel lvl, const __FlashStringHelper *fmt, ...) {
  char buf[kLogBufferSize];
  va_list ap;

  va_start(ap, fmt);
  vsnprintf_P(buf, sizeof(buf), (const char *)fmt, ap);

  printLogLevel(lvl);
  Serial.println(buf);

  va_end(ap);
}