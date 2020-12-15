#include <Arduino.h>

#include <CircularBuffer.h>
#include <AccelStepper.h>

#include <configuration.h>
#include <events.h>
#include <state.h>

State state;
EventQueue event_queue;

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
      switchOpMode(OpMode::ERROR);
      break;

    case Event::DEBUG:
      Serial.println("DEBUG");
      switchOpMode(OpMode::DEBUG);
      
      break;

    default:
      Serial.println("Unsupported event");
    }
  }

  switch (state.mode) {
  case OpMode::IDLE:
    break;
  case OpMode::ERROR:
    break;
  }
}