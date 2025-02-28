# Core Ruby libraries
require 'json'
require 'fileutils'

# Configuration
require_relative 'config/language_config'

# Core data models
require_relative 'models/function'
require_relative 'models/parameter'

# Service handlers for messages and class wrapping
require_relative 'services/handlers/class_wrapper_handler'
require_relative 'services/handlers/constructor_handler'
require_relative 'services/handlers/tear_down_handler'

# Code and value formatting services
require_relative 'services/formatters/code_formatter'
require_relative 'services/formatters/value_formatter'

# Test writing services
require_relative 'services/writers/step_writer'
require_relative 'services/writers/test_case'
require_relative 'services/writers/test_writer'

# Test loading services
require_relative 'services/loaders/test_loader'

# Configuration validation
require_relative 'validators/config_validator'
require_relative 'validators/source_validator'

# Utility classes
require_relative 'utils/function_lookup'
require_relative 'utils/parser'
require_relative 'utils/pascal_variable_collector'
require_relative 'utils/cmake_builder'
require_relative 'utils/binding_fetcher'

# Custom error definitions
require_relative 'errors/test_generator_errors'
