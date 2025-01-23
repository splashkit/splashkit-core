module TestGenerator
  # Handles tear down and cleanup test code generation
  class TearDownHandler
    def initialize(config)
      @config = config
    end

    # Generates tear down related test lines if conditions are met
    # @param group [String] The test group name
    # @param cleanup_steps [Array] Steps to be cleaned up
    # @return [Array] Array of formatted test lines
    def lines(group, group_file)
      return [] unless @config.should_write?(:tear_down, group_file)

      [
        *header_lines(group),
        *step_lines(group_file[:cleanup]),
        *footer_lines
      ]
    end

    private

    # Generates header lines with proper group name formatting
    # @param group [String] The test group name
    # @return [Array, String] Formatted header lines
    def header_lines(group)
      formatted_group = @config.apply_case(group, :types)
      @config.tear_down[:header].call(formatted_group)
    end

    # Formats cleanup steps into test lines
    # @param cleanup_steps [Array] Steps to be cleaned up
    # @return [Array] Formatted cleanup step lines
    def step_lines(cleanup_steps)
      cleanup_steps.flat_map do |step|
        formatted_type = @config.apply_case(step[:cleanup_type], :types)
        @config.cleanup_handlers[:free].call(formatted_type)
      end
    end

    # Returns footer configuration for tear down wrapper
    # @return [Array, String] Footer lines for tear down
    def footer_lines
      @config.tear_down[:footer]
    end
  end
end
