#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

#include <AccelStepper.h>
#include <Adafruit_NeoPixel.h>

#include <configuration.h>
#include <events.h>
#include <HC_SR04.h>

enum class OpMode { IDLE, ERROR, DEBUG };
const char *const op_mode_str[] = {"IDLE", "ERROR", "DEBUG"};

struct State {
  OpMode mode = OpMode::IDLE;
  EventQueue event_queue;
  char serial_buffer[kSerialBufferSize];
  size_t serial_buffer_index = 0;
  int8_t last_error = -1;
  bool prompt_active = false;
  AccelStepper stepperA;
  AccelStepper stepperB;
  Adafruit_NeoPixel pixels;
  HC_SR04 sensor;
  // bool sensor_measuring = false;

  State()
      : stepperA{AccelStepper::FULL4WIRE, kStepperAPin1, kStepperAPin2,
                 kStepperAPin3, kStepperAPin4},
        stepperB{AccelStepper::FULL4WIRE, kStepperBPin1, kStepperBPin2,
                 kStepperBPin3, kStepperBPin4},
        pixels{kNumPixels, kPixelPin, NEO_GRB + NEO_KHZ800},
        sensor{kSensorTrigPin, kSensorEchoPin, 0} {}
};

// Global state of the machine
extern State state;

void switchOpMode(OpMode new_mode);

#endif // INCLUDE_STATE_H_
