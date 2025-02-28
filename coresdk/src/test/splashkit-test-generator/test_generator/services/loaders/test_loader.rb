module TestGenerator
  # Class responsible for loading and organizing test files into groups
  class TestLoader
    # Loads and organizes all test files into groups
    # @return [Hash] Tests organized by group name
    def load_all
      MessageHandler.log_info('Loading test files...')
      all_tests = {}
      process_test_files(all_tests)
      log_results(all_tests)
      all_tests
    end

    private

    # Processes all test files in the data/tests directory
    # @param all_tests [Hash] Hash to store the processed tests
    # @return [void]
    def process_test_files(all_tests)
      files = Dir.glob('data/tests/*.json')
      MessageHandler.log_info("Found #{files.count} test files")
      files.each { |file| process_single_file(file, all_tests) }
    end

    # Processes a single test file and adds its tests to the appropriate group
    # @param file [String] Path to the test file
    # @param all_tests [Hash] Hash to store the processed tests
    # @return [void]
    def process_single_file(file, all_tests)
      content = parse_and_validate_file(file)
      group = content[:group]
      all_tests[group] ||= {
        tests: [],
        constructor: content[:constructor],
        cleanup: content[:cleanup],
        group: group
      }
      all_tests[group][:tests].concat(content[:tests])
      MessageHandler.log_status("Found #{content[:tests].count} tests for group '#{group}' from #{file}")
    rescue JSON::ParserError => e
      raise ValidationError, "Invalid JSON in test file #{file}: #{e.message}"
    rescue StandardError => e
      raise TestGeneratorError, "Error processing test file #{file}: #{e.message}"
    end

    # Parses and validates a test file
    # @param file [String] Path to the file
    # @return [Hash] Parsed and validated content
    # @raise [ValidationError] If content structure is invalid
    def parse_and_validate_file(file)
      content = JSON.parse(File.read(file), symbolize_names: true)
      unless content.is_a?(Hash) && content[:group] && content[:tests].is_a?(Array)
        raise ValidationError, "Invalid test file structure in #{file}. Required keys: 'group' and 'tests' array"
      end

      content
    end

    # Logs the groups found after processing all files
    # @param all_tests [Hash] The processed tests organized by group
    # @return [void]
    def log_results(all_tests)
      MessageHandler.log_info("Groups found: #{all_tests.keys.join(', ')}")
    end
  end
end
