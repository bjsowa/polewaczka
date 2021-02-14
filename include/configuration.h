#ifndef INCLUDE_CONFIGURATION_H_
#define INCLUDE_CONFIGURATION_H_

#include <stdint.h>

// Baud rate for serial communication
const uint32_t kSerialBaud = 115200;

// Size of the serial buffer
const size_t kSerialBufferSize = 100;

// Size of the buffer for processed events
const uint16_t kEventQueueCapacity = 10;

// Stepper A configuration
const uint8_t kStepperAPin1 = 5;
const uint8_t kStepperAPin2 = 6;
const uint8_t kStepperAPin3 = 3;
const uint8_t kStepperAPin4 = 4;
const float kStepperAMaxSpeed = 140.0;
const float kStepperAAcceleration = 200.0;

// Stepper B configuration
const uint8_t kStepperBPin1 = 28;
const uint8_t kStepperBPin2 = 29;
const uint8_t kStepperBPin3 = 30;
const uint8_t kStepperBPin4 = 31;
const float kStepperBMaxSpeed = 180.0;
const float kStepperBAcceleration = 300.0;

#endif // INCLUDE_CONFIGURATION_H_
