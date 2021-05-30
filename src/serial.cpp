#include <ctype.h>

#include <Arduino.h>

#include <logging.h>
#include <serial.h>
#include <state.h>

void printState() {}

void processCommand() {
  log(LogLevel::DEBUG, "Processing command: \'%s\'", state.serial_buffer);

  if (!strcmp(state.serial_buffer, "debug")) {
    addEvent(Event{Event::DEBUG});
    return;
  }

  if (state.mode == OpMode::DEBUG) {
    if (!strcmp(state.serial_buffer, "d")) {
      log(LogLevel::INFO, "Moving left by %d steps", 500);
      state.stepperA.moveTo(500);
      return;
    } else if (!strcmp(state.serial_buffer, "a")) {
      log(LogLevel::INFO, "Moving right by %d steps", 500);
      state.stepperA.move(-500);
      return;
    } else if (!strcmp(state.serial_buffer, "c")) {
      log(LogLevel::INFO, "Moving left by %d steps", 400);
      state.stepperB.move(400);
      return;
    } else if (!strcmp(state.serial_buffer, "z")) {
      log(LogLevel::INFO, "Moving right by %d steps", 400);
      state.stepperB.move(-400);
      return;
    } else if (!strcmp(state.serial_buffer, "r")) {
      state.pixels.setPixelColor(0, Adafruit_NeoPixel::Color(255, 0, 0));
      return;
    } else if (!strcmp(state.serial_buffer, "g")) {
      state.pixels.setPixelColor(0, Adafruit_NeoPixel::Color(0, 255, 0));
      return;
    } else if (!strcmp(state.serial_buffer, "b")) {
      state.pixels.setPixelColor(0, Adafruit_NeoPixel::Color(0, 0, 255));
      return;
    } else if (!strcmp(state.serial_buffer, "w")) {
      state.pixels.setPixelColor(0, Adafruit_NeoPixel::Color(255, 255, 255));
      return;
    } else if (!strcmp(state.serial_buffer, "ron")) {
      digitalWrite(kRelayPin, LOW);
      return;
    } else if (!strcmp(state.serial_buffer, "roff")) {
      digitalWrite(kRelayPin, HIGH);
      return;
    } else if (!strcmp(state.serial_buffer, "m")) {
      log(LogLevel::INFO, "Measuring distance");

      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(kSensorTrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(kSensorTrigPin, LOW);

      // Reads the echoPin, returns the sound wave travel time in microseconds
      unsigned long duration = pulseIn(kSensorEchoPin, HIGH);
      log(LogLevel::INFO, "Finished measuring: %d", duration);

      // state.sensor.start();
      // state.sensor_measuring = true;
      return;
    }
  }

  log(LogLevel::ERROR, "Unknown command: \'%s\'", state.serial_buffer);
}

void processSerial() {
  while (Serial.available()) {
    char c = static_cast<char>(Serial.read());

    if (c == '\r')
      continue;

    if (c == '\n') {
      if (state.mode == OpMode::DEBUG) {
        // Temporarily disable prompt
        Serial.println();
        state.prompt_active = false;
      }

      processCommand();
      state.serial_buffer_index = 0;
      state.serial_buffer[state.serial_buffer_index] = '\0';

      if (state.mode == OpMode::DEBUG) {
        // Reactivate new prompt
        Serial.print("> ");
        state.prompt_active = true;
      }
    } else if (isalnum(c) || isspace(c)) {
      state.serial_buffer[state.serial_buffer_index++] = c;

      if (state.mode == OpMode::DEBUG)
        Serial.print(c);

      // Check for buffer overflow
      if (state.serial_buffer_index == kSerialBufferSize) {
        state.serial_buffer_index = 0;
        state.serial_buffer[state.serial_buffer_index] = '\0';
        error(Error::SERIAL_BUFFER_OVERFLOW);
      } else {
        state.serial_buffer[state.serial_buffer_index] = '\0';
      }
    } else if (c == '\b' && kFormattedLogs) { // Backspace
      if (state.serial_buffer_index > 0) {
        Serial.print("\b \b");
        state.serial_buffer[--state.serial_buffer_index] = '\0';
      }
    }
  }
}