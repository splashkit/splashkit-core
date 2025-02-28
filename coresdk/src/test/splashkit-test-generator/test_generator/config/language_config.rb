Dir[File.join(__dir__, 'languages', '*_config.rb')].sort.each { |file| require file }
module TestGenerator
  # Manages configuration for different programming language test generators
  class LanguageConfig
    # List of supported languages
    SUPPORTED_LANGUAGES = %i[python cpp rust csharp pascal].freeze

    attr_reader :language,
                :statement_terminator,
                :file_extension,
                :indent_size,
                :imports,
                :variable_handlers,
                :function_handlers,
                :assert_conditions,
                :if_conditions,
                :control_flow,
                :string_handlers,
                :supports_overloading,
                :class_wrapper_handler,
                :tear_down_handler,
                :constructor_handler,
                :numeric_constants,
                :terminal_handlers,
                :comment_syntax,
                :indentation,
                :literal_cast,
                :comparison_cast,
                :test_main_file,
                :boolean_mapping,
                :type_mapping,
                :class_wrapper,
                :tear_down,
                :cleanup_handlers

    def initialize(config)
      ConfigValidator.validate!(config)
      @config_instance = config.delete(:config_instance)
      @language = config[:language]
      @indent_size = config[:indent_size]
      @file_extension = config[:file_extension]
      @imports = config[:imports]
      @variable_handlers = config[:variable_handlers]
      @class_wrapper = config[:class_wrapper]
      @tear_down = config[:tear_down]
      @cleanup_handlers = config[:cleanup_handlers]
      @assert_conditions = config[:assert_conditions]
      @if_conditions = config[:if_conditions]
      @control_flow = config[:control_flow]
      @string_handlers = config[:string_handlers]
      @supports_overloading = config[:supports_overloading]
      @numeric_constants = config[:numeric_constants]
      @terminal_handlers = config[:terminal_handlers]
      @comment_syntax = config[:comment_syntax]
      @indentation = config[:indentation]
      @literal_cast = config[:literal_cast]
      @comparison_cast = config[:comparison_cast]
      @test_main_file = config[:test_main_file]
      @statement_terminator = config[:statement_terminator]
      @boolean_mapping = config[:boolean_mapping]
      @type_mapping = config[:type_mapping]
      @class_wrapper_handler = ClassWrapperHandler.new(self)
      @constructor_handler = ConstructorHandler.new(self)
      @tear_down_handler = TearDownHandler.new(self)
    end

    # Creates a configuration instance for a specific language
    # @param language [Symbol] The programming language to configure
    # @return [LanguageConfig] The configuration instance
    # @raise [StandardError] If language is unsupported or configuration is missing
    def self.for_language(language)
      raise LanguageError, "Unsupported language: #{language}" unless SUPPORTED_LANGUAGES.include?(language)

      begin
        config_class = Object.const_get("LanguageConfig::#{language.to_s.capitalize}Config")
        config_instance = config_class.new
        config = config_instance.get
        config[:language] = language
        config[:config_instance] = config_instance
        new(config)
      rescue NameError
        raise ConfigurationError, "Configuration not found for language: #{language}"
      rescue StandardError => e
        raise TestGeneratorError, "Error loading configuration: #{e.message}"
      end
    end

    # Handles method calls that are not directly defined in the LanguageConfig class
    # Delegates undefined methods to the underlying configuration instance if possible
    # @param method_name [Symbol] The name of the method being called
    # @param args [Array] Arguments passed to the method
    # @param block [Proc] Optional block passed to the method
    # @return [Object] Result of the method call on the config instance
    # @raise [NoMethodError] If the method is not found on the config instance
    def method_missing(method_name, *args, &block)
      if @config_instance.respond_to?(method_name)
        @config_instance.send(method_name, *args, &block)
      else
        super
      end
    end

    # Checks if a method can be handled by the underlying configuration instance
    # Extends the default respond_to? behavior to include methods from the config instance
    # @param method_name [Symbol] The name of the method to check
    # @param include_private [Boolean] Whether to include private methods in the check
    # @return [Boolean] True if the method exists on the config instance or the parent class
    def respond_to_missing?(method_name, include_private = false)
      @config_instance.respond_to?(method_name) || super
    end
  end
end
