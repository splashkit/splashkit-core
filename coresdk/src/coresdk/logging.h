#ifndef FIRESTORM_LOGGING
#define FIRESTORM_LOGGING

#include "terminal.h"
#include <chrono>
#include <ctime>

enum LogLevel {
  INFO,
  DEBUG,
  WARNING,
  ERROR
};

extern LogLevel _log_level;

void log(LogLevel level, string message);

#endif
