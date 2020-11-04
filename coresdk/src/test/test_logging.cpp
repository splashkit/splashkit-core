#include "logging.h"

using namespace splashkit_lib;

void run_logging_test ()
{
    log_level _log_level = INFO;
log_mode _log_mode = CONSOLE_AND_FILE;
    
    set_logger_status ("../../../logs/test_logging", _log_mode);
    log (INFO, "Testing info");
    log (DEBUG, "Testing debug");
    log (WARNING, "Testing warning");
    log (ERROR, "Testing error");
}