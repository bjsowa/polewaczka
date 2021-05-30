#include <ctype.h>

#include <Arduino.h>

#include <logging.h>
#include <state.h>
#include <terminal.h>

void Terminal::processCommand() {
  log(LogLevel::DEBUG, "Processing command: \'%s\'", buffer_);

  if (!strcmp(buffer_, "debug")) {
    addEvent(Event{Event::DEBUG});
    return;
  }

  if (state.mode == OpMode::DEBUG) {
    if (!strcmp(buffer_, "d")) {
      log(LogLevel::INFO, "Moving left by %d steps", 500);
      state.stepperA.moveTo(500);
      return;
    } else if (!strcmp(buffer_, "a")) {
      log(LogLevel::INFO, "Moving right by %d steps", 500);
      state.stepperA.move(-500);
      return;
    } else if (!strcmp(buffer_, "c")) {
      log(LogLevel::INFO, "Moving left by %d steps", 400);
      state.stepperB.move(400);
      return;
    } else if (!strcmp(buffer_, "z")) {
      log(LogLevel::INFO, "Moving right by %d steps", 400);
      state.stepperB.move(-400);
      return;
    } else if (!strcmp(buffer_, "r")) {
      state.pixels.setPixelColor(0, Adafruit_NeoPixel::Color(255, 0, 0));
      return;
    } else if (!strcmp(buffer_, "g")) {
      state.pixels.setPixelColor(0, Adafruit_NeoPixel::Color(0, 255, 0));
      return;
    } else if (!strcmp(buffer_, "b")) {
      state.pixels.setPixelColor(0, Adafruit_NeoPixel::Color(0, 0, 255));
      return;
    } else if (!strcmp(buffer_, "w")) {
      state.pixels.setPixelColor(0, Adafruit_NeoPixel::Color(255, 255, 255));
      return;
    } else if (!strcmp(buffer_, "ron")) {
      digitalWrite(kRelayPin, LOW);
      return;
    } else if (!strcmp(buffer_, "roff")) {
      digitalWrite(kRelayPin, HIGH);
      return;
    } else if (!strcmp(buffer_, "m")) {
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

  log(LogLevel::ERROR, "Unknown command: \'%s\'", buffer_);
}

void Terminal::handleRxAvailable() {
  while (console_.available()) {
    char c = static_cast<char>(console_.read());

    if (c == '\r')
      continue;

    if (c == '\n') {
      if (state.mode == OpMode::DEBUG) {
        // Temporarily disable prompt
        console_.println();
        prompt_active = false;
      }

      processCommand();
      buffer_index_ = 0;
      buffer_[buffer_index_] = '\0';

      if (state.mode == OpMode::DEBUG) {
        // Reactivate new prompt
        printPrompt();
        prompt_active = true;
      }
    } else if (isalnum(c) || isspace(c)) {
      buffer_[buffer_index_++] = c;

      if (state.mode == OpMode::DEBUG)
        Serial.print(c);

      // Check for buffer overflow
      if (buffer_index_ == kTerminalBufferSize) {
        buffer_index_ = 0;
        buffer_[buffer_index_] = '\0';
        error(Error::SERIAL_BUFFER_OVERFLOW);
      } else {
        buffer_[buffer_index_] = '\0';
      }
    } else if (c == '\b' && kFormattedLogs) { // Backspace
      if (buffer_index_ > 0) {
        Serial.print("\b \b");
        buffer_[--buffer_index_] = '\0';
      }
    }
  }
}

void Terminal::printPrompt() {
  console_.print("> ");
  console_.print(buffer_);
}