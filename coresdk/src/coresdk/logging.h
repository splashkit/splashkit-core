/**
 * @header logging
 * @author Nathaniel Schmidt
 * @brief SplashKit Logging facilitates streamlined logging with customizable severity levels and modes.
 * 
 * SplashKit Logging module,  allows users to initialize a custom logger with specified log levels and modes (console, file, or both). 
 * The module provides functions to log messages at different severity levels (INFO, DEBUG, WARNING, ERROR, FATAL) with timestamped entries. 
 * Users can close the logging process as needed, and the module handles customization for console and file output.
 * 
 * @attribute group  logging
 * @attribute static logging
 */

#ifndef logging_h
#define logging_h

#include "terminal.h"
#include <chrono>
#include <ctime>
#include <fstream>

namespace splashkit_lib
{

    /**
     * Defines the available levels for log messages. This allows categorisation of log
     * messages which can then be filtered allowing messages below a given level to be
     * ignored.
     * 
     * @constant NONE    Output to the message log but without a specified level
     * @constant INFO    Output information to the message log
     * @constant DEBUG   Output a debug message to the message log
     * @constant WARNING Output a warning message to the message log
     * @constant ERROR   Output an error message to the message log
     * @constant FATAL   Output an error message to the message log
     */
    enum log_level {
        NONE,
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        FATAL
    };
    
    /**
     * Defines the available modes of logging, indicating where messages are written to.
     * 
     * @constant LOG_NONE Set the logging mode to none for nothing to be logged to the console or a file.
     * @constant LOG_CONSOLE Ensure that output only directs to the on-screen, text-based console..
     * @constant LOG_FILE_ONLY Ensure that output only directs to a text file..
     * @constant LOG_CONSOLE_AND_FILE Direct ouput to both the console and a file.
    */
    enum log_mode
    {
        LOG_NONE,
        LOG_CONSOLE,
        LOG_FILE_ONLY,
        LOG_CONSOLE_AND_FILE
    };
    
    /**
     * Initialises the logging mode between either writing to a file or both a file and the text-based console.
     * 
     * @param app_name The name of the application being written requiring logging
     * @param override_prev_log Determines whether or not a new logging session should override the existing file, if any. Set this to false if you want new log messages to be appended to the bottom of the file; otherwise set it to true if you would like a new file to be created on top of the old one.  
     * @param mode The mode of log output i.e. whether there should be output to the console, a text file, or both.  Pass your choice of mode variable in by reference.
     * 
     * @attribute suffix  _name_override_mode
     */
    void init_custom_logger (string app_name, bool override_prev_log, log_mode mode);

    /**
     * Initialises the logging mode for logged messages to be written to the text-based console.
     * @param mode The mode of log output i.e. whether there should be output to the console, a text file, or both.  Pass your choice of mode variable in by reference.
     */
    void init_custom_logger (log_mode mode);

    /**
     * Send a message to the message log. The message will be written if the log level for
     * the program is set to display this.
     * 
     * @param level         The level of the message to log
     * @param message     The message to be shown
     */
    void log(log_level level, string message);
    
    /**
     * Ensures propper memory clean-up prior to exit, if needed.  Used in sk_init_looging ().
     */
    void close_log_process ();
}
#endif
