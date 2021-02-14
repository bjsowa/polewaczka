#include <Arduino.h>

#include <logging.h>

void logEvent(Event e) {
  Serial.print(F("Received event: "));
  switch (e.type) {
  case Event::DEBUG:
    Serial.print(F("DEBUG"));
  }
  Serial.println();
}

void logError(const char *msg)
{
  Serial.print(F("ERROR: "));
  Serial.println(msg);
}