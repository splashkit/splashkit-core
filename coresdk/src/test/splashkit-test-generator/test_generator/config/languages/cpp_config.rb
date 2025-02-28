module LanguageConfig
  # Configuration class for generating Cpp test files
  class CppConfig < BaseConfig
    def initialize
      super(DEFAULT_CONFIG)
    end

    class << self
      private

      def format_string_handler(text_parts, expressions)
        combined_parts = text_parts.zip(expressions).flatten.compact
        formatted_parts = combined_parts.each_with_index.map do |part, index|
          if index.odd?
            "to_string_custom(#{part})"
          else
            "\"#{part}\""
          end
        end
        formatted_parts.join(' + ')
      end
    end

    DEFAULT_CONFIG = {
      supports_overloading: true,
      statement_terminator: ';',
      var_keyword: 'auto',
      string_keyword: 'std::string',
      file_extension: 'cpp',

      imports: [
        '#include <catch2/catch_all.hpp>',
        '#include <iostream>',
        '#include <limits>',
        '#include "../helpers.hpp"'
      ],

      identifier_cases: {
        cleanup:    :snake_case,
        types:      :snake_case,
        functions:  :snake_case,
        variables:  :snake_case,
        fields:     :snake_case,
        constants:  :upper_case
      }.freeze,

      assert_conditions: {
        'equal'                   => ->(v1, v2, precision = nil) { precision ? "REQUIRE(abs(#{v1} - #{v2}) <= #{precision});" : "REQUIRE(#{v1} == #{v2});" },
        'not_equal'               => ->(v1, v2, _)    { "REQUIRE(#{v1} != #{v2});" },
        'greater_than'            => ->(v1, v2, _)    { "REQUIRE(#{v1} > #{v2});" },
        'less_than'               => ->(v1, v2, _)    { "REQUIRE(#{v1} < #{v2});" },
        'null'                    => ->(v1, _, _)     { "REQUIRE(#{v1} == nullptr);" },
        'not_null'                => ->(v1, _, _)     { "REQUIRE(#{v1} != nullptr);" },
        'range'                   => ->(v1, v2, v3)   { "REQUIRE((#{v1} >= #{v2})); REQUIRE((#{v1} <= #{v3}));" },
        'true'                    => ->(v1, _, _)     { "REQUIRE(#{v1});" },
        'false'                   => ->(v1, _, _)     { "REQUIRE_FALSE(#{v1});" },
        'greater_than_or_equal'   => ->(v1, v2, _)    { "REQUIRE(#{v1} >= #{v2});" },
        'less_than_or_equal'      => ->(v1, v2, _)    { "REQUIRE(#{v1} <= #{v2});" },
        'throws'                  => ->(v1, _, _)     { "REQUIRE_THROWS_AS(#{v1}, exception);" },
        'not_empty'               => ->(v1, _, _)     { "REQUIRE(!#{v1}.empty());" },
        'contains'                => ->(v1, v2, _)    { "REQUIRE(#{v2}.find(#{v1}) != string::npos);" },
        'empty'                   => ->(v1, _, _)     { "REQUIRE(#{v1}.empty());" }
      }.freeze,

      if_conditions: {
        'greater_than' => ->(v1, v2) { "#{v1} > #{v2}" },
        'true'         => ->(v1, _)  { "#{v1} == true" },
        'false'        => ->(v1, _)  { "#{v1} == false" },
        'equal'        => ->(v1, v2) { "#{v1} == #{v2}" },
        'not_equal'    => ->(v1, v2) { "#{v1} != #{v2}" }
      }.freeze,

      numeric_constants: {
        infinity: 'std::numeric_limits<double>::infinity()',
        negative_infinity: '-std::numeric_limits<double>::infinity()',
        max_value: 'std::numeric_limits<float>::max()'
      }.freeze,

      control_flow: {
        loop:      ->(iterations) { "for (int i = 0; i < #{iterations}; ++i) {" },
        while:     ->(condition) { "while (#{condition}) {" },
        if:        ->(condition) { "if (#{condition}) {" },
        else:      -> { 'else {' },
        break:     -> { 'break;' },
        end:       -> { '}' },
        new_line: 'endl'
      }.freeze,

      string_handlers: {
        string: ->(value) { "\"#{value}\"" },
        char: ->(value) { "'#{value}'" },
        string_ref: ->(value) { value },
        format_string: method(:format_string_handler)
      }.freeze,

      literal_cast: {
        unsigned_int: ->(value) { "#{value}u" },
        float: ->(value) { "#{value}f" },
        double: ->(value) { "#{value}d" },
      }.freeze,

      variable_handlers: {
        array_size: ->(arr) { "#{arr}.size()" },
      }.freeze,

      function_handlers: {
        test: ->(group, name) { ["TEST_CASE_METHOD(Test#{group}Fixture, \"test_#{name}_integration\") {"] }
      }.freeze,

      comment_syntax: {
        single: '//',
        multi_start: '/*',
        multi_end: '*/',
      }.freeze,

      class_wrapper: {
        header: [->(group) { "struct Test#{group}Fixture" }, '{'],
        constructor_wrapper: {
          header: ->(group) { ["Test#{group}Fixture()", '{'] },
          footer: ['}']
        },
        footer: ['};']
      }.freeze,

      cleanup_handlers: {
        setup: ->(name, type, arg = nil) { "#{type}_cleanup #{name}#{arg.empty? ? '' : "(#{arg})" };" }
      }.freeze,

      indentation: {
        indent_after: ['{', 'public:', 'private:'],
        unindent_before: ['};', '};', '}', 'public:', 'private:']
      }.freeze,

      terminal_handlers: {
        message: ->(text) { "std::cout << \"#{text}\" << std::endl;" }
      }.freeze,

      list_handlers: {
        prefix: ->(type) { "vector<#{type}> {" },
        suffix: '}',
        separator: ', '
      },

      enum_handlers: {
        separator: '::'
      }
    }.freeze
  end
end
