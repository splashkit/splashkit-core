module TestConfig
  def self.setup
    config = TestRunnerConfig.new

    # Sequential test groups
    config.mark_as_sequential('audio')
    config.mark_as_sequential('animations')
    config.mark_as_skip('networking')
    config.mark_as_sequential('windows')
    config.mark_as_sequential('utilities')
    config.mark_as_sequential('camera')
    config.mark_as_sequential('graphics')
    config.mark_as_sequential('geometry')
    config.mark_as_sequential('sprites')
    config.mark_as_sequential('physics')
    config.mark_as_sequential('resource_bundles')
    config.mark_as_sequential('resources')
    config.mark_as_sequential('timers')
    config.mark_as_sequential('json')

    # Manual test groups
    config.mark_as_sequential('input')
    config.mark_as_sequential('interface')
    config.mark_as_sequential('terminal')
    config.mark_as_sequential('logging')
    config.mark_as_manual('input')
    config.mark_as_manual('interface')
    config.mark_as_manual('terminal')
    config.mark_as_manual('logging')

    @runners = {
      cpp: CppTestRunner.new(config),
      python: PythonTestRunner.new(config),
      pascal: PascalTestRunner.new(config),
      rust: RustTestRunner.new(config),
      csharp: CSharpTestRunner.new(config)
    }
  end

  def self.runners
    @runners
  end
end
