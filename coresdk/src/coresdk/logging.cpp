#include "logging.h"

namespace splashkit_lib
{

  log_level _log_level = DEBUG;
  ofstream log_file ;
  log_mode _log_mode = CONSOLE;
  
  void set_logger_status (string app_name = "sk_log", log_mode &mode, bool override_prev_log = false)
  {
    switch (mode)
    {
      case CONSOLE:
        if (log_file.is_open ())
        {
          log_file.close ();
        }
        return;// Easy as just using log procedure by itself, also helpful if there is no logging to be done in a portion of a program if it is modularised
        break;
      case FILE:
        if (override_prev_log == false)// Default
        {
          log_file.open (app_name + ".log", fstream::app);
        }
        else
        {
          log_file.open (app_name + ".log", fstream::out);
        }
        atexit (log_file.close);
        break;
        case CONSOLE_AND_FILE:
        if (override_prev_log == false)// Default
        {
          log_file.open (app_name + ".log", fstream::app);
        }
        else
        {
          log_file.open (app_name + ".log", fstream::out);
        }
          atexit (log_file.close);
          break;
    }
  }

  void log (log_level level, string message)
  {
    switch (level)
    {
    case INFO:
      if (_log_level == DEBUG)
      {
        return;
      }
      if (log_mode == CONSOLE || log_mode == CONSOLE_AND_FILE)
      {
        write("INFO: ");
      }
      else if (log_mode == FILE || log_mode == CONSOLE_AND_FILE)
      {
        log_file << "INFO: "
      }
      break;
    case DEBUG:
      if (_log_level == WARNING)
      {
        return;
      }
      if (log_mode == CONSOLE || log_mode == CONSOLE_AND_FILE)
      {
        write("DEBUG: ");
      }
      else if (log_mode == FILE || log_mode == CONSOLE_AND_FILE)
      {
        log_file << "DEBUG: "
      }
      break;
    case WARNING:
      if (_log_level == ERROR)
      {
        return;
      }
      if (log_mode == CONSOLE || log_mode == CONSOLE_AND_FILE)
      {
        write("WARNING: ");
      }
      else if (log_mode == FILE || log_mode == CONSOLE_AND_FILE)
      {
        log_file << "WARNING: "
      }
      break;
    case ERROR:
      if (log_mode == CONSOLE || log_mode == CONSOLE_AND_FILE)
      {
        write("ERROR: ");
      }
      else if (log_mode == FILE || log_mode == CONSOLE_AND_FILE)
      {
        log_file << "ERROR: "
      }
      break;
    }

    auto time = std::chrono::system_clock::now();
    std::time_t c_time = std::chrono::system_clock::to_time_t(time);
    string str_time = std::ctime(&c_time);
    // Required to remove the new line character ctime decides to add, then we add the log message
    if (log_mode == CONSOLE || log_mode == CONSOLE_AND_FILE)
    {
      write(str_time.substr(0, str_time.length() - 1));
      write(" ");
      write(message);
    }
    else if (log_mode == FILE || log_mode == CONSOLE_AND_FILE)
    {
      log_file << str_time.substr(0, str_time.length() - 1);
      log_file << " ";
      log_file << message;
    }
  }
} // namespace splashkit_lib