#pragma once

#include <Stream.h>

#include <configuration.h>

// A very simple terminal emulator and shell
class Terminal {
  Stream &console_;

  char buffer_[kTerminalBufferSize];
  size_t buffer_index_ = 0;

  void processCommand();

public:
  Terminal(Stream &console) : console_{console} {}

  bool prompt_active = false;

  void handleRxAvailable();
  void printPrompt();
};
