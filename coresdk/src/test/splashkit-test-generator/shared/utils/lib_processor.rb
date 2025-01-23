
# Handles platform-specific test library operations and configurations
class LibProcessor
  # Locates the compiled test library for the current platform
  # @return [String, nil] Path to the test library or nil if not found
  def self.find_test_library
    DirectoryManager.find_built_library(os_config)
  end

  # Generates the platform-specific test library filename
  # @return [String] The formatted library name with appropriate prefix and extension
  def self.test_library_name
    "#{os_config[:lib_prefix]}SplashKitBackend#{os_config[:lib_extension]}"
  end

  # Gets the absolute path to the test library
  # @return [String] Full path to the test library file
  def self.test_library_path
    DirectoryManager.lib_absolute_path(os_config, test_library_name)
  end

  # Gets the directory containing the test library
  # @return [String] Path to the test library directory
  def self.test_library_dir
    DirectoryManager.lib_dir(os_config)
  end

  # Gets the source directory for a specific language's generated files
  # @param language [String] The target programming language
  # @return [String] Path to the source directory
  def self.source_dir(language)
    File.join(DirectoryManager::GENERATED_DIR, language)
  end

  # Gets the destination directory for a specific language's test files
  # @param language [String] The target programming language
  # @return [String] Path to the destination directory
  def self.dest_dir(language)
    File.join(DirectoryManager::LANGUAGE_FILES_DIR, language)
  end

  # Returns platform-specific configuration for library handling
  # @return [Hash] Configuration hash containing platform-specific settings
  def self.os_config
    @os_specific_config ||= case RbConfig::CONFIG['host_os']
      when /mswin|mingw|cygwin/
        {
          platform: :windows,
          lib_extension: '.dll',
          lib_prefix: '',
          lib_dir: 'windows',
          lib_glob: '*.dll'
        }
      when /darwin/
        {
          platform: :macos,
          lib_extension: '.dylib',
          lib_prefix: 'lib',
          lib_dir: 'macos',
          lib_glob: '*.dylib'
        }
      else
        {
          platform: :linux,
          lib_extension: '.so',
          lib_prefix: 'lib',
          lib_dir: 'linux',
          lib_glob: '*.so'
        }
    end
  end
end