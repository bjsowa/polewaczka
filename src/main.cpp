#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <CircularBuffer.h>

#include <configuration.h>
#include <events.h>
#include <logging.h>
#include <serial.h>
#include <state.h>

State state;

void setup() {
  Serial.begin(kSerialBaud);

  pinMode(kSensorTrigPin, OUTPUT); // Sets the trigPin as an Output
  digitalWrite(kSensorTrigPin, LOW);
  pinMode(kSensorEchoPin, INPUT);  // Sets the echoPin as an Input

  state.stepperA.setMaxSpeed(kStepperAMaxSpeed);
  state.stepperA.setAcceleration(kStepperAAcceleration);
  state.stepperB.setMaxSpeed(kStepperBMaxSpeed);
  state.stepperB.setAcceleration(kStepperBAcceleration);

  state.pixels.begin();
  state.pixels.setBrightness(255);

  pinMode(kRelayPin, OUTPUT);
  digitalWrite(kRelayPin, HIGH);
}

void loop() {
  // Process new events
  while (!state.event_queue.isEmpty()) {
    Event event = state.event_queue.pop();
    logEvent(event);

    switch (event.type) {
    case Event::DEBUG:
      switchOpMode(OpMode::DEBUG);
      break;

    default:
      error(Error::UNSUPPORTED_EVENT);
    }
  }

  // Perform operations common to all operation modes
  processSerial();
  state.stepperA.run();
  state.stepperB.run();
  state.pixels.show();

  if (!state.stepperA.isRunning())
    state.stepperA.disableOutputs();
  if (!state.stepperB.isRunning())
    state.stepperB.disableOutputs();

  // if (state.sensor_measuring && state.sensor.isFinished()) {
  //   log(LogLevel::INFO, "Finished sensor: %d", state.sensor.getRange());
  //   state.sensor_measuring = false;
  // }

  // Perform operations specific to the current operation mode
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