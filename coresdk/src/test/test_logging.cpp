#include "logging.h"

using namespace splashkit_lib;

void run_logging_test ()
{
    log_level _log_level = DEBUG;
    log_mode _log_mode = CONSOLE_AND_FILE;
    
   init_custom_logger ("test_logging", _log_mode);
    log (NONE, "Testing with no[ne] logging level");// This message should not ultimately be logged.
    log (INFO, "Testing info");// This message should not ultimately be logged.
    log (DEBUG, "Testing debug");
    log (WARNING, "Testing warning");
    log (ERROR, "Testing error");
}