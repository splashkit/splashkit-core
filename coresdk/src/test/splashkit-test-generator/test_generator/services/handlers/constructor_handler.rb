module TestGenerator
  # Handles constructor-related test code generation
  class ConstructorHandler
    def initialize(config)
      @config = config
    end

    # Generates constructor-related test lines if conditions are met
    # @param group [String] The test group name
    # @param constructor_steps [Array] Steps to be executed in constructor
    # @return [Array] Array of formatted test lines
    def lines(group, group_file, functions, formatter)
      return [] unless @config.should_write?(:constructor, group_file)

      [
        *header_lines(group),
        *step_lines(group_file, functions, formatter),
        *footer_lines
      ]
    end

    private

    # Generates header lines with proper group name formatting
    # @param group [String] The test group name
    # @return [Array, String] Formatted header lines
    def header_lines(group)
      formatted_group = @config.apply_case(group, :types)
      header = @config.class_wrapper[:constructor_wrapper][:header]
      header.is_a?(Proc) ? header.call(formatted_group) : header
    end

    # Processes each constructor step, with special handling for resource paths
    # @param steps [Array] Array of step definitions
    # @return [Array] Formatted test steps
    def step_lines(group_file, functions, formatter)
      group_file[:constructor].map do |step|
        step = update_resources_path(step) if step[:function_name] == 'set_resources_path'
        StepWriter.write_test_step(step, functions, @config, formatter)
      end
    end

    # Returns footer configuration for constructor wrapper
    # @return [Array, String] Footer lines for constructor
    def footer_lines
      @config.class_wrapper[:constructor_wrapper][:footer]
    end

    # Updates resource path to absolute path based on current file location
    # This is for the set_resources_path splashkit function.
    # @param step [Hash] The step definition to update
    # @return [Hash] Updated step with absolute resource path
    def update_resources_path(step)
      step = step.dup
      step[:args] = step[:args].map(&:dup)
      step[:args][0][:value] = DirectoryManager::RESOURCES_DIR
      step
    end
  end
end
