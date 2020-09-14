#include "logging.h"

using namespace splashkit_lib;

void run_logging_test ()
{
    // Test log output to console
    log (INFO, "Test info Message");
    log (DEBUG, "Test debug Message");
    log (WARNING, "Test warning Message");
    log (ERROR, "Test error Message");
    
    // Test output to plain text file:
    
}