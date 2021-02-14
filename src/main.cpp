#include <Arduino.h>

#include <AccelStepper.h>
#include <CircularBuffer.h>

#include <configuration.h>
#include <events.h>
#include <logging.h>
#include <serial.h>
#include <state.h>

State state;

void setup() { Serial.begin(kSerialBaud); }

void loop() {
  while (!state.event_queue.isEmpty()) {
    Event event = state.event_queue.pop();
    logEvent(event);

    switch (event.type) {
    case Event::DEBUG:
      switchOpMode(OpMode::DEBUG);
      break;

    default:
      logError("Unsupperted Event");
    }
  }

  process_serial();

  switch (state.mode) {
  case OpMode::IDLE:
    break;
  case OpMode::ERROR:
    // Display error code
    break;
  case OpMode::DEBUG:
    //
    break;
  }
}