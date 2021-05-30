#include <Arduino.h>

#include <logging.h>
#include <state.h>
#include <terminal.h>

extern Terminal terminal;

void switchOpMode(OpMode new_mode) {
  if (state.mode != new_mode) {
    OpMode prev_mode = state.mode;
    log(LogLevel::INFO, F("Switched to a new operation mode: %s"),
        op_mode_str[static_cast<int>(new_mode)]);
    state.mode = new_mode;

    // Prepare for the new operation mode
    switch (new_mode) {
    case OpMode::IDLE:

      break;
    case OpMode::DEBUG:
      terminal.prompt_active = true;
      log(LogLevel::INFO, F("Debug mode activated. Type \'help\' for a list of "
                            "available commands."));
      noInterrupts();
      state.event_queue.clear();
      interrupts();
      break;
    case OpMode::ERROR:
      noInterrupts();
      state.event_queue.clear();
      interrupts();
      break;
    }
  } else {
    log(LogLevel::WARNING,
        F("Trying to switch to the already active operation mode: %s"),
        op_mode_str[static_cast<int>(new_mode)]);
  }
}