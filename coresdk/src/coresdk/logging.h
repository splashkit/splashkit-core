#ifndef LOGGING
#define LOGGING
#include "splashkit.h"

/**Function to configure and initialise the logger for a solution utilising Splashkit, according to the developers subjectively-defined specs.
@param cmd_ln_args: Specifies whether Easylogging++ needs to look for any potentially passed command-line arguments, if they are given to the application.  This feature is off (param set to false) by default.
@type cmd_ln_args: bool
*/
void conf_and_init (el::Configurations &log_conf, string log_conf_category, bool cmd_ln_args = false);

#endif