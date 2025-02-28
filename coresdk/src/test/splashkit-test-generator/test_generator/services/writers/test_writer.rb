module TestGenerator
  # Class responsible for writing test files for each function group
  class TestWriter
    def initialize(group, group_functions, all_functions, config, group_files)
      @group = group
      @group_functions = group_functions # Functions for this group only
      @functions = all_functions # All available functions
      @config = config
      @group_files = group_files
      @formatter = CodeFormatter.new(config.indent_size)
    end

    # Writes the test file for a function group
    # @param tests_dir [String] Directory where test files will be written
    # @return [void]
    def write_to(tests_dir)
      FileUtils.mkdir_p(File.dirname(test_file_path(tests_dir)))
      File.open(test_file_path(tests_dir), 'w') do |file|
        write_content(file)
      end
    rescue SystemCallError => e
      raise TestGeneratorError, "Failed to write test file: #{e.message}"
    end

    private

    # Generates the file path for the test file
    # @param tests_dir [String] Base directory for test files
    # @return [String] Complete file path
    def test_file_path(tests_dir)
      "#{tests_dir}/#{@group.downcase.gsub(/\s+/, '_')}_tests.#{@config.file_extension}"
    end

    # Writes the complete test file content
    # @param file [File] File handle to write to
    # @return [void]
    def write_content(file)
      write_imports(file)
      if @config.class_wrapper
        write_wrapped_tests(file)
      else
        write_unwrapped_tests(file)
      end
    end

    # Writes import statements at the start of the file
    # @param file [File] File handle to write to
    # @return [void]
    def write_imports(file)
      @config.imports.each do |import|
        line = import.respond_to?(:call) ? import.call(@group) : import
        file.puts(line)
      end
    end

    # Writes tests wrapped in a class structure
    # @param file [File] File handle to write to
    # @return [void]
    def write_wrapped_tests(file)
      write_class_header(file)
      write_constructor(file)
      write_class_footer(file) if @config.language == :cpp
      write_test_methods(file)
      write_tear_down(file)
      write_class_footer(file) if @config.language != :cpp
    end

    # Writes tests without class wrapping
    # @param file [File] File handle to write to
    # @return [void]
    def write_unwrapped_tests(file)
      @group_functions.each do |function|
        write_test_method(file, function)
      end
    end

    # Writes the class header with proper indentation
    # @param file [File] File handle to write to
    # @return [void]
    def write_class_header(file)
      tests = @group_functions.map { |function| find_test_case(function) }
      @config.class_wrapper_handler.header_lines(@group, group_file, tests).each do |line|
        file.puts(@formatter.indent(line, @config))
      end
    end

    # Writes the class footer
    # @param file [File] File handle to write to
    # @return [void]
    def write_class_footer(file)
      @config.class_wrapper_handler.footer_lines(@group).each do |line|
        file.puts(@formatter.format_line(line, @config))
      end
    end

    # Writes the constructor if required
    # @param file [File] File handle to write to
    # @return [void]
    def write_constructor(file)
      @config.constructor_handler.lines(@group, group_file, @functions, @formatter).each do |line|
        file.puts(@formatter.format_line(line, @config))
      end
    end

    # Writes individual test methods for each function
    # @param file [File] File handle to write to
    # @return [void]
    def write_test_methods(file)
      @group_functions.each do |function|
        test_case = find_test_case(function)
        test = TestCase.new(test_case[:name], @group, test_case[:steps], @config, @functions)
        file.puts(test.to_code(@formatter))
      end
    end

    # Finds the test case for a given function
    # @param function [Function] The function to find tests for
    # @return [Hash] The test case for the function
    # @raise [StandardError] If no test case is found
    def find_test_case(function)
      test_case = FunctionLookup.get_test_by_function_name(function, @group_files)
      validate_test_case_exists!(function, test_case)
      test_case
    end

    # Writes the tear down section
    # @param file [File] File handle to write to
    # @return [void]
    def write_tear_down(file)
      @config.tear_down_handler.lines(@group, group_file).each do |line|
        file.puts(@formatter.format_line(line, @config))
      end
    end

    # Gets constructor steps from group tests
    # @return [Array, nil] Array of constructor steps or nil if none exist
    def group_file
      return nil unless @group_files[@group].is_a?(Hash)

      @group_files[@group]
    end

    # Validates that a test case exists for a given function
    # @param function [Function] The function to validate
    # @param test_case [Hash, nil] The test case or nil if not found
    # @raise [ValidationError] If no test case is found
    def validate_test_case_exists!(function, test_case)
      return if test_case

      raise ValidationError, <<~ERROR
        No test case found for:
        - Function: #{function.name}
        - Group: #{function.group}
        - Available groups: #{@group_files.to_h.keys.join(', ')}
      ERROR
    end
  end
end
