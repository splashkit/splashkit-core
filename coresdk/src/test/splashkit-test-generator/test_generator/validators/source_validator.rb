module TestGenerator
  # Validates the existence and state of required source files and tools
  # Ensures translator and bindings are properly set up before test generation
  class SourceValidator
    # Main validation method that checks for bindings and translator
    # Provides guidance on setup and running the translator when needed
    # @return [void]
    def self.validate
      if bindings_exist?
        MessageHandler.log_warning(
          "Important:\n" \
          "1. Run translator after any source code changes\n" \
          "2. Re-run test generator to apply updates"
        )
        return
      end

      if translator_exists?
        MessageHandler.log_error(
          "Generated bindings are missing.\n" \
          "Please run the translator to generate language bindings.\n" \
          "See Docker_README.md for instructions on running the translator."
        )
      else
        MessageHandler.log_error(
          "Setup required:\n" \
          "1. Clone the translator repository (git submodule init && git submodule update)\n" \
          "2. See Docker_README.md for instructions on running the translator\n" \
          "3. Keep running translator after source code changes\n" \
          "4. Re-run the test generator to apply changes"
        )
      end
      exit 1
    end

    private

    # Checks if all required language bindings exist in the generated directory
    # @return [Boolean] true if all required language bindings exist
    def self.bindings_exist?
      DirectoryManager::REQUIRED_LANGUAGES.all? do |lang|
        Dir.exist?(File.join(DirectoryManager::GENERATED_DIR, lang))
      end
    end

    # Verifies that the translator directory exists and contains files
    # @return [Boolean] true if translator is properly installed
    def self.translator_exists?
      translator_dir = DirectoryManager::TRANSLATOR_DIR
      puts "Translator dir: #{translator_dir}"
      Dir.exist?(translator_dir) && !Dir.empty?(translator_dir)
    end
  end
end