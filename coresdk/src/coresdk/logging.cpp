/**logging.cpp: brings Splashkit backend support for Easylogging++ to the core SDK, making it explicitly callable outside of the  SDK's source code, for operational for use by third-party apps.
Author: Nathaniel Schmidt <schmidty2244@gmail.com>
Modified on 04/09/2020*/

#include "splashkit.h"
#include "easylogging++.h"

/**Function to configure and initialise the logger for a solution utilising Splashkit, according to the developers subjectively-defined specs.
@param cmd_ln_args: Specifies whether Easylogging++ needs to look for any potentially passed command-line arguments, if they are given to the application.  This feature is off (param set to false) by default.
@type cmd_ln_args: bool
*/
void conf_and_init (el::Configurations &log_conf, string log_conf_category, string log_filename, string log_format, bool use_as_default = false, bool override_prev_logs = false, bool cmd_ln_args = false)
{
	defaultConf.setToDefault ();// Just in case someone forgets to set something important.
	        conf.setGlobally(ConfigurationType::Format, log_format);
        conf.setGlobally(ConfigurationType::Filename, log_filename);
	el::Loggers::reconfigureLogger (log_conf_category, log_conf);

	if (use_as_default)
	{
		if (override_prev_logs)
		{
			el::Loggers::setDefaultConfigurations (log_conf, configureExistingLoggers = true);
		}
		else
		{
			el::Loggers::setDefaultConfigurations (log_conf);
		}
	}

	el::Loggers::addFlag(LoggingFlag::DisableApplicationAbortOnFatalLog);
	
	if (cmd_ln_args)
	{
		START_EASYLOGGINGPP (argc, argv);/// If the developer wants command-line arguments to be passed to their application, otherwise do nothing.  also definitely do this last so that func params hopefully don't override command-line args.
	}
}