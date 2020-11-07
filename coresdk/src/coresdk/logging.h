#ifndef logging_h
#define logging_h

#include "terminal.h"
#include <chrono>
#include <ctime>
#include <fstream>

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
  
  enum log_mode
  {
    CONSOLE,
    FILE,
    CONSOLE_AND_FILE
  };
  
  /**
   * Changes the logging mode between either writing to the console, or a file, or both.
   * 
   * @param app_name The name of the application being written requiring logging
   * override_prev_log Determines whether or not a new logging session should override the existing file, if any.  Set this to false if you want new log messages to be appended to the bottom of the file; otherwise set it to true if you would like a new file to be created on top of the old one.  This parameter is assigned false by default.
   */
    void set_logger_status (string app_name = "sk_log", bool override_prev_log = false, log_mode &mode);
  
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
