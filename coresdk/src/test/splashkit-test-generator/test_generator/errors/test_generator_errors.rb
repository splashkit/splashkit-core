module TestGenerator
  class TestGeneratorError < StandardError; end
  class ConfigurationError < TestGeneratorError; end
  class ValidationError < TestGeneratorError; end
  class LanguageError < TestGeneratorError; end
  class HandlerError < TestGeneratorError; end
end
