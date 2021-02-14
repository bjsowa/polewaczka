#include <Arduino.h>

#include <serial.h>
#include <state.h>

void print_state() {}

void process_command() {
  Serial.println(state.serial_buffer);
}

void process_serial() {
  while (Serial.available()) {
    char c = static_cast<char>(Serial.read());

    if (c == '\r')
      continue;

    if (c == '\n') {
      state.serial_buffer[state.serial_buffer_index] = 0;
      process_command();
      state.serial_buffer_index = 0;
    } 
    else {
      state.serial_buffer[state.serial_buffer_index++] = c; 

      // Check for buffer overflow
      if (state.serial_buffer_index == kSerialBufferSize) {
        error(Error::SERIAL_BUFFER_OVERFLOW);
        state.serial_buffer_index = 0;
      }
    }
  }
}