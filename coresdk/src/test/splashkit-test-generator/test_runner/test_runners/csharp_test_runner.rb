require_relative 'base_test_runner'

class CSharpTestRunner < BaseTestRunner
  def run_sequential_group(group)
    group_name = group.to_pascal_case
    run_in_dir('csharp', "dotnet test --nologo --filter \"FullyQualifiedName~SplashKitTests.Test#{group_name}\" --logger \"console;verbosity=detailed\"")
  end

  def run_parallel_group(group)
    group_name = group.to_pascal_case
    run_in_dir('csharp', "dotnet test --nologo --filter \"FullyQualifiedName~SplashKitTests.Test#{group_name}\" --logger \"console;verbosity=detailed\"")
  end

  def run_specific_test(group, test_method)
    group_name = group.to_pascal_case
    run_in_dir('csharp', "dotnet test --nologo --filter \"FullyQualifiedName~SplashKitTests.Test#{group_name}.#{test_method}\" --logger \"console;verbosity=detailed\"")
  end

  def get_test_method_name(test_name)
    "Test#{test_name.to_pascal_case}Integration"
  end
end
