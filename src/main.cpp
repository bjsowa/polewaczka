#include <Arduino.h>

#include <CircularBuffer.h>

#include <configuration.h>
#include <events.h>
#include <state.h>

State state;
CircularBuffer<Event, kEventQueueCapacity> event_queue;

void setup() {
  Serial.begin(kSerialBaud);

  state.mode = OpMode::IDLE;
}

void loop() {
  while (!event_queue.isEmpty()) {
    Event event = event_queue.pop();
    Serial.print("Received event: ");

    switch (event.type) {
    case Event::ERROR:
      Serial.print("ERROR: ");
      Serial.println(error_msgs[event.data[0]]);
      state.mode = OpMode::ERROR;
    default:
      Serial.println("Unsupported event");
    }
  }
}