#ifndef INCLUDE_EVENTS_H_
#define INCLUDE_EVENTS_H_

#include <stdint.h>

#include <CircularBuffer.h>

#include <configuration.h>

struct Event {
  enum {
    ERROR,
  } type;

  // a buffer for additional information about the event
  uint8_t data[4];
};

const char *const error_msgs[] = {
    "Event buffer overflow", // 0
};

extern CircularBuffer<Event, kEventQueueCapacity> event_queue;

// Adds an error event to the beginning of the queue
void error(uint8_t error_id);

// Adds an event to the end of the queue
void addEvent(Event *e);

#endif // INCLUDE_EVENTS_H_
