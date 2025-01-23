# Base class for language-specific test runners
class BaseTestRunner
  def initialize(config)
    @config = config
    # Extract language name from class name (e.g., 'PascalTestRunner' -> 'pascal')
    @language = self.class.name.downcase.sub('testrunner', '')
  end

  # Executes test groups, handling both sequential and parallel test execution
  # @param groups [Array<String>] List of test groups to run
  def run_tests(groups)
    sequential_tests = []
    parallel_tests = []

    groups.each do |group|
      next if @config.should_skip?(group)
      next unless CapabilityValidator.validate_group(group)

      if @config.is_sequential?(group)
        sequential_tests << group
      else
        parallel_tests << group
      end
    end

    # Run sequential tests first, then parallel tests
    run_sequential_tests(sequential_tests) unless sequential_tests.empty?
    run_parallel_tests(parallel_tests) unless parallel_tests.empty?
  end

  # Runs a specific test within a group
  # @param group [String] The test group name
  # @param test_name [String] The specific test to run
  # @raise [RuntimeError] If the specified test cannot be found
  def run_single_test(group, test_name)
    test_method = get_test_method_name(test_name)
    test_files = Dir.glob("generated_tests/#{@language}/tests/#{group}_tests.*")
    test_file = test_files.find { |f| File.read(f).include?(test_method) }
    raise "No test found for function #{test_name}" unless test_file

    MessageHandler.log_test("Running specific test: #{group}.#{test_method}")
    run_specific_test(group, test_method)
  end

  protected

  # Executes tests that must run sequentially
  # @param groups [Array<String>] List of sequential test groups
  def run_sequential_tests(groups)
    groups.each do |group|
      next if @config.is_manual?(group) && !Prompt.confirm_manual_test(group)

      MessageHandler.log_test("Running sequential test: #{group}")
      run_sequential_group(group)
    end
  end

  # Executes tests that can run in parallel
  # @param groups [Array<String>] List of parallel test groups
  def run_parallel_tests(groups)
    groups.each do |group|
      next if @config.is_manual?(group) && !Prompt.confirm_manual_test(group)

      MessageHandler.log_test("Running parallel test: #{group}")
      run_parallel_group(group)
    end
  end

  # Template method to be implemented by subclasses for sequential test execution
  # @param group [String] The test group to run
  # @raise [NotImplementedError] Must be implemented by subclasses
  def run_sequential_group(group)
    raise NotImplementedError
  end

  # Template method to be implemented by subclasses for parallel test execution
  # @param group [String] The test group to run
  # @raise [NotImplementedError] Must be implemented by subclasses
  def run_parallel_group(group)
    raise NotImplementedError
  end

  # Template method to be implemented by subclasses for specific test execution
  # @param group [String] The test group containing the test
  # @param test_method [String] The specific test method to run
  # @raise [NotImplementedError] Must be implemented by subclasses
  def run_specific_test(group, test_method)
    raise NotImplementedError
  end

  # Template method to be implemented by subclasses for test method name formatting
  # @param test_name [String] The raw test name
  # @return [String] The formatted test method name
  # @raise [NotImplementedError] Must be implemented by subclasses
  def get_test_method_name(test_name)
    raise NotImplementedError
  end

  private

  def run_in_dir(lang, command)
    system("export #{lib_path} && cd generated_tests/#{lang} && #{command}")
  end

  def lib_path
    lib_path = LibProcessor.test_library_dir
    case RbConfig::CONFIG['host_os']
    when /mswin|mingw|windows/i
      "PATH=#{lib_path};#{ENV['PATH']}"
    when /darwin|mac os/i
      "DYLD_LIBRARY_PATH=#{lib_path}"
    else # Linux
      "LD_LIBRARY_PATH=#{lib_path}:#{ENV['LD_LIBRARY_PATH']}"
    end
  end
end
