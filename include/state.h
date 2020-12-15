#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

enum class OpMode {
  IDLE,
  ERROR,
};

struct State {
  OpMode mode;
};

extern State state;

#endif // INCLUDE_STATE_H_
