#include <Arduino.h>

#include <AccelStepper.h>
#include <CircularBuffer.h>

#include <configuration.h>
#include <events.h>
#include <serial.h>
#include <state.h>

State state;

void setup() { Serial.begin(kSerialBaud); }

void loop() {
  while (!state.event_queue.isEmpty()) {
    Event event = state.event_queue.pop();
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
  case OpMode::DEBUG:
    break;
  }
}