#include "logging.h"

using namespace std;

namespace splashkit_lib
{
    log_level _log_level;
    log_mode _log_mode; // Necessary for telling the logger where to send messages to
    ofstream custom_log_file;

    void init_custom_logger(string app_name, bool override_prev_log, log_mode mode)
    {
        switch (mode)
        {
        case LOG_CONSOLE:
            if (custom_log_file.is_open())
            {
                custom_log_file.close();
            }
            _log_mode = mode;
            break; // Easy as just using log procedure by itself, also helpful if there is no logging to be done in a portion of a program if it is modularised
        case LOG_FILE_ONLY:
            if (override_prev_log == false) // Default
            {
                custom_log_file.open(app_name + ".log", ofstream::out | ofstream::app);
            }
            else
            {
                custom_log_file.open(app_name + ".log", ofstream::out);
            }
            _log_mode = mode;
            break;
        case LOG_CONSOLE_AND_FILE:
            if (override_prev_log == false) // Default
            {
                custom_log_file.open(app_name + ".log", ofstream::out | ofstream::app);
            }
            else
            {
                custom_log_file.open(app_name + ".log", ofstream::out);
            }
            _log_mode = mode;
            break;
        }
    }

    void init_custom_logger(log_mode mode)
    {
        // Give default values for simpler overloading;
        init_custom_logger("console", true, mode);
    }

    void log(log_level level, string message)
    {
        switch (level)
        {
        case NONE:
            break;
        case INFO:
            if (level < _log_level)
            {
                return;
            }
            if (_log_mode == LOG_CONSOLE || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                write("INFO: ");
            }
            if (_log_mode == LOG_FILE_ONLY || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                custom_log_file << "INFO: ";
            }
            break;
        case DEBUG:
            if (level < _log_level)
            {
                return;
            }
            if (_log_mode == LOG_CONSOLE || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                write("DEBUG: ");
            }
            if (_log_mode == LOG_FILE_ONLY || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                custom_log_file << "DEBUG: ";
            }
            break;
        case WARNING:
            if (level < _log_level)
            {
                return;
            }
            if (_log_mode == LOG_CONSOLE || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                write("WARNING: ");
            }
            if (_log_mode == LOG_FILE_ONLY || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                custom_log_file << "WARNING: ";
            }
            break;
        case ERROR:
            if (level < _log_level)
            {
                return;
            }
            if (_log_mode == LOG_CONSOLE || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                write("ERROR: ");
            }
            if (_log_mode == LOG_FILE_ONLY || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                custom_log_file << "ERROR: ";
            }
            break;
        case FATAL:
            if (_log_mode == LOG_CONSOLE || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                write("FATAL: ");
            }
            if (_log_mode == LOG_FILE_ONLY || _log_mode == LOG_CONSOLE_AND_FILE)
            {
                custom_log_file << "FATAL: ";
            }
            break;
        }

        auto time = std::chrono::system_clock::now();
        std::time_t c_time = std::chrono::system_clock::to_time_t(time);
        string str_time = std::ctime(&c_time);
        // Required to remove the new line character ctime decides to add, then we add the log message
        if (_log_mode == LOG_CONSOLE || _log_mode == LOG_CONSOLE_AND_FILE)
        {
            write(str_time.substr(0, str_time.length() - 1));
            write(" ");
            write_line(message);
        }
        if (_log_mode == LOG_FILE_ONLY || _log_mode == LOG_CONSOLE_AND_FILE)
        {
            custom_log_file << str_time.substr(0, str_time.length() - 1);
            custom_log_file << " ";
            custom_log_file << message + "\n";
        }
    }

    void close_log_process()
    {
        if (custom_log_file.is_open())
        {
            custom_log_file.close();
        }
    }
} // namespace splashkit_lib