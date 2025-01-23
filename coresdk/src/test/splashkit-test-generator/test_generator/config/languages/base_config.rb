module LanguageConfig
  # Base configuration class for all language configurations
  class BaseConfig
    def initialize(default_config)
      @config = deep_merge(build_config, default_config)
    end

    # Build the base configuration with default settings
    # @return [Hash] The base configuration hash
    def build_config
      {
        imports: [],
        indent_size: 4,
        assignment_operator: '=',
        identifier_cases: {
          cleanup:    :pascal_case,
          functions:  :snake_case,
          variables:  :snake_case,
          fields:     :snake_case,
          constants:  :upper_case
        },

        literal_cast: {
          unsigned_int: ->(value) { value },
          float: ->(value) { value },
          double: ->(value) { value }
        },

        comparison_cast: {
          unsigned_int: ->(value) { value },
          float: ->(value) { value },
          double: ->(value) { value }
        },

        variable_handlers: {
          declaration: {
            regular: ->(name) { "#{var_keyword}#{add_space}#{apply_case(name, :variables)} #{assignment_operator} " },
            string: ->(name) { "#{string_assignment_operator}#{add_space}#{apply_case(name, :variables)} #{assignment_operator} " },
            mutable: ->(name) { "#{var_mut_keyword}#{add_space}#{apply_case(name, :variables)} #{assignment_operator} " },
            reassignment: ->(name) { "#{apply_case(name, :variables)} #{assignment_operator} " }
          },
          reference_operator: ->(var) { var }
        },

        list_handlers: {
          prefix: ->(_) { '[' },
          suffix: ']',
          separator: ',',
          type_wrapper: ->(type) { type }
        },

        enum_handlers: {
          separator: '.'
        },

        array_handlers: {
          prefix: ->(arr) { "#{arr}[" },
          suffix: ']',
          separator: ']['
        },

        method_handlers: {
          prefix: ->(var, method) { "#{var}.#{method}(" },
          suffix: ')',
          separator: ', '
        },

        class_handlers: {
          prefix: ->(name) { "#{name}(" },
          suffix: ')',
          separator: ', '
        }.freeze,

        write_conditions: {
          constructor: ->(group_file) { group_file[:constructor] && !group_file[:constructor].empty? },
          tear_down: ->(group_file) { group_file[:cleanup] && !group_file[:cleanup].empty? && @config[:tear_down] },
          protected_section: ->(group_file) { should_write?(:constructor, group_file) || should_write?(:tear_down, group_file) }
        }
      }
    end

    # Retrieve the current configuration
    # @return [Hash] The current configuration
    def get
      @config
    end

    # Update the configuration with new options
    # @param options [Hash] The options to merge into the existing configuration
    def config=(options)
      @config.merge!(options)
    end

    # Apply the specified case to a value
    # @param value [String] The value to transform
    # @param type [Symbol] The type of identifier (e.g., :variables, :types)
    # @return [String] The case-transformed value
    def apply_case(value, type)
      case @config[:identifier_cases][type]
      when :snake_case then value.to_snake_case
      when :pascal_case then value.to_pascal_case
      when :camel_case then value.to_camel_case
      when :upper_case then value.to_upper_case
      else value
      end
    end

    # Determines if a specific section should be written
    # @param section [Symbol] The section to check (:constructor, :tear_down, etc.)
    # @param *args [Array] Arguments to pass to the condition check
    # @return [Boolean] True if the section should be written
    def should_write?(section, *args)
      return false unless @config[:write_conditions][section]

      @config[:write_conditions][section].call(*args)
    end

    # Format an identifier according to the configured case
    # @param name [String] The identifier to format
    # @return [String] The formatted identifier
    def format_identifier(name)
      apply_case(name, :variables)
    end

    # Format field access with proper case
    # @param var [String] The variable name
    # @param field [String] The field to access (can be nested)
    # @return [String] The formatted field access
    def format_field_access(var, field)
      parts = field.split('.')
      formatted_parts = []
      parts.each do |part|
        formatted_parts << apply_case(part, :fields)
      end
      "#{var}.#{formatted_parts.join('.')}"
    end

    # Format matrix access with configurable separator
    # @param var [String] The variable name
    # @param row [String] The row index
    # @param col [String] The column index
    # @return [String] The formatted matrix access
    def format_matrix_access(var, row, col)
      separator = @config[:array_handlers][:matrix_separator] || @config[:array_handlers][:separator]
      "#{var}[#{row}#{separator}#{col}]"
    end

    # Format a list with optional type wrapping
    # @param values [Array] The list of values
    # @param target_type [String, nil] Optional type for the list
    # @return [String] The formatted list
    def format_list(values, target_type = nil)
      handlers = @config[:list_handlers]
      if target_type
        mapped_type = @config[:type_mapping]&.[](target_type) || target_type
        type_str = handlers[:type_wrapper] ? handlers[:type_wrapper].call(mapped_type) : ''
      else
        type_str = ''
      end
      "#{handlers[:prefix].call(type_str)}#{values.join(handlers[:separator])}#{handlers[:suffix]}"
    end

    # Format an enum value with proper case
    # @param type [String] The enum type
    # @param value [String] The enum value
    # @return [String] The formatted enum value
    def format_enum(type, value)
      type_formatted = apply_case(type, :types)
      value_formatted = apply_case(value, :constants)
      separator = @config[:enum_handlers][:separator]
      "#{type_formatted}#{separator}#{value_formatted}"
    end

    # Format array access with configurable handlers
    # @param var [String] The variable name
    # @param indices [Array] The indices to access
    # @return [String] The formatted array access
    def format_array_access(var, *indices)
      handlers = @config[:array_handlers]
      "#{handlers[:prefix].call(var)}#{indices.join(handlers[:separator])}#{handlers[:suffix]}"
    end

    # Format a method call with proper case
    # @param var [String] The variable or object
    # @param method [String] The method name
    # @param args [Array] The method arguments
    # @return [String] The formatted method call
    def format_method_call(var, method, *args)
      handlers = @config[:method_handlers]
      formatted_var = apply_case(var, :variables)
      formatted_method = apply_case(method, :functions)
      "#{handlers[:prefix].call(formatted_var, formatted_method)}#{args.join(handlers[:separator])}#{handlers[:suffix]}"
    end

    # Format a class instance creation
    # @param name [String] The class name
    # @param args [Array] The constructor arguments
    # @return [String] The formatted class instance creation
    def format_class_instance(name, args)
      handlers = @config[:class_handlers]
      formatted_name = apply_case(name, :types)
      formatted_args = args.join(handlers[:separator])
      "#{handlers[:prefix].call(formatted_name)}#{formatted_args}#{handlers[:suffix]}"
    end

    # Format a test function name
    # @param group [String] The test group name
    # @param name [String] The test function name
    # @return [String] The formatted test function name
    def format_test_function(group, name)
      formatted_group = apply_case(group, :types)
      formatted_name = apply_case(name, :functions)
      @config[:function_handlers][:test].call(formatted_group, formatted_name)
    end

    # Format a function call
    # @param name [String] The function name
    # @param args [String] The function arguments
    # @return [String] The formatted function call
    def format_function_call(name, args)
      formatted_name = apply_case(name, :functions)
      "#{formatted_name}(#{args})"
    end

    # Format a cleanup operation
    # @param name [String] The variable name
    # @param type [String] The cleanup type
    # @param args [String, nil] Optional arguments for cleanup
    # @return [String] The formatted cleanup operation
    def format_cleanup(name, type, args = nil)
      formatted_name = apply_case(name, :variables)
      formatted_type = apply_case(type, :cleanup)
      @config[:cleanup_handlers][:setup].call(formatted_name, formatted_type, args)
    end

    private

    # Get the variable keyword from configuration
    # @return [String] The variable keyword
    def var_keyword
      @config[:var_keyword]
    end

    # Get the mutable variable keyword from configuration
    # @return [String] The mutable variable keyword
    def var_mut_keyword
      @config[:var_keyword] + (@config[:var_mut_keyword] ? " #{@config[:var_mut_keyword]}" : '')
    end

    # Get the assignment operator from configuration
    # @return [String] The assignment operator
    def assignment_operator
      @config[:assignment_operator]
    end

    # Get the string assignment operator from configuration
    # @return [String] The string assignment operator
    def string_assignment_operator
      @config[:string_keyword] || var_keyword
    end

    # Determine if a space should be added after the variable keyword
    # @return [String] A space or an empty string
    def add_space
      @config[:var_keyword].empty? ? '' : ' '
    end

    # Perform a deep merge of two hashes
    # @param base [Hash] The base configuration
    # @param override [Hash] The configuration to override base with
    # @return [Hash] The merged configuration
    def deep_merge(base, override)
      result = base.dup
      override.each do |key, value|
        if value.is_a?(Hash) && result[key].is_a?(Hash)
          result[key] = deep_merge(result[key], value)
        elsif value.is_a?(Array) && result[key].is_a?(Array)
          result[key] = result[key] + value
        else
          result[key] = value
        end
      end
      result
    end
  end
end
