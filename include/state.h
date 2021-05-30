#pragma once

#include <AccelStepper.h>
#include <Adafruit_NeoPixel.h>

#include <HC_SR04.h>
#include <configuration.h>
#include <events.h>

enum class OpMode { IDLE, ERROR, DEBUG };
const char *const op_mode_str[] = {"IDLE", "ERROR", "DEBUG"};

struct State {
  OpMode mode = OpMode::IDLE;
  EventQueue event_queue;
  int8_t last_error = -1;
  AccelStepper stepperA =
      AccelStepper(AccelStepper::FULL4WIRE, kStepperAPin1, kStepperAPin2,
                   kStepperAPin3, kStepperAPin4);
  AccelStepper stepperB =
      AccelStepper(AccelStepper::FULL4WIRE, kStepperBPin1, kStepperBPin2,
                   kStepperBPin3, kStepperBPin4);
  Adafruit_NeoPixel pixels =
      Adafruit_NeoPixel(kNumPixels, kPixelPin, NEO_GRB + NEO_KHZ800);
  HC_SR04 sensor = HC_SR04(kSensorTrigPin, kSensorEchoPin, 0);
};

// Global state of the machine
extern State state;

void switchOpMode(OpMode new_mode);
