//
// SplashKit Generated Logging C++ Code
// DO NOT MODIFY
//

#ifndef __logging_h
#define __logging_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

typedef enum {
    NONE,
    INFO,
    DEBUG,
    WARNING,
    ERROR,
    FATAL
} log_level;
typedef enum {
    LOG_NONE,
    LOG_CONSOLE,
    LOG_FILE_ONLY,
    LOG_CONSOLE_AND_FILE
} log_mode;
/**
* Ensures propper memory clean-up prior to exit, if needed.  Used in sk_init_looging ().

*
*/
void close_log_process();
/**
* Initialises the logging mode for logged messages to be written to the text-based console.
* @param mode The mode of log output i.e. whether there should be output to the console, a text file, or both.  Pass your choice of mode variable in by reference.
*
*/
void init_custom_logger(log_mode mode);
/**
* Initialises the logging mode between either writing to a file or both a file and the text-based console.
* @param app_name The name of the application being written requiring logging
* @param override_prev_log Determines whether or not a new logging session should override the existing file, if any. Set this to false if you want new log messages to be appended to the bottom of the file; otherwise set it to true if you would like a new file to be created on top of the old one.
* @param mode The mode of log output i.e. whether there should be output to the console, a text file, or both.  Pass your choice of mode variable in by reference.
*
*/
void init_custom_logger(string app_name, bool override_prev_log, log_mode mode);
/**
* Send a message to the message log. The message will be written if the log level for
* the program is set to display this.
* @param level The level of the message to log
* @param message The message to be shown
*
*/
void log(log_level level, string message);

#endif /* __logging_h */
