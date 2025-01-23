module TestGenerator
  # Class responsible for writing individual test steps based on their type and configuration
  class StepWriter
    def initialize(step, functions, config, formatter)
      @step = step
      @functions = functions
      @config = config
      @formatter = formatter
    end

    # Writes a test step using a new instance of StepWriter
    # @param step [Hash] The test step to write
    # @param functions [Array<Function>] Available functions
    # @param config [Object] Language configuration
    # @param formatter [CodeFormatter] Code formatting utility
    # @return [String] The formatted test step code
    def self.write_test_step(step, functions, config, formatter)
      new(step, functions, config, formatter).write
    end

    def write
      type = @step[:type]
      method_name = "write_#{type}_step"

      if respond_to?(method_name, true)
        send(method_name)
      else
        MessageHandler.log_warning("Unimplemented step type: #{type}")
        puts ": #{JSON.pretty_generate(@step)}"
        @formatter.indent("# TODO: Implement #{type} step", @config)
      end
    rescue StandardError => e
      MessageHandler.log_error("Error in step #{type}", e.message)
      raise TestGeneratorError, "Failed to write #{type} step: #{e.message}"
    end

    private

    # Writes a variable declaration step
    # @return [String] Formatted variable declaration code
    def write_variable_step
      declaration_op = declaration
      declaration = declaration_op.call(@step[:variable_name])
      step_clone = @step.clone
      step_clone[:type] = step_clone[:variable_type]
      value = ValueFormatter.format_value(step_clone, @functions, @config)
      @formatter.indent("#{declaration}#{value}", @config, true)
    end

    # Writes a function call step
    # @return [String] Formatted function call code
    def write_function_step
      call = ValueFormatter.format_value(@step, @functions, @config)
      if @step[:store_result]
        declaration_op = declaration
        declaration = declaration_op.call(@step[:store_result])
        @formatter.indent("#{declaration}#{call}", @config, true)
      else
        @formatter.indent(call, @config, true)
      end
    end

    # Gets the appropriate declaration handler based on variable type and mutability
    # @param handlers [Hash] The variable handlers configuration
    # @return [Proc] The declaration handler to use
    def declaration
      handlers = @config.variable_handlers
      if @step[:variable_type] == 'string' && handlers[:declaration][:string]
        handlers[:declaration][:string]
      elsif @step[:is_mutable]
        handlers[:declaration][:mutable]
      else
        handlers[:declaration][:regular]
      end
    end

    # Writes an assertion step
    # @return [String] Formatted assertion code
    def write_assertion_step
      comparison = @step[:compare]
      value1 = ValueFormatter.format_value(comparison[:value1], @functions, @config)
      value2 = comparison[:value2] ? ValueFormatter.format_value(comparison[:value2], @functions, @config) : nil
      value3 = comparison[:value3] ? ValueFormatter.format_value(comparison[:value3], @functions, @config) : nil

      @formatter.indent(@config.assert_conditions[comparison[:compare_type]].call(value1, value2, value3), @config)
    end

    # Writes a loop step
    # @return [String] Formatted loop code
    def write_loop_step
      loop_code = @formatter.indent(@config.control_flow[:loop].call(@step[:iterations]), @config)
      @step[:loop_steps].each do |inner_step|
        loop_code << self.class.write_test_step(inner_step, @functions, @config, @formatter)
      end
      loop_code << @formatter.indent(@config.control_flow[:end].call, @config)
      loop_code
    end

    # Writes a condition for if or while steps
    # @param comparison [Hash] The comparison configuration
    # @return [String] Formatted condition code
    # @raise [StandardError] If comparison type is unsupported
    def write_condition(comparison)
      type = comparison[:compare_type]
      value1 = ValueFormatter.format_value(comparison[:value1], @functions, @config)
      value2 = comparison[:value2] ? ValueFormatter.format_value(comparison[:value2], @functions, @config) : nil
      @config.if_conditions.fetch(type) do
        MessageHandler.log_error("Unsupported comparison type: #{type}", comparison)
        raise "Unsupported comparison type: #{type}"
      end.call(value1, value2)
    end

    # Writes an if-else step
    # @return [String] Formatted if-else code
    def write_if_step
      condition_code = write_condition(@step[:compare])
      if_code = @formatter.indent(@config.control_flow[:if].call(condition_code), @config)
      @step[:then_steps].each do |then_step|
        if_code << self.class.write_test_step(then_step, @functions, @config, @formatter)
      end
      if_code << @formatter.indent(@config.control_flow[:end].call, @config)
      if_code << write_else_steps
      if_code
    end

    # Writes the else part of an if-else step
    # @return [String] Formatted else code
    def write_else_steps
      return '' unless @step[:else_steps]

      else_code = @formatter.indent(@config.control_flow[:else].call, @config)
      @step[:else_steps].each do |else_step|
        else_code << self.class.write_test_step(else_step, @functions, @config, @formatter)
      end
      else_code << @formatter.indent(@config.control_flow[:end].call, @config)
      else_code
    end

    # Writes a while loop step
    # @return [String] Formatted while loop code
    def write_while_step
      condition = write_condition(@step[:compare]).strip
      while_code = @formatter.indent(@config.control_flow[:while].call(condition), @config)
      @step[:while_steps].each do |inner_step|
        while_code << self.class.write_test_step(inner_step, @functions, @config, @formatter)
      end
      while_code << @formatter.indent(@config.control_flow[:end].call, @config)
      while_code
    end

    # Writes a variable reassignment step
    # @return [String] Formatted reassignment code
    def write_reassignment_step
      reassignment_op = @config.variable_handlers[:declaration][:reassignment].call(@step[:variable_name])
      step_clone = @step.clone
      step_clone[:type] = step_clone[:reassignment_type]
      value = ValueFormatter.format_value(step_clone, @functions, @config)
      @formatter.indent("#{reassignment_op}#{value}", @config, true)
    end

    # Writes a prompt step that displays a message to the user
    # @return [String] Formatted prompt code (e.g., cout, print, Console.WriteLine etc.)
    def write_message_step
      @formatter.indent(@config.terminal_handlers[:message].call(@step[:message]), @config)
    end

    # Writes a cleanup step
    # @return [String] Formatted cleanup code
    def write_cleanup_step
      args = format_args(@step[:args])
      cleanup = @config.format_cleanup(@step[:store_result], @step[:cleanup_type], args)
      @formatter.indent(cleanup, @config)
    end

    def format_args(args)
      args.map { |arg| ValueFormatter.format_value(arg, @functions, @config) }.join(', ')
    end

    # Writes a delegate call step
    # @return [String] Formatted delegate call code
    def write_method_call_step
      method_call = ValueFormatter.format_value(@step, @functions, @config)
      @formatter.indent(method_call, @config, true)
    end
  end
end
