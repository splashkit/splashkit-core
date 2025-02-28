require_relative 'base_test_runner'

class CppTestRunner < BaseTestRunner
  def run_sequential_group(group)
    test_files = "test_main.cpp tests/#{group}_tests.cpp"
    cmd = "#{compile_command(test_files)} -l Catch2 -o test && ./test -r console -d yes"
    run_in_dir('cpp', cmd)
  end

  def run_parallel_group(group)
    test_files = "test_main.cpp tests/#{group}_tests.cpp"
    cmd = "#{compile_command(test_files)} -l Catch2 -o test && ./test -r console -d yes"
    run_in_dir('cpp', cmd)
  end

  def run_specific_test(group, test_method)
    test_files = "test_main.cpp tests/#{group}_tests.cpp"
    cmd = "#{compile_command(test_files)} -l Catch2 -o test && ./test \"#{test_method}\" -r console -d yes"
    run_in_dir('cpp', cmd)
  end

  def get_test_method_name(test_name)
    "test_#{test_name}_integration"
  end

  private

  def compile_command(test_files)
    base_cmd = "g++"
    lib_dir = LibProcessor.test_library_dir
    case RbConfig::CONFIG['host_os']
    when /mswin|mingw|windows/i
      "#{base_cmd} #{test_files} -L#{lib_dir} -lSplashKitBackend"
    when /darwin|mac os/i
      "#{base_cmd} #{test_files} -L#{lib_dir} -lSplashKitBackend -rpath @loader_path"
    else 
      "#{base_cmd} #{test_files} -L#{lib_dir} -Wl,-rpath=\\$ORIGIN -lSplashKitBackend"
    end
  end
end