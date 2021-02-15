#ifndef INCLUDE_EVENTS_H_
#define INCLUDE_EVENTS_H_

#include <stdint.h>

#include <CircularBuffer.h>

#include <configuration.h>

struct Event {
  enum {
    DEBUG, // Debug mode requested
  } type;

  // a buffer for additional information about the event
  uint8_t data[4];
};

enum class Error {
  EVENT_QUEUE_OVERFLOW,
  SERIAL_BUFFER_OVERFLOW,
  UNSUPPORTED_EVENT,
};

const char *const error_msgs[] = {
    "Event queue overflow",
    "Serial buffer overflow",
    "Unsupported Event",
};

typedef CircularBuffer<Event, kEventQueueCapacity> EventQueue;

//
void error(Error err);

// Add an event to the end of the queue
void addEvent(Event e);

#endif // INCLUDE_EVENTS_H_
