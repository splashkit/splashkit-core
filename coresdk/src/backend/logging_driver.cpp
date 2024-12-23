//
//  logging_driver.h
//  sgsdl2
//
//  Created by James Armstrong on 03/09/2016.
//  Modified by Nathaniel Schmidt <schmidty2244@gmail.com> on 21/11/2020.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#include "logging_driver.h"
#include "logging.h"

#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

using namespace el;
namespace splashkit_lib
{
    void sk_init_logging()
    {
        // for Backend logging
        el::Configurations conf;
        conf.setToDefault();
        conf.setGlobally(
                         ConfigurationType::Format,
                         "(%datetime{%d/%M/%Y}) %level -> %msg [raised in %fbase:%line]");
        conf.setGlobally(ConfigurationType::Filename, "logs/splashkit.log");

        Loggers::reconfigureLogger("default", conf);
        
        Loggers::addFlag(LoggingFlag::ColoredTerminalOutput);
        Loggers::addFlag(LoggingFlag::DisableApplicationAbortOnFatalLog);
        Loggers::addFlag(LoggingFlag::LogDetailedCrashReason);
        Loggers::addFlag(LoggingFlag::ImmediateFlush);
        
        // For use in core SDK
        atexit (close_log_process);
            }
}
