#ifndef logging_h
#define logging_h

#include "terminal.h"
#include <chrono>
#include <ctime>

namespace splashkit_lib
{

  /**
   *  
   * @constant INFO     Output information to the message log
   * @constant DEBUG    Output a debug message to the message log
   * @constant WARNING  Output a warning message to the message log
   * @constant ERROR    Output an error message to the message log
   */
  enum log_level {
    INFO,
    DEBUG,
    WARNING,
    ERROR
  };

  /**
   * Send a message to the message log. The message will be written if the log level for
   * the program is set to display this.
   * 
   * @param level     The level of the message to log
   * @param message   The message to be shown
   */
  void log(log_level level, string message);

}
#endif
