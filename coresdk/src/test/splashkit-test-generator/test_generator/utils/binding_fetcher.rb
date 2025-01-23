module TestGenerator
  # Handles the generation and updating of language-specific test bindings
  class BindingFetcher
    # Processes binding files for all supported languages
    # @return [void]
    def self.process_files
      process_python_files
      process_rust_files
      process_csharp_files
      process_pascal_files
    end

    private

    # Generates Python-specific test bindings with updated library paths
    # @return [void]
    def self.process_python_files
      generate_language_bindings('python', 'splashkit.py', 'splashkit_test.py') do |content|
        new_lib_path = LibProcessor.test_library_path
        content.gsub(/search_paths = \[.*?\]/m) do |match|
          "search_paths = [\"#{new_lib_path.gsub('\\', '/').strip}\"]\n"
        end
      end
    end

    # Copies Rust bindings
    # @return [void]
    def self.process_rust_files
      generate_language_bindings('rust', 'splashkit.rs', 'src/lib.rs')
    end

    # Generates C#-specific test bindings with updated library paths
    # @return [void]
    def self.process_csharp_files
      generate_language_bindings('csharp', 'splashkit.cs', 'splashkit_test.cs') do |content|
        content.gsub!(/\[DllImport\("SplashKit",/, '[DllImport("SplashKitBackend",')
      end
    end

    # Generates Pascal-specific test bindings with updated library paths
    # @return [void]
    def self.process_pascal_files
      generate_language_bindings('pascal', 'splashkit.pas', 'splashkit_test.pas') do |content|
        content.gsub!(/unit\s+SplashKit;/i, 'unit splashkit_test;')
      end
    end

    # Generic method to generate language-specific bindings
    # @param language [String] Target programming language
    # @param source_filename [String] Name of the source binding file
    # @param dest_filename [String] Name of the destination test binding file
    # @yield [String] Optional block for content modification
    # @return [void]
    def self.generate_language_bindings(language, source_filename, dest_filename)
      paths = setup_paths(language, source_filename, dest_filename)
      return unless paths[:source_exists]
      
      return if bindings_up_to_date?(paths, language)
      
      generate_binding_file(paths, language) do |content|
        block_given? ? yield(content) : content
      end
    end

    # Sets up source and destination paths for binding generation
    # @param language [String] Target programming language
    # @param source_filename [String] Name of the source binding file
    # @param dest_filename [String] Name of the destination test binding file
    # @return [Hash] Paths and existence information
    def self.setup_paths(language, source_filename, dest_filename)
      source_dir = LibProcessor.source_dir(language)
      source_file = File.join(source_dir, source_filename)
      dest_dir = LibProcessor.dest_dir(language)
      dest_path = File.join(dest_dir, dest_filename)
      
      FileUtils.mkdir_p(File.dirname(dest_path))
      
      {
        source: source_file,
        dest: dest_path,
        source_exists: File.exist?(source_file)
      }
    end

    # Checks if existing bindings are up to date
    # @param paths [Hash] Source and destination path information
    # @param language [String] Target programming language
    # @return [Boolean] true if bindings are current
    def self.bindings_up_to_date?(paths, language)
      if timestamps_current?(paths[:dest], paths[:source])
        MessageHandler.log_info("Test #{language} bindings are up to date at #{paths[:dest]}")
        true
      else
        false
      end
    end

    # Generates the actual binding file with optional content modification
    # @param paths [Hash] Source and destination path information
    # @param language [String] Target programming language
    # @yield [String] Block for content modification
    # @return [void]
    def self.generate_binding_file(paths, language)
      content = File.read(paths[:source])
      content = yield(content)
      File.write(paths[:dest], content)
      MessageHandler.log_info("Created test #{language} bindings at #{paths[:dest]}")
    end

    # Checks if destination file is newer than source file
    # @param dest_file [String] Path to destination file
    # @param source_file [String] Path to source file
    # @return [Boolean] true if destination is current
    def self.timestamps_current?(dest_file, source_file)
      dest_time = File.mtime(dest_file)
      [source_file, __FILE__ ].all? do |file|
        dest_time >= File.mtime(file)
      end
    end
  end
end