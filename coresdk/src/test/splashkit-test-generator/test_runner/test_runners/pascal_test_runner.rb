require_relative 'base_test_runner'

class PascalTestRunner < BaseTestRunner
  def run_sequential_group(group)
    group_name = group.to_pascal_case
    run_in_dir('pascal', "#{compile_command(group_name)} && ./test_main --group=#{group_name}")
  end

  def run_parallel_group(group)
    group_name = group.to_pascal_case
    output_name = "test_main_#{Process.pid}"
    run_in_dir('pascal', "#{compile_command(group_name, output_name)} && ./#{output_name} --group=#{group_name}")
  end

  def run_specific_test(group, test_method)
    group_name = group.to_pascal_case
    run_in_dir('pascal', "#{compile_command(group_name)} && ./test_main --group=#{group_name} --test=#{test_method}")
  end

  private

  def get_test_method_name(test_name)
    "Test#{test_name.to_pascal_case}Integration"
  end

  def compile_command(group_name, output_name = 'test_main')
    lib_dir = LibProcessor.test_library_dir
    base_cmd = case RbConfig::CONFIG['host_os']
    when /mswin|mingw|windows/i
      "fpc -S2 -Sh -Cg -dTEST_#{group_name.upcase} -Fu'.' -Fu'tests' -k\"-L#{lib_dir}\" -k\"-lSplashKitBackend.dll\""
    when /darwin|mac os/i
      "ppcx64 -Tdarwin -S2 -Sh -XR/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -WM10.11 -Cg -dTEST_#{group_name.upcase} -Fu'.' -Fu'tests' " \
      "-k\"-L#{lib_dir}\" -k\"-lSplashKitBackend\" -k\"-rpath @loader_path -rpath #{lib_dir}\""
    else # Linux
      "ppcx64 -S2 -Sh -Cg -dTEST_#{group_name.upcase} -Fu'.' -Fu'tests' -k\"-L#{lib_dir}\" -k\"-lSplashKitBackend\" " \
      "-k\"-rpath=\\$ORIGIN -rpath='#{lib_dir}'\""
    end
    "#{base_cmd} test_main.pas -o#{output_name}"
  end
end