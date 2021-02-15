#include <Arduino.h>

#include <logging.h>
#include <serial.h>
#include <state.h>

void printState() {}

void processCommand() {
  log(LogLevel::DEBUG, "Processing command: \'%s\'", state.serial_buffer);

  if (!strcmp(state.serial_buffer, "debug")) {
    addEvent(Event{Event::DEBUG});
  }
  else {
    log(LogLevel::ERROR, "Unknown command: \'%s\'", state.serial_buffer);
  }
}

void processSerial() {
  while (Serial.available()) {
    char c = static_cast<char>(Serial.read());

    if (c == '\r')
      continue;

    if (c == '\n') {
      // Temporarily disable prompt
      if (state.mode == OpMode::DEBUG) {
        Serial.println();
        state.prompt_active = false;
      }

      processCommand();
      state.serial_buffer_index = 0;

      // Reactivate new prompt
      if (state.mode == OpMode::DEBUG) {
        Serial.print("> ");
        state.prompt_active = true;
      }
    } else {
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
    }
  }
}