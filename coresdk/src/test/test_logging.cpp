#include "logging.h"

using namespace splashkit_lib;

void run_logging_test()
{
    write_line("If this test works, ten lines should be written to both the console and a test log file, not inclusive of this current line.");
    log_level _log_level = DEBUG;
    log_mode _log_mode;
    _log_mode = LOG_CONSOLE_AND_FILE;

    init_custom_logger("test_logging", true, _log_mode);
    log(NONE, "Testing with no[ne] logging level"); // This message should not ultimately be logged.
    log(INFO, "Testing info");                      // This message should not ultimately be logged.
    log(DEBUG, "Testing debug");
    log(WARNING, "Testing warning");
    log(ERROR, "Testing error");

    _log_mode = LOG_CONSOLE;
    init_custom_logger(_log_mode);
    log(NONE, "Testing with no[ne] logging level"); // This message should not ultimately be logged.
    log(INFO, "Testing info");                      // This message should not ultimately be logged.
    log(DEBUG, "Testing debug");
    log(WARNING, "Testing warning");
    log(ERROR, "Testing error");

    _log_mode = LOG_FILE_ONLY;
    init_custom_logger("test_logging", true, _log_mode);
    log(NONE, "Testing with no[ne] logging level"); // This message should not ultimately be logged.
    log(INFO, "Testing info");                      // This message should not ultimately be logged.
    log(DEBUG, "Testing debug");
    log(WARNING, "Testing warning");
    log(ERROR, "Testing error");
}