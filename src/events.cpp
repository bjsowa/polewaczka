#include <Arduino.h>

#include <events.h>
#include <logging.h>
#include <state.h>

void logEvent(const Event e) {
  int length;
  char buf[kLogBufferSize];

  length = sprintf(buf, "Received Event: ");
  switch (e.type) {
  case Event::DEBUG:
    snprintf(buf + length, kLogBufferSize - length, "DEBUG");
    break;
  }

  log(LogLevel::DEBUG, buf);
}

void error(const Error err) {
  int8_t error_code = static_cast<int8_t>(err);
  state.last_error = error_code;

  log(LogLevel::ERROR, error_msgs[error_code]);

  if (state.mode != OpMode::DEBUG)
    switchOpMode(OpMode::ERROR);
}

void addEvent(const Event e) {
  if (state.event_queue.isFull()) {
    error(Error::EVENT_QUEUE_OVERFLOW);
  } else {
    state.event_queue.push(e);
  }
}