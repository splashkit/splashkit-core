module TestRunner
  class TestRunnerError < StandardError; end
  class ConfigurationError < TestRunnerError; end
  class ExecutionError < TestRunnerError; end
  class LanguageError < TestRunnerError; end
end 