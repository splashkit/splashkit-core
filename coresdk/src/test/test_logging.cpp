#include "splashkit.h"
#include "logging.h"

int main ()
{
	el::Configurations app_log_conf;
	conf_and_init (
		app_log_conf,
		log_conf_category = "default",
log_filename = "app.log",
log_format = "%level (%datetime{%d/%M/%Y, %h:%m:%s}): %msg [in %fbase, ln %line]");
	return 0;
}