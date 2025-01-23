module TestGenerator
  # Formats values for test generation based on their type and language configuration
  module ValueFormatter
    class << self
      # Checks if running in Windows Subsystem for Linux (WSL)
      # WSL uses a different graphics and window manager than Windows,
      # which can lead to different window/element sizes when created.
      # this is because it reserves space for borders and title bars
      # The alt_value is used for WSL environments, while the normal
      # value is used for native Windows environments.
      def is_wsl
        @is_wsl ||= system('uname -r | grep -q "WSL"')
      end
      # Maps value types to their corresponding formatting methods
      # @return [Hash<String, Symbol>] Map of value types to formatter method names
      def formatter_map
        @formatter_map ||= {
          'function'                  => :format_function_value,
          'variable'                  => :format_variable_value,
          'variable_field'            => :format_variable_field_value,
          'variable_matrix_access'    => :format_variable_matrix_access_value,
          'list'                      => :format_list_value,
          'array_access'              => :format_array_access_value,
          'array_access_field'        => :format_array_access_field_value,
          'double'                    => :format_primitive_value,
          'int'                       => :format_primitive_value,
          'bool'                      => :format_boolean_value,
          'string'                    => :format_string_value,
          'string_ref'                => :format_string_ref_value,
          'float'                     => :format_float_value,
          'enum'                      => :format_enum_value,
          'inf'                       => :format_infinity_value,
          'neg_inf'                   => :format_neg_infinity_value,
          'char'                      => :format_char_value,
          'max_value'                 => :format_max_value,
          'interpolated_string'       => :format_interpolated_string_value,
          'class_instance'            => :format_class_instance_value,
          'unsigned_int'              => :format_unsigned_int_value,
          'unsigned_short'            => :format_primitive_value,
          'ref'                       => :format_ref_value,
          'size'                      => :format_array_size_value,
          'object'                    => :format_object_value,
          'precision'                 => :format_primitive_value,
          'method_call'               => :format_method_call_value,
          'reference'                 => :format_reference_value
        }.freeze
      end

      # Formats the value based on its type
      # @param value [Hash] The value to format
      # @param functions [Array] Available functions
      # @param config [Hash] Language configuration
      # @return [String] The formatted value
      def format_value(value, functions, config)
        return value.to_s if value.nil? || !value.is_a?(Hash)

        formatter = formatter_map[value[:type]]
        if formatter
          send(formatter, value, functions, config)
        else
          MessageHandler.log_warning("Unknown value type: #{value[:type]}")
          puts "value: #{JSON.pretty_generate(value)}"
          value.to_s
        end
      rescue StandardError => e
        MessageHandler.log_error('Value formatting error', e.message)
        raise HandlerError, "Failed to format value: #{e.message}"
      end

      # Formats function values with arguments
      # @param value [Hash] The function value to format
      # @param functions [Array] Available functions
      # @param config [Hash] Language configuration
      # @return [String] The formatted function call
      # @raise [StandardError] If function name is missing
      def format_function_value(value, functions, config)
        args = (value[:args] || []).map { |arg| format_value(arg, functions, config) }.join(', ')
        function_name = FunctionLookup.determine_function_name(value, config, functions)
        raise "Function name is required for function value #{JSON.pretty_generate(value)}" unless function_name

        result = config.format_function_call(function_name, args)
        if value[:cast_to] && config.comparison_cast
          result = config.comparison_cast[value[:cast_to].to_sym].call(result)
        end
        result
      end

      # Formats variable references
      # @param value [Hash] The variable value to format
      # @param _ [Array] Unused functions parameter
      # @param config [Hash] Language configuration
      # @return [String] The formatted variable reference
      def format_variable_value(value, _, config)
        config.format_identifier(value[:variable_name])
      end

      # Formats field access on variables
      # @param value [Hash] The field access value to format
      # @param functions [Array] Available functions
      # @param config [Hash] Language configuration
      # @return [String] The formatted field access
      def format_variable_field_value(value, functions, config)
        variable_value = format_variable_value(value, functions, config)
        config.format_field_access(variable_value, value[:variable_field])
      end

      # Formats primitive values
      # @param value [Hash] The primitive value to format
      # @return [String] The formatted primitive value
      def format_primitive_value(value, _, _)
        if value[:alt_value] && is_wsl
          value[:alt_value].inspect
        else
          value[:value].inspect
        end
      end

      # Formats enum values
      # @param value [Hash] The enum value to format
      # @param config [Hash] Language configuration
      # @return [String] The formatted enum value
      def format_enum_value(value, _, config)
        config.format_enum(value[:enum_type], value[:value])
      end

      # Formats matrix access on variables
      # @param value [Hash] The matrix access value to format
      # @param functions [Array] Available functions
      # @param config [Hash] Language configuration
      # @return [String] The formatted matrix access
      def format_variable_matrix_access_value(value, functions, config)
        variable_value = format_variable_value(value, functions, config)
        variable_with_field = config.format_field_access(variable_value, value[:field])
        config.format_matrix_access(variable_with_field, value[:row], value[:col])
      end

      # Formats array access values
      # @param value [Hash] The array access value to format
      # @param config [Hash] Language configuration
      # @return [String] The formatted array access
      def format_array_access_value(value, _, config)
        array_identifier = config.format_identifier(value[:array_name])
        config.format_array_access(array_identifier, value[:index])
      end

      # Formats list values
      # @param value [Hash] The list value to format
      # @param functions [Array] Available functions
      # @param config [Hash] Language configuration
      # @return [String] The formatted list
      def format_list_value(value, functions, config)
        values = value[:value].map { |v| format_value(v, functions, config) }
        config.format_list(values, value[:target_type])
      end

      # Formats field access on array elements
      # @param value [Hash] The array field access value to format
      # @param config [Hash] Language configuration
      # @return [String] The formatted array field access
      def format_array_access_field_value(value, _, config)
        identifier = config.format_identifier(value[:variable_name])
        array_access = config.format_field_access(identifier, value[:array_name])
        array_with_index = config.format_array_access(array_access, value[:index])
        config.format_field_access(array_with_index, value[:field])
      end

      # Formats infinity constant
      # @param config [Hash] Language configuration
      # @return [String] The language-specific infinity constant
      def format_infinity_value(_, _, config)
        config.numeric_constants[:infinity]
      end

      # Formats negative infinity constant
      # @param config [Hash] Language configuration
      # @return [String] The language-specific negative infinity constant
      def format_neg_infinity_value(_, _, config)
        config.numeric_constants[:negative_infinity]
      end

      # Formats character values
      # @param value [Hash] The character value to format
      # @param config [Hash] Language configuration
      # @return [String] The formatted character value
      def format_char_value(value, _, config)
        config.string_handlers[:char].call(value[:value])
      end

      # Formats maximum value constant
      # @param config [Hash] Language configuration
      # @return [String] The language-specific maximum value constant
      def format_max_value(_, _, config)
        config.numeric_constants[:max_value]
      end

      # Formats interpolated strings
      # @param value [Hash] The interpolated string value to format
      # @param functions [Array] Available functions
      # @param config [Hash] Language configuration
      # @return [String] The formatted interpolated string
      def format_interpolated_string_value(value, functions, config)
        text_parts = []
        expressions = []
        value[:parts].each do |part|
          if part[:type] == 'text'
            text_parts << part[:value]
          else
            expressions << format_value(part[:expression], functions, config)
          end
        end
        config.string_handlers[:format_string].call(text_parts, expressions)
      end

      # Formats class instance creation
      # @param value [Hash] The class instance value to format
      # @param functions [Array] Available functions
      # @param config [Hash] Language configuration
      # @return [String] The formatted class instance creation
      # @raise [StandardError] If class name is missing
      def format_class_instance_value(value, functions, config)
        formatted_args = (value[:args] || []).map { |arg| format_value(arg, functions, config) }
        raise "Class name is required for class instance value #{JSON.pretty_generate(value)}" unless value[:class_name]

        config.format_class_instance(value[:class_name], formatted_args)
      end

      # Formats array size access
      # @param value [Hash] The array size value to format
      # @param _ [Array] Unused functions parameter
      # @param config [Hash] Language configuration
      # @return [String] The formatted array size access
      def format_array_size_value(value, _, config)
        array_identifier = config.format_identifier(value[:variable_name])
        config.variable_handlers[:array_size].call(array_identifier)
      end

      # Formats float values
      # @param value [Hash] The float value to format
      # @return [String] The formatted float value
      def format_float_value(value, _, config)
        config.literal_cast[:float].call(value[:value])
      end

      # Formats unsigned integer values
      # @param value [Hash] The unsigned integer value to format
      # @param _ [Array] Unused functions parameter
      # @param config [Hash] Language configuration
      # @return [String] The formatted unsigned integer value
      def format_unsigned_int_value(value, _, config)
        config.literal_cast[:unsigned_int].call(value[:value])
      end

      # Formats reference values
      # @param value [Hash] The ref value to format
      # @param functions [Array] Available functions
      # @param config [Hash] Language configuration
      # @return [String] The formatted reference
      def format_ref_value(value, _, config)
        identifier = config.format_identifier(value[:variable_name])
        config.variable_handlers[:reference_operator].call(identifier)
      end

      # Formats reference values
      # @param value [Hash] The reference value to format
      # @param _ [Array] Unused functions parameter
      # @param config [Hash] Language configuration
      # @return [String] The formatted reference
      def format_reference_value(value, _, config)
        config.format_identifier(value[:value])
      end

      # Formats string values
      # @param value [Hash] The string value to format
      # @param _ [Array] Unused functions parameter
      # @param config [Hash] Language configuration
      # @return [String] The formatted string value
      def format_string_value(value, _, config)
        config.string_handlers[:string].call(value[:value])
      end

      # Formats string reference values
      # @param value [Hash] The string reference value to format
      # @param _ [Array] Unused functions parameter
      # @param config [Hash] Language configuration
      # @return [String] The formatted string reference
      def format_string_ref_value(value, _, config)
        config.string_handlers[:string_ref].call(value[:value])
      end

      # # Formats object values
      # # @param value [Hash] The object value to format
      # # @param _ [Array] Unused functions parameter
      # # @param config [Hash] Language configuration
      # # @return [String] The formatted object
      # def format_object_value(value, _, config)
      #   config.type_handlers[:object].call(value[:object_type], value[:variable_name])
      # end

      # Formats method call values
      # @param value [Hash] The method call value to format
      # @param config [Hash] Language configuration
      # @return [String] The formatted method call
      def format_method_call_value(value, _, config)
        config.format_method_call(value[:variable_name], value[:method_name], value[:args])
      end

      # Formats boolean values
      # @param value [Hash] The boolean value to format
      # @param _ [Array] Unused functions parameter
      # @param config [Hash] Language configuration
      # @return [String] The formatted boolean value
      def format_boolean_value(value, _, config)
        bool_value = value[:value]
        mapping = config.boolean_mapping&.[](bool_value)
        mapping || bool_value.to_s
      end
    end
  end
end
