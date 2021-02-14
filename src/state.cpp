#include <Arduino.h>

#include <logging.h>
#include <state.h>

void switchOpMode(OpMode new_mode) {
  if (state.mode != new_mode) {
    state.mode = new_mode;
    log(LogLevel::INFO, F("Switched to a new operation mode: %s"),
        op_mode_str[static_cast<int>(new_mode)]);
  } else {
    
  }
}