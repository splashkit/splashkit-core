class DirectoryManager
  REQUIRED_LANGUAGES = ['rust', 'python', 'cpp', 'clib', 'pascal', 'csharp']
  ROOT_DIR = File.expand_path('../../../../../..', __dir__) # splashkit-core root
  RESOURCES_DIR = File.join(File.expand_path('../../..', __dir__), 'Resources') # test/resources
  LANGUAGE_FILES_DIR = File.join('data', 'language_files') # splashkit-test-generator/data/language_files
  CMAKE_PATH = File.join(LANGUAGE_FILES_DIR, 'cpp') # splashkit-test-generator/data/language_files/cpp
  OUTPUT_DIR = File.join(LANGUAGE_FILES_DIR, 'cpp', 'lib') # splashkit-test-generator/data/language_files/cpp/lib
  TRANSLATOR_DIR = File.join(ROOT_DIR, 'tools', 'translator') # splashkit-core/tools/translator
  GENERATED_DIR = File.join(ROOT_DIR, 'generated') # splashkit-core/generated
  SK_SRC = File.join(ROOT_DIR, 'coresdk', 'src') # splashkit-core/coresdk/src
  SK_EXT = File.join(ROOT_DIR, 'coresdk', 'external') # splashkit-core/coresdk/external

  class << self
    def setup(language)
      new(language).setup
    end

    def source_patterns
      [
        File.join(SK_SRC, 'coresdk', '*.cpp'),
        File.join(SK_SRC, 'backend', '*.cpp'),
        File.join(SK_EXT, 'civetweb', 'src', 'civetweb.c'),
        File.join(SK_EXT, 'sqlite', 'sqlite3.c'),
        File.join(SK_EXT, 'hash-library', '*.cpp'),
        File.join(SK_EXT, 'easyloggingpp', '*.cc'),
        File.join(SK_EXT, 'microui', 'src', '*.c'),
        File.join(GENERATED_DIR, 'clib', '*.cpp')
      ]
    end

    def find_built_library(os_config)
      Dir.glob(File.join(OUTPUT_DIR, os_config[:lib_dir], os_config[:lib_glob])).first
    end

    def lib_absolute_path(os_config, lib_file_name)
      File.absolute_path(File.join(OUTPUT_DIR, os_config[:lib_dir], lib_file_name))
    end

    def lib_dir(os_config)
      File.absolute_path(File.join(OUTPUT_DIR, os_config[:lib_dir]))
    end
    
    def find_all_library_files
      Dir.glob(File.join(OUTPUT_DIR, '**', LibProcessor.os_config[:lib_glob]))
    end

    def find_all_source_files
      source_patterns.flat_map { |pattern| Dir.glob(pattern) }
    end
  end

  def initialize(language)
    @language = language
  end

  def setup
    create_base_directories
    create_language_test_directories
    [@language_dir, @tests_dir]
  end

  private

  def create_base_directories
    create_directory('generated_tests')
    create_directory('resources')
  end

  def create_language_test_directories
    @language_dir = "generated_tests/#{@language}"
    @tests_dir = "#{@language_dir}/tests"
    create_directory(@language_dir)
    create_directory(@tests_dir)
  end

  def create_directory(path)
    FileUtils.mkdir_p(path) unless Dir.exist?(path)
  rescue StandardError => e
    MessageHandler.log_error("Failed to create directory: #{path}", e.message)
    raise TestGeneratorError, "Directory creation failed: #{e.message}"
  end
end
