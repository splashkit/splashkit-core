require_relative 'lib'

# Module responsible for generating test cases for SplashKit functions
module TestGenerator
  # Main entry point for test generation
  # @param api_json [String] JSON string containing the API specification
  def self.generate(api_json)
    SourceValidator.validate
    CMakeBuilder.build_if_needed
    BindingFetcher.process_files
    
    api = JSON.parse(api_json)
    functions = Parser.parse_functions(api)
    group_tests = TestLoader.new.load_all

    # Generate tests for each supported programming language
    LanguageConfig::SUPPORTED_LANGUAGES.each do |language|
      generate_for_language(functions, language, group_tests)
      MessageHandler.log_success("Completed generating tests for #{language}")
    end
  end

  # Generates test files for a specific programming language
  # @param functions [Array<Function>] List of functions to generate tests for
  # @param language [String] Target programming language
  # @param group_tests [Hash] Pre-loaded test cases grouped by category
  def self.generate_for_language(functions, language, group_tests)
    config = LanguageConfig.for_language(language)
    base_dir, tests_dir = DirectoryManager.setup(config.language)
    write_group_files(functions, tests_dir, config, group_tests)
  rescue StandardError => e
    MessageHandler.log_error('Test generation failed', e.message)
    raise
  end

  # Writes individual test group files
  # @param functions [Array<Function>] List of all functions
  # @param tests_dir [String] Directory to write test files
  # @param config [LanguageConfig] Language configuration
  # @param group_tests [Hash] Pre-loaded test cases
  def self.write_group_files(functions, tests_dir, config, group_tests)
    functions
      .group_by { |func| func.group || 'ungrouped' } # Group functions by their category
      .each do |group, group_funcs|
        TestWriter.new(group, group_funcs, functions, config, group_tests).write_to(tests_dir)
      end
  end
end