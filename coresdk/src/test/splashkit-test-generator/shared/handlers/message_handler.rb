def colorize(text, color_code)
  "\e[#{color_code}m#{text}\e[0m"
end

# Module for handling error and warning messages
module MessageHandler
  COLORS = {
    error: '31',    # red
    warning: '33',  # yellow
    info: '36',     # cyan
    success: '32',  # green
    test: '35',     # magenta
    status: '34'    # blue
  }.freeze

  class << self
    def log_error(message, details = nil)
      puts colorize("Error: #{message}", COLORS[:error])
      puts colorize("Details: #{details}", COLORS[:error]) if details
    end

    def log_warning(message)
      puts colorize("Warning: #{message}", COLORS[:warning])
    end

    def log_info(message)
      puts colorize("Info: #{message}", COLORS[:info])
    end

    def log_success(message)
      puts colorize("Success: #{message}", COLORS[:success])
    end

    def log_test(message)
      puts colorize(message, COLORS[:test])
    end

    def log_status(message)
      puts colorize("Status: #{message}", COLORS[:status])
    end

    def colorize(text, color_code)
      "\e[#{color_code}m#{text}\e[0m"
    end
  end
end
