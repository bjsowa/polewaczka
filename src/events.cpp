#include <events.h>
#include <state.h>

void error(uint8_t error_id) {
  Event e;
  e.type = Event::ERROR;
  e.data[0] = error_id;
  state.event_queue.unshift(e);
}

void addEvent(Event *e) {
  if (state.event_queue.isFull()) {
    error(0);
  } else {
    state.event_queue.push(*e);
  }
}