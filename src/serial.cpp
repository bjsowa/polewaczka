#include <ctype.h>

#include <Arduino.h>

#include <logging.h>
#include <serial.h>
#include <state.h>

void printState() {}

void processCommand() {
  log(LogLevel::DEBUG, "Processing command: \'%s\'", state.serial_buffer);

  if (!strcmp(state.serial_buffer, "debug")) {
    addEvent(Event{Event::DEBUG});
  } else {
    log(LogLevel::ERROR, "Unknown command: \'%s\'", state.serial_buffer);
  }
}

void processSerial() {
  while (Serial.available()) {
    char c = static_cast<char>(Serial.read());

    if (c == '\r')
      continue;

    if (c == '\n') {
      if (state.mode == OpMode::DEBUG) {
        // Temporarily disable prompt
        Serial.println();
        state.prompt_active = false;
      }

      processCommand();
      state.serial_buffer_index = 0;
      state.serial_buffer[state.serial_buffer_index] = '\0';

      if (state.mode == OpMode::DEBUG) {
        // Reactivate new prompt
        Serial.print("> ");
        state.prompt_active = true;
      }
    } else if (isalnum(c) || isspace(c)) {
      state.serial_buffer[state.serial_buffer_index++] = c;

      if (state.mode == OpMode::DEBUG)
        Serial.print(c);

      // Check for buffer overflow
      if (state.serial_buffer_index == kSerialBufferSize) {
        state.serial_buffer_index = 0;
        state.serial_buffer[state.serial_buffer_index] = '\0';
        error(Error::SERIAL_BUFFER_OVERFLOW);
      } else {
        state.serial_buffer[state.serial_buffer_index] = '\0';
      }
    } else if (c == '\b' && kFormattedLogs) { // Backspace
      if (state.serial_buffer_index > 0) {
        Serial.print("\b \b");
        state.serial_buffer[--state.serial_buffer_index] = '\0';
      }
    }
  }
}