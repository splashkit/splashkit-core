require_relative 'lib'

# Module for executing tests across different programming languages
module TestRunner
  # Executes all tests for a specified programming language
  # @param language [String] The programming language to run tests for
  # @raise [TestRunnerError] If there's an error during test execution
  # @raise [StandardError] If there's an unexpected error
  def self.run_all_tests(language)
    TestConfig.setup unless TestConfig.runners
    InstallationValidator.validate_language(language)
    runner = TestConfig.runners[language]
    MessageHandler.log_test("Starting all tests for #{language}")
    runner.run_tests(find_test_groups(language))
  rescue TestRunner::TestRunnerError => e
    MessageHandler.log_error("Test runner error: #{e.message}")
    raise
  rescue StandardError => e
    MessageHandler.log_error("Unexpected error running tests for #{language}: #{e.message}")
    raise
  end

  # Executes a specific test within a test group
  # @param language [String] The programming language to run the test in
  # @param group [String] The test group containing the test
  # @param test_name [String] The specific test to run
  # @raise [TestRunnerError] If there's an error during test execution
  # @raise [StandardError] If there's an unexpected error
  def self.run_specific_test(language, group, test_name)
    TestConfig.setup unless TestConfig.runners
    InstallationValidator.validate_language(language)
    runner = TestConfig.runners[language]
    MessageHandler.log_test("Starting test #{test_name} in #{group} for #{language}")
    runner.run_single_test(group, test_name)
  rescue TestRunner::TestRunnerError => e
    MessageHandler.log_error("Test runner error: #{e.message}")
    raise
  rescue StandardError => e
    MessageHandler.log_error("Unexpected error running specific test #{test_name} for #{language}: #{e.message}")
    raise
  end

  # Executes all tests in a specific file
  # @param language [String] The programming language to run the test in
  # @param file_name [String] The name of the test file to run
  # @raise [TestRunnerError] If there's an error during test execution
  # @raise [StandardError] If there's an unexpected error
  def self.run_single_file(language, file_name)
    TestConfig.setup unless TestConfig.runners
    InstallationValidator.validate_language(language)
    runner = TestConfig.runners[language]
    MessageHandler.log_test("Starting tests for #{file_name} in #{language}")
    runner.run_tests([file_name])
  rescue TestRunner::TestRunnerError => e
    MessageHandler.log_error("Test runner error: #{e.message}")
    raise
  rescue StandardError => e
    MessageHandler.log_error("Unexpected error running file #{file_name} for #{language}: #{e.message}")
    raise
  end

  # Finds all test groups for a given language
  # @param language [String] The programming language to find test groups for
  # @return [Array<String>] List of test group names
  def self.find_test_groups(language)
    test_files = Dir.glob("data/tests/*.*")
    test_files.map { |f| File.basename(f, '.*') }
  end
end
