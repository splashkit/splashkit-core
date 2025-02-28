module TestRunner
  # Validates that required development tools are installed for each supported language
  class InstallationValidator
    def self.validate_language(language)
      validator_class = VALIDATORS[language] or
        raise TestRunner::LanguageError, "Unsupported language: #{language}"
      validator_class.new.validate
    end
  end

  # Base validator class that provides common validation functionality for all language validators
  class BaseValidator
    INSTALLATION_INSTRUCTIONS = {
      'cargo' => 'Install Rust from https://rustup.rs',
      'rustc' => 'Install Rust from https://rustup.rs',
      'python3' => 'Download Python from https://www.python.org/downloads',
      'pytest' => 'Install pytest using: pip install pytest',
      'fpc' => 'Install Free Pascal:\n' \
      'If you get "cannot execute: required file not found" with test_main,\n' \
      'this is likely a loader issue. Try a different version of fpc:\n' \
      '1. Remove current fpc: sudo apt remove fpc\n' \
      '2. Download from https://sourceforge.net/projects/freepascal/\n' \
      '3. Or try an older/newer version from your package manager',
      'g++' => 'Install g++ using your system package manager (sudo apt install g++, brew install gcc, etc.)',
      'dotnet' => 'Install .NET SDK from https://dotnet.microsoft.com/download',
      'catch2' => 'Install Catch2 using your package manager (sudo apt install catch2, brew install catch2)',
      'dunit' => 'Install FPCUnit using:\n' \
                 '   sudo apt install fp-units-fcl fp-units-base'
    }.freeze

    def validate
      missing = required_tools.reject { |cmd| command_exists?(cmd) }
      unless missing.empty?
        instructions = missing.map do |tool|
          "\n- #{tool}: #{INSTALLATION_INSTRUCTIONS[tool] || 'No installation instructions available'}"
        end
        raise TestRunner::ConfigurationError, "Missing required tools: #{instructions.join}"
      end

      true
    end

    private

    def command_exists?(cmd)
      case platform
      when :windows
        system("where #{cmd} > NUL 2>&1")
      when :wsl, :unix
        system("which #{cmd} > /dev/null 2>&1")
      end
    end

    def platform
      @platform ||= detect_platform
    end

    def detect_platform
      return :windows if RUBY_PLATFORM =~ /mswin|mingw|cygwin/
      return :wsl if wsl?

      :unix
    end

    def wsl?
      @wsl ||= system('uname -r | grep -q "WSL"')
    end

    def required_tools
      raise NotImplementedError
    end
  end

  # Validates installation requirements for Rust development tools
  class RustValidator < BaseValidator
    private

    def required_tools
      %w[cargo rustc]
    end
  end

  # Validates installation requirements for Python development tools
  class PythonValidator < BaseValidator
    private

    def required_tools
      %w[python3 pytest]
    end
  end

  # Validates installation requirements for Pascal development tools
  class PascalValidator < BaseValidator
    def validate
      super
      check_fpcunit
    end

    private

    def required_tools
      %w[fpc]
    end

    def check_fpcunit
      fpcunit_paths = [
        # Linux paths
        '/usr/lib/fpc/*/units/*/fcl-fpcunit/fpcunit.ppu',
        '/usr/lib/fpc/3.2.2/units/x86_64-linux/fcl-fpcunit/fpcunit.ppu',
        '/usr/share/fpcsrc/*/packages/fcl-fpcunit/src/fpcunit.pp',
        '/usr/lib/fpc/*/units/*/fcl-base/fpcunit.ppu',
        '/usr/share/fpcsrc/*/fcl-fpcunit/src/fpcunit.pp',
        '/usr/share/fpcsrc/*/packages/fcl-base/src/fpcunit.pp',
        '/usr/lib/fpc/*/units/*/rtl/fpcunit.ppu',
        # macOS paths
        '/usr/local/lib/fpc/*/units/*/fcl-fpcunit/fpcunit.ppu',
        '/usr/local/share/fpcsrc/*/packages/fcl-fpcunit/src/fpcunit.pp',
        '/opt/homebrew/lib/fpc/*/units/*/fcl-fpcunit/fpcunit.ppu',
        '/opt/homebrew/share/fpcsrc/*/packages/fcl-fpcunit/src/fpcunit.pp'
      ]

      found = Dir.glob(fpcunit_paths).any?
      unless found
        raise TestRunner::ConfigurationError,
              "FPCUnit not found. Try these steps:\n\n" \
              "1. On Linux:\n" \
              "   sudo apt install fp-units-fcl fp-units-base\n\n" \
              "   If the error persists:\n" \
              "   sudo apt install fpc-source\n" \
              "   sudo apt install fp-units-rtl\n\n" \
              "2. On macOS:\n" \
              "   brew install fpc\n" \
              "   brew install fpc-units-fcl fpc-units-base"
      end
    end
  end

  # Validates installation requirements for C++ development tools
  class CppValidator < BaseValidator
    def validate
      super
      check_catch2_headers
    end

    private

    def required_tools
      %w[g++]
    end

    def check_catch2_headers
      catch2_paths = [
        '/usr/include/catch2/catch_all.hpp',
        '/usr/local/include/catch2/catch_all.hpp'
      ]

      return if catch2_paths.any? { |path| File.exist?(path) }

      raise TestRunner::ConfigurationError,
            'Catch2 headers not found. Install using: sudo apt install catch2'
    end
  end

  # Validates installation requirements for C# development tools
  class CSharpValidator < BaseValidator
    private

    def required_tools
      %w[dotnet]
    end
  end

  # Move VALIDATORS to the end of the file, after all classes are defined
  InstallationValidator::VALIDATORS = {
    rust: RustValidator,
    python: PythonValidator,
    pascal: PascalValidator,
    cpp: CppValidator,
    csharp: CSharpValidator
  }.freeze
end
