#include "logging.h"
#include "terminal.h"

LogLevel _log_level = DEBUG;

void log(LogLevel level, string message) {
  switch (level) {
  case INFO:
    if (_log_level == DEBUG)
    {
      return;
      break;
    }
  case DEBUG:
    if (_log_level == WARNING) {
      return;
    }
    write("DEBUG: ");
    break;
  case WARNING:
    if (_log_level == ERROR) {
      return;
    }
    write("WARNING: ");
    break;
  case ERROR:
    write("ERROR: ");
    break;
  }

  auto time = std::chrono::system_clock::now();
  std::time_t c_time = std::chrono::system_clock::to_time_t(time);
  string str_time = std::ctime(&c_time);
  // Required to remove the new line character ctime decides to add
  write(str_time.substr(0, str_time.length() - 1));
  write(" ");
  write(message);
}