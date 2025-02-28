module TestGenerator
  # Collects and maps variables from test steps for pascal
  class VariableCollector
    def initialize(config, functions)
      @config = config
      @functions = functions
    end

    # Processes all test steps and builds a hash of variable names and their Pascal types
    # @param steps [Array] List of test steps to process
    # @return [Hash] Map of variable names to their Pascal types
    def collect_from_steps(steps)
      variables = {}
      steps.each do |step|
        search_for_variables(step, variables)
      end
      variables
    end

    private

    # Recursively searches through test step data structures to find variable declarations
    # @param item [Hash, Array] The current item being processed
    # @param variables [Hash] The collection of variables being built
    def search_for_variables(item, variables)
      case item
      when Hash
        check_for_loop(item, variables)
        check_for_store_result(item, variables)
        check_for_variable_step(item, variables)
        item.each_value { |v| search_for_variables(v, variables) }
      when Array
        item.each { |i| search_for_variables(i, variables) }
      end
    end

    # Adds loop counter variable 'i' when a loop step is encountered
    # @param item [Hash] The step being checked
    # @param variables [Hash] The collection of variables being built
    def check_for_loop(item, variables)
      return unless item.is_a?(Hash) && item[:type] == 'loop'

      variables['i'] = 'Integer'
    end

    # Processes function results that are stored in variables
    # @param item [Hash] The step being checked
    # @param variables [Hash] The collection of variables being built
    def check_for_store_result(item, variables)
      return unless item.is_a?(Hash) && item[:store_result] && item[:function_name]

      function = FunctionLookup.get_function_by_unique_global_name(item[:function_name], @functions)
      is_array = function.return_type == 'vector'
      type = is_array ? function.type_parameter : function.return_type
      variables[item[:store_result]] = map_type(type, is_array)
    end

    # Processes variable declaration steps
    # @param item [Hash] The step being checked
    # @param variables [Hash] The collection of variables being built
    def check_for_variable_step(item, variables)
      return unless item[:type] == 'variable' && item[:variable_type]
      # Handle variable references (copying type from another variable)
      return variables[item[:variable_name]] = variables[item[:value]] if item[:variable_type] == 'reference'

      is_class = item[:variable_type] == 'class_instance'
      is_array = item[:variable_type] == 'list'
      type = is_array ? item[:target_type] : item[:variable_type]
      type = is_class ? "t_#{item[:class_name]}" : type
      variables[item[:variable_name]] = map_type(type, is_array)
    end

    # Maps a type to its Pascal equivalent, handling arrays if necessary
    # @param type [String] The type to map
    # @param is_array [Boolean] Whether this type should be wrapped as an array
    # @return [String] The mapped Pascal type
    def map_type(type, is_array = false)
      mapped_type = @config.type_mapping[type] || type.to_pascal_case
      is_array ? "ArrayOf#{mapped_type}" : mapped_type
    end
  end
end
