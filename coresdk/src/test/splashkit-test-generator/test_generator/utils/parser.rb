# frozen_string_literal: true

module TestGenerator
  # Parses SplashKit API definitions to create function and parameter objects
  module Parser

    def self.parse_functions(api)
      all_functions = []
      api.each_value do |group|
        next unless group['functions'].is_a?(Array)

        # Create function objects for each function in the group
        group['functions'].each { |f| all_functions << create_function(f) }
      end
      all_functions
    end

    class << self
      private

      def create_function(func)
        Function.new(
          name: func['name'],
          unique_global_name: func['unique_global_name'],
          description: func['description'] || '',
          parameters: parse_parameters(func),
          return_type: func.dig('return', 'type'),
          type_parameter: func.dig('return', 'type_parameter'),
          return_description: func.dig('return', 'description'),
          group: func.dig('attributes', 'group') || 'other',
          suffix: func.dig('attributes', 'suffix'),
          signature: func.dig('signatures', 'cpp', 0)
        )
      end

      def parse_parameters(function)
        parameters = []
        return parameters unless function['parameters'].is_a?(Hash)

        function['parameters'].each do |param_name, info|
          parameters << Parameter.new(
            name: param_name,
            param_type: info['type'],
            description: info['description'] || '',
            is_array: info['is_array'] || false,
            array_dimension_sizes: info['array_dimension_sizes'] || []
          )
        end
        parameters
      end
    end
  end
end
