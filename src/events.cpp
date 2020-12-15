#include <events.h>

void error(uint8_t error_id) {
  Event e;
  e.type = Event::ERROR;
  e.data[0] = error_id;
  event_queue.unshift(e);
}

void addEvent(Event *e) {
  if (event_queue.isFull()) {
    error(0);
  } else {
    event_queue.push(*e);
  }
}