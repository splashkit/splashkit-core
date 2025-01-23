#!/usr/bin/env ruby
require_relative 'shared/lib'

options = CliParser.parse

begin
  if options[:generate]
    api_json = File.read(options[:generate])
    require_relative 'test_generator/test_generator'
    TestGenerator.generate(api_json)
  elsif options[:run_tests] || options[:language] || options[:group] || options[:test]
    require_relative 'test_runner/test_runner'
    if options[:run_tests]
      # Add your TestRunner calls here for default behavior
      # Examples:
      # TestRunner.run_all_tests(:pascal)
      # TestRunner.run_single_file(:pascal, 'animations')
      # TestRunner.run_specific_test(:pascal, 'animations', 'animation_count')
    elsif options[:test]
      TestRunner.run_specific_test(options[:language], options[:group], options[:test])
    elsif options[:group]
      TestRunner.run_single_file(options[:language], options[:group])
    else
      TestRunner.run_all_tests(options[:language])
    end
  else
    puts "\nError: No valid operation specified"
    puts "Please use one of the following options:"
    puts "  --generate PATH     : Generate tests from API JSON file"
    puts "  --run-tests        : Run tests with default configuration"
    puts "  --language LANGUAGE : Run tests for specific language"
    puts "\nUse --help for complete usage information"
    exit 1
  end
rescue Errno::ENOENT
  puts MessageHandler.log_warning("Could not find file '#{options[:generate]}'")
  exit 1
rescue JSON::ParserError
  puts MessageHandler.log_warning('Invalid JSON file')
  exit 1
rescue StandardError => e
  puts MessageHandler.log_warning("Error: #{e.message}")
  exit 1
end
