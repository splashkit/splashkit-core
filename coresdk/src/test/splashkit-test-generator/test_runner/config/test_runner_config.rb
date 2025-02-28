class TestRunnerConfig
  def initialize
    @manual_tests = []
    @sequential_tests = []
    @skip_tests = []
  end

  def mark_as_manual(test_name)
    @manual_tests << test_name
  end

  def mark_as_sequential(test_name)
    @sequential_tests << test_name
  end

  def mark_as_skip(test_name)
    @skip_tests << test_name
  end

  def is_manual?(test_name)
    @manual_tests.include?(test_name)
  end

  def is_sequential?(test_name)
    @sequential_tests.include?(test_name)
  end

  def should_skip?(test_name)
    @skip_tests.include?(test_name)
  end
end
