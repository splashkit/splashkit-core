module TestGenerator
  # Class responsible for handling code indentation and formatting in test generation
  class CodeFormatter
    attr_reader :level

    def initialize(indent_size)
      @indent_size = indent_size
      @level = 0
    end

    # Indents text with the current indentation level
    # @param text [String, Object] The text to indent
    # @param config [Hash] The language configuration
    # @param add_terminator [Boolean] Whether to add a statement terminator
    # @return [String] The indented text
    def indent(text, config, add_terminator = false)
      text_str = text.to_s
      return handle_block_end if block_end?(text_str, config)

      handle_indent(text_str, config, add_terminator)
    end

    # Increases the indentation level by one
    # @return [void]
    def increase_indent
      @level += 1
    end

    # Decreases the indentation level by one if possible
    # @return [void]
    def decrease_indent
      @level -= 1 if @level > 0
    end

    # Formats and indents a single line of code
    # @param line [String] The line to format
    # @return [String] The formatted and indented line
    def format_line(line, config)
      return '' if line.nil? || line.empty?

      indent(line.strip, config)
    end

    # Adds the language-specific statement terminator if configured (e.g. ; in C++)
    # @param text [String] The text to add the line operator to
    # @param config [Hash] The language configuration
    # @return [String] The text with line operator added if configured
    def add_statement_terminator(text, config)
      return text unless config.statement_terminator

      text + config.statement_terminator
    end

    private

    # Handles regular indentation for non-block-end text
    # @param text_str [String] The text to indent
    # @param config [Hash] The language configuration
    # @param add_terminator [Boolean] Whether to add a statement terminator
    # @return [String] The indented text
    def handle_indent(text_str, config, add_terminator)
      check_reset_patterns(text_str, config)
      check_unindent_patterns(text_str, config)
      indented_text = create_indented_text(text_str, config, add_terminator)
      check_indent_patterns(text_str, config)
      indented_text
    end

    # Checks if the text matches any unindent patterns and decreases indent if needed
    # @param text_str [String] The text to check
    # @param config [Hash] The language configuration
    def check_unindent_patterns(text_str, config)
      config.indentation[:unindent_before]&.any? { |pattern| text_str.strip.end_with?(pattern) } && decrease_indent
    end

    # Checks if the text matches any indent patterns and increases indent if needed
    # @param text_str [String] The text to check
    # @param config [Hash] The language configuration
    def check_indent_patterns(text_str, config)
      config.indentation[:indent_after]&.any? { |pattern| text_str.strip.end_with?(pattern) } && increase_indent
    end

    # Creates indented text with proper spacing and terminators
    # @param text_str [String] The text to indent
    # @param config [Hash] The language configuration
    # @param add_terminator [Boolean] Whether to add a statement terminator
    # @return [String] The formatted text with indentation
    def create_indented_text(text_str, config, add_terminator)
      base_text = add_terminator ? add_statement_terminator(text_str, config) : text_str
      "#{' ' * (@level * @indent_size)}#{base_text}\n"
    end

    # Checks if the text matches any reset patterns and sets the indentation level
    # @param text_str [String] The text to check for reset patterns
    # @param config [Hash] The language configuration containing reset patterns and their target levels
    def check_reset_patterns(text_str, config)
      config.indentation[:reset_on]&.each do |pattern, target_level|
        if text_str.strip.start_with?(pattern)
          @level = target_level
          break
        end
      end
    end

    # Checks if the text is a block end marker
    # @param text_str [String] The text to check
    # @param config [Hash] The language configuration
    # @return [Boolean] True if text is a block end marker
    def block_end?(text_str, config)
      return false unless config.control_flow[:block_end]

      text_str == config.control_flow[:block_end].call
    end

    # Handles block end by decreasing indent and returning empty string
    # @return [String] Empty string
    def handle_block_end
      decrease_indent
      "\n"
    end
  end
end
