require 'optparse'

class CliParser
  def self.parse
    options = {}
    parser = OptionParser.new do |opts|
      opts.banner = <<~BANNER
        #{colorize('SplashKit Test Tool', '1;34')}
        #{colorize('==============================', '1;34')}
        #{colorize('Usage:', '94')} #{colorize('ruby main.rb [options]', '1;33')}

        #{colorize('Examples:', '94')}
          #{colorize('ruby main.rb --generate api.json', '32')}                          #{colorize('# Generate tests from API', '90')}
          #{colorize('ruby main.rb --run-tests', '32')}                                  #{colorize('# Run tests that have been set in main.rb', '90')}
          #{colorize('ruby main.rb -l pascal', '32')}                                    #{colorize('# Run all Pascal tests', '90')}
          #{colorize('ruby main.rb -l pascal -g animations', '32')}                      #{colorize('# Run animation tests', '90')}
          #{colorize('ruby main.rb -l pascal -g animations -t animation_count', '32')}   #{colorize('# Run specific test', '90')}

        #{colorize('Available options:', '94')}
      BANNER

      opts.on("--run-tests", 
              "#{colorize('Run tests that have been set in main.rb', '36')}") do |v|
        options[:run_tests] = v
      end

      opts.on("--generate PATH",
              "#{colorize('Generate test files from API JSON', '36')}") do |v|
        options[:generate] = v
      end

      opts.on("-l", "--language LANGUAGE", %w[cpp python pascal rust csharp],
              "#{colorize('Select programming language for tests', '36')}",
              "#{colorize('Supported:', '90')} #{colorize('cpp, python, pascal, rust, csharp', '1;33')}") do |v|
        options[:language] = v.to_sym
      end

      opts.on("-g", "--group GROUP",
              "#{colorize('Specify test group/category to run', '36')}",
              "#{colorize('Example:', '90')} #{colorize('animations, audio, input', '1;33')}",
              "#{colorize('(requires --language to be specified)', '90')}") do |v|
        options[:group] = v
      end

      opts.on("-t", "--test TEST",
              "#{colorize('Run a specific test within a group', '36')}",
              "#{colorize('(requires --group to be specified)', '90')}") do |v|
        options[:test] = v
      end

      opts.on("-h", "--help",
              "#{colorize('Show this help message', '36')}") do
        puts opts
        exit 0
      end
    end

    parser.parse!
    options
  end
end
