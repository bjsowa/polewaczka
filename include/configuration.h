#ifndef INCLUDE_CONFIGURATION_H_
#define INCLUDE_CONFIGURATION_H_

#include <stdint.h>

#include <logging.h>

// The maximum verbosity level of printed logs
const LogLevel kLogVerbosityLevel = LogLevel::DEBUG;

// Whether to use ANSI Escape sequences for formatted logs
const bool kFormattedLogs = true;

// Baud rate for serial communication
const uint32_t kSerialBaud = 115200;

// Size of the buffer for serial read data
const size_t kSerialBufferSize = 100;

// Size of the buffer for a single log message
const size_t kLogBufferSize = 100;

// Size of the buffer for processed events
const uint16_t kEventQueueCapacity = 10;

// Stepper A configuration
const uint8_t kStepperAPin1 = 5;
const uint8_t kStepperAPin2 = 6;
const uint8_t kStepperAPin3 = 3;
const uint8_t kStepperAPin4 = 4;
const float kStepperAMaxSpeed = 280.0;
const float kStepperAAcceleration = 200.0;

// Stepper B configuration
const uint8_t kStepperBPin1 = 28;
const uint8_t kStepperBPin2 = 29;
const uint8_t kStepperBPin3 = 30;
const uint8_t kStepperBPin4 = 31;
const float kStepperBMaxSpeed = 720.0;
const float kStepperBAcceleration = 5000.0;

const uint8_t kSensorTrigPin = 14;
const uint8_t kSensorEchoPin = 12;

const uint8_t kNumPixels = 1;
const uint8_t kPixelPin = 20;

const uint8_t kRelayPin = 2;

#endif // INCLUDE_CONFIGURATION_H_
