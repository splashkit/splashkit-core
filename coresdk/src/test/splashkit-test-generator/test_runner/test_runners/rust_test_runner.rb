require_relative 'base_test_runner'

class RustTestRunner < BaseTestRunner
  def run_sequential_group(group)
    run_in_dir('rust', "cargo test --test #{group}_tests -- --test-threads=1 --nocapture")
  end

  def run_parallel_group(group)
    run_in_dir('rust', "cargo test --test #{group}_tests")
  end

  def run_specific_test(group, test_class, test_method)
    run_in_dir('rust', "cargo test --test #{group}_tests #{test_class}::#{test_method} -- --test-threads=1 --nocapture")
  end

  def get_test_method_name(test_name)
    "test_#{test_name}_integration"
  end
end
