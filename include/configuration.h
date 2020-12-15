#ifndef INCLUDE_CONFIGURATION_H_
#define INCLUDE_CONFIGURATION_H_

#include <stdint.h>

// Baud rate for serial communication
const uint32_t kSerialBaud = 115200;

// Size of the buffer for processed events
const uint16_t kEventQueueCapacity = 100;

#endif // INCLUDE_CONFIGURATION_H_
