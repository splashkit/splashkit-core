module TestGenerator
  # Handles the generation of class wrapper code for test files
  class ClassWrapperHandler
    def initialize(config)
      @config = config
    end

    # Gets the header lines for the class wrapper
    # @param group [String] The group name for the test class
    # @return [Array<String>] Array of header lines, with procs evaluated
    def header_lines(group, group_file, tests)
      formatted_group = @config.apply_case(group, :types)
      @config.class_wrapper[:header].map do |line|
        if line == 'published_functions' && @config.language == :pascal
          write_published_section(tests, group_file)
        elsif line == 'private_vars' && @config.language == :pascal
          write_private_vars(group_file)
        else
          line.is_a?(Proc) ? line.call(formatted_group) : line
        end
      end.flatten
    end

    # Gets the footer lines for the class wrapper
    # @return [Array<String>] Array of footer lines
    def footer_lines(group)
      formatted_group = @config.apply_case(group, :types)
      @config.class_wrapper[:footer].map do |line|
        line.is_a?(Proc) ? line.call(formatted_group) : line
      end
    end

    private

    # Writes the private vars for Pascal test classes
    # @param file [File] File handle to write to
    # @return [void]
    def write_private_vars(group_file)
      return [] unless group_file[:cleanup]

      ['private'] + group_file[:cleanup].map do |step|
        "cleanup#{step[:cleanup_type].to_pascal_case}: #{step[:cleanup_type].to_pascal_case}Cleanup;"
      end
    end

    # Writes the published section for Pascal test classes
    # @param file [File] File handle to write to
    # @return [void]
    def write_published_section(tests, group_file)
      lines = []
      tests.each do |test|
        lines << "procedure Test#{test[:name].to_pascal_case}Integration;"
      end
      lines += write_protected_section(group_file)
      lines
    end

    # Writes the protected section with setup and tear down declarations
    # @param file [File] File handle to write to
    # @return [void]
    def write_protected_section(group_file)
      return [] unless @config.should_write?(:protected_section, group_file)

      lines = ['protected']
      lines << write_protected_line(:setup) if @config.should_write?(:constructor, group_file)
      lines << write_protected_line(:tear_down) if @config.should_write?(:tear_down, group_file)
      lines
    end

    def write_protected_line(section_type)
      @config.class_wrapper[:publish][section_type]
    end
  end
end
