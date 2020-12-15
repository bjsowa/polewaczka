#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

enum class OpMode {
  IDLE,
  ERROR,
  DEBUG,
};

const char *const op_mode_str[] = {
    "IDLE",
    "ERROR",
    "DEBUG",
};

struct State {
  OpMode mode;
};

extern State state;

void switchOpMode(OpMode new_mode);

#endif // INCLUDE_STATE_H_
