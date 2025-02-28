module TestGenerator
  # Class responsible for generating individual test case code with proper formatting
  class TestCase
    attr_reader :name, :steps

    def initialize(name, group, steps, config, functions)
      @name = name
      @group = group
      @steps = steps
      @config = config
      @functions = functions
    end

    # Generates formatted code for the test case
    # @param formatter [CodeFormatter] The formatter to use for code indentation
    # @return [String] The complete formatted test case code
    def to_code(formatter)
      code = write_header(formatter)
      code << write_var_section(formatter) if @config.language == :pascal
      code << write_steps(formatter)
      code << formatter.indent(@config.control_flow[:end].call, @config)
      code
    end

    private

    # Writes the test case header with the test name
    # @return [String] The formatted test header
    def write_header(formatter)
      @config.format_test_function(@group, @name).map do |line|
        formatter.indent(line, @config)
      end.join
    end

    # Writes all test steps in sequence
    # @param formatter [CodeFormatter] The formatter to use for code indentation
    # @return [String] The formatted test steps code
    def write_steps(formatter)
      @steps.map.with_index do |step, index|
        StepWriter.write_test_step(step, @functions, @config, formatter)
      rescue StandardError => e
        raise TestGeneratorError, "Error writing step #{index + 1} in test '#{@name}': #{e.message}"
      end.join
    end

    # Generates the variable declaration section for Pascal tests
    # @param formatter [CodeFormatter] The formatter to use for code indentation
    # @return [String] Formatted variable declarations or just 'begin' if no variables
    def write_var_section(formatter)
      variables = collect_variables
      return formatter.indent('begin', @config) if variables.empty?

      format_var_declarations(formatter, variables)
    end

    # Formats the variable declarations in Pascal syntax
    # @param formatter [CodeFormatter] The formatter to use for code indentation
    # @param variables [Hash] Map of variable names to their Pascal types
    # @return [String] Formatted string containing all variable declarations
    def format_var_declarations(formatter, variables)
      var_section = formatter.indent('var', @config)
      formatter.increase_indent
      variables.each do |var_name, type|
        var_section << formatter.indent("#{var_name.to_camel_case}: #{type};", @config)
      end
      formatter.decrease_indent
      var_section << formatter.indent('begin', @config)
      var_section
    end

    # Collects all variables used in the test steps
    # @return [Hash] Map of variable names to their Pascal types
    def collect_variables
      collector = VariableCollector.new(@config, @functions)
      collector.collect_from_steps(@steps)
    end
  end
end
