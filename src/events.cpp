#include <Arduino.h>

#include <events.h>
#include <state.h>

void error(Error err) {
  int8_t error_code = static_cast<int8_t>(err);
  state.last_error = error_code;

  Serial.print(F("ERROR: "));
  Serial.println(error_msgs[error_code]);

  if (state.mode != OpMode::DEBUG)
    switchOpMode(OpMode::ERROR);
  
  state.event_queue.clear();
}

void addEvent(Event e) {
  if (state.event_queue.isFull()) {
    error(Error::EVENT_QUEUE_OVERFLOW);
  } else {
    state.event_queue.push(e);
  }
}