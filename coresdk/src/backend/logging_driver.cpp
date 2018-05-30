//
//  logging_driver.h
//  sgsdl2
//
//  Created by James Armstrong on 03/09/2016.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#include "logging_driver.h"

#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

using namespace el;
namespace splashkit_lib
{
    void sk_init_logging()
    {
        el::Configurations conf;
        conf.setToDefault();
        conf.setGlobally(
                         ConfigurationType::Format,
                         "(%datetime{%d/%m/%Y}) %level -> %msg [%file:%line]");
        conf.setGlobally(ConfigurationType::Filename, "logs/splashkit.log");

        Loggers::reconfigureLogger("default", conf);
        
        Loggers::addFlag(LoggingFlag::ColoredTerminalOutput);
        Loggers::addFlag(LoggingFlag::DisableApplicationAbortOnFatalLog);
    }
}
