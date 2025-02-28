module TestGenerator
  # Class responsible for validating language configuration handlers and their required methods
  class ConfigValidator
    # List of required configuration handlers that must be present
    REQUIRED_KEYS = %i[
      language identifier_cases indent_size file_extension imports assert_conditions
      if_conditions control_flow string_handlers supports_overloading class_wrapper
      numeric_constants terminal_handlers comment_syntax indentation literal_cast
      statement_terminator variable_handlers function_handlers cleanup_handlers
      array_handlers method_handlers list_handlers class_handlers
    ].freeze

    # Creates a new validator instance
    # @param config [Object] The configuration object to validate
    def initialize(config)
      @config = config.is_a?(Hash) ? config : {}
    end

    # Validates a configuration by creating a new validator instance
    # @param config [Object] The configuration to validate
    # @return [Boolean] True if validation passes
    # @raise [StandardError] If validation fails
    def self.validate!(config)
      new(config).validate!
    end

    # Performs all validation checks
    # @return [Boolean] True if all validations pass
    # @raise [StandardError] If any validation fails
    def validate!
      validate_required_keys
      validate_handler_methods
      true
    end

    private

    # Checks for presence of all required handlers
    # @raise [StandardError] If any required handlers are missing
    def validate_required_keys
      missing = REQUIRED_KEYS - @config.keys
      raise "Missing required handlers: #{missing.join(', ')}" if missing.any?
    end

    # Validates all handler method requirements
    # @return [void]
    def validate_handler_methods
      validate_variable_handlers
      validate_function_handlers
      validate_control_flow
      validate_string_handlers
      validate_assert_conditions
      validate_if_conditions
      validate_class_wrapper
      validate_comment_syntax
      validate_indentation
      validate_cleanup_handlers
      validate_literal_cast
      validate_terminal_handlers
      validate_list_handlers
      validate_class_handlers
      validate_method_handlers
      validate_array_handlers
      validate_enum_handlers
      validate_numeric_constants
      validate_identifier_cases
    end

    # Validates required variable handler methods
    # @return [void]
    def validate_variable_handlers
      required = %i[array_size reference_operator declaration]
      validate_methods(@config[:variable_handlers], required, 'variable_handlers')
    end

    # Validates required function handler methods
    # @return [void]
    def validate_function_handlers
      required = %i[test]
      validate_methods(@config[:function_handlers], required, 'function_handlers')
    end

    # Validates required control flow methods
    # @return [void]
    def validate_control_flow
      required = %i[loop while if else break end]
      validate_methods(@config[:control_flow], required, 'control_flow')
    end

    # Validates required string handler methods
    # @return [void]
    def validate_string_handlers
      required = %i[char format_string string string_ref]
      validate_methods(@config[:string_handlers], required, 'string_handlers')
    end

    # Validates required assert condition methods
    # @return [void]
    def validate_assert_conditions
      required = %w[equal not_equal greater_than less_than null not_null range true false
                    greater_than_or_equal less_than_or_equal throws not_empty contains empty]
      validate_methods(@config[:assert_conditions], required, 'assert_conditions')
    end

    # Validates required if condition methods
    # @return [void]
    def validate_if_conditions
      required = %w[greater_than true false equal not_equal]
      validate_methods(@config[:if_conditions], required, 'if_conditions')
    end

    # Validates required class wrapper methods
    # @return [void]
    def validate_class_wrapper
      required = %i[header constructor_wrapper footer]
      validate_methods(@config[:class_wrapper], required, 'class_wrapper')
    end

    # Validates required comment syntax methods
    # @return [void]
    def validate_comment_syntax
      required = %i[single multi_start multi_end]
      validate_methods(@config[:comment_syntax], required, 'comment_syntax')
    end

    # Validates required indentation rules
    # @return [void]
    def validate_indentation
      required = %i[indent_after unindent_before]
      validate_methods(@config[:indentation], required, 'indentation')
    end

    # Validates required cleanup handler methods
    # @return [void]
    def validate_cleanup_handlers
      return unless @config[:cleanup_handlers]

      required = %i[setup]
      validate_methods(@config[:cleanup_handlers], required, 'cleanup_handlers')
    end

    # Validates required literal cast methods
    # @return [void]
    def validate_literal_cast
      required = %i[unsigned_int float double]
      validate_methods(@config[:literal_cast], required, 'literal_cast')
    end

    # Validates required terminal handler methods
    # @return [void]
    def validate_terminal_handlers
      required = %i[message]
      validate_methods(@config[:terminal_handlers], required, 'terminal_handlers')
    end

    # Validates required list handler methods
    # @return [void]
    def validate_list_handlers
      required = %i[prefix suffix separator]
      validate_methods(@config[:list_handlers], required, 'list_handlers')
    end

    # Validates required class handler methods
    # @return [void]
    def validate_class_handlers
      required = %i[prefix suffix separator]
      validate_methods(@config[:class_handlers], required, 'class_handlers')
    end

    # Validates required method handler methods
    # @return [void]
    def validate_method_handlers
      required = %i[prefix suffix separator]
      validate_methods(@config[:method_handlers], required, 'method_handlers')
    end

    # Validates required array handler methods
    # @return [void]
    def validate_array_handlers
      required = %i[prefix suffix separator]
      validate_methods(@config[:array_handlers], required, 'array_handlers')
    end

    # Validates required enum handler methods
    # @return [void]
    def validate_enum_handlers
      required = %i[separator]
      validate_methods(@config[:enum_handlers], required, 'enum_handlers')
    end

    # Validates required numeric constant methods
    # @return [void]
    def validate_numeric_constants
      required = %i[infinity negative_infinity max_value]
      validate_methods(@config[:numeric_constants], required, 'numeric_constants')
    end

    # Validates required identifier case methods
    # @return [void]
    def validate_identifier_cases
      required = %i[cleanup functions variables fields constants]
      validate_methods(@config[:identifier_cases], required, 'identifier_cases')
    end

    # Validates that a handler has all required methods
    # @param handler [Object] The handler to validate
    # @param required_methods [Array<Symbol>] List of required method names
    # @param handler_name [String] Name of the handler for error messages
    # @raise [StandardError] If handler is invalid or missing required methods
    def validate_methods(handler, required_methods, handler_name)
      raise "Invalid or missing handler: #{handler_name}" if handler.nil? || !handler.respond_to?(:keys)

      missing = required_methods - handler.keys
      return unless missing.any?

      error_msg = "Missing required methods in #{handler_name} for #{@config[:language]}: #{missing.join(', ')}"
      MessageHandler.log_error(error_msg)
      raise error_msg
    end
  end
end
