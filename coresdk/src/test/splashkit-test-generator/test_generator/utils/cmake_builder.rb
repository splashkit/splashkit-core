module TestGenerator
  # Handles CMake-based compilation of the C/C++ test library
  class CMakeBuilder
    BUILD_DIR = 'build'

    # Initiates build process if source files or CMake configuration have changed
    # @return [Boolean] true if build succeeds or not needed, false on failure
    def self.build_if_needed
      return unless needs_rebuild?
      
      MessageHandler.log_info("Building C library...")
      build_library
    end

    private

    # Performs the actual build process using CMake and Make
    # @return [Boolean] true if build succeeds, false otherwise
    def self.build_library
      build_path = File.join(DirectoryManager::CMAKE_PATH, BUILD_DIR)
      FileUtils.mkdir_p(build_path)
      run_cmake && run_make
    end

    # Runs CMake to generate build files
    # @return [Boolean] true if CMake configuration succeeds
    def self.run_cmake
      Dir.chdir(DirectoryManager::CMAKE_PATH) do
        return MessageHandler.log_error('CMake configuration failed') unless system('cmake', '-B', BUILD_DIR)
        true
      end
    end

    # Runs Make to compile the library
    # @return [Boolean] true if compilation succeeds
    def self.run_make
      Dir.chdir(File.join(DirectoryManager::CMAKE_PATH, BUILD_DIR)) do
        return MessageHandler.log_error('Make build failed') unless system('make')
        true
      end
    end

    # Determines if rebuilding is necessary based on file modifications
    # @return [Boolean] true if rebuild is needed
    def self.needs_rebuild?
      cmake_file_modified? || source_files_modified?
    end

    # Checks if CMake configuration file has been modified since last build
    # @return [Boolean] true if CMake files are newer than built library
    def self.cmake_file_modified?
      return true unless library_files_exist?
      cmake_path = File.join(DirectoryManager::CMAKE_PATH, 'CMakeLists.txt')
      File.mtime(cmake_path) > newest_library_timestamp
    end

    # Checks if any source files have been modified since last build
    # @return [Boolean] true if any source files are newer than built library
    def self.source_files_modified?
      return true unless library_files_exist?
      source_files.any? { |f| File.mtime(f) > newest_library_timestamp }
    end

    # Verifies existence of built library files
    # @return [Boolean] true if library files exist
    def self.library_files_exist?
      library_files.any?
    end

    # Gets list of all library files in build directory
    # @return [Array<String>] List of library file paths
    def self.library_files
      @library_files ||= DirectoryManager.find_all_library_files
    end

    # Gets list of all source files that need to be compiled
    # @return [Array<String>] List of source file paths
    def self.source_files
      @source_files ||= DirectoryManager.find_all_source_files
    end

    # Gets timestamp of most recently built library file
    # @return [Time, nil] Timestamp of newest library file or nil if none exist
    def self.newest_library_timestamp
      @newest_library_timestamp ||= library_files.map { |f| File.mtime(f) }.max
    end
  end
end