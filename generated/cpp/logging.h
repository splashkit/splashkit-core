//
// SplashKit Generated Logging C++ Code
// DO NOT MODIFY
//

#ifndef __logging_h
#define __logging_h

#include <string>
#include <vector>
using std::string;
using std::vector;

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
void close_log_process();
void init_custom_logger(log_mode mode);
void init_custom_logger(string app_name, bool override_prev_log, log_mode mode);
void log(log_level level, string message);

#endif /* __logging_h */
