#include <Arduino.h>

#include <state.h>

void switchOpMode(OpMode new_mode) {
  if (state.mode != new_mode) {
    state.mode = new_mode;
    Serial.print("Switched to a new operation mode: ");
    Serial.println(op_mode_str[static_cast<int>(new_mode)]);
  }
}