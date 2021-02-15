#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

#include <events.h>

enum class OpMode { IDLE, ERROR, DEBUG };
const char *const op_mode_str[] = {"IDLE", "ERROR", "DEBUG"};

struct State {
  OpMode mode = OpMode::IDLE;
  EventQueue event_queue;
  char serial_buffer[kSerialBufferSize];
  size_t serial_buffer_index = 0;
  int8_t last_error = -1;
  bool prompt_active = false;
};

// Global state of the machine
extern State state;

void switchOpMode(OpMode new_mode);

#endif // INCLUDE_STATE_H_
