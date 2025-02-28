module LanguageConfig
  # Configuration class for generating python test files
  class PythonConfig < BaseConfig
    def initialize
      super(DEFAULT_CONFIG)
    end

    class << self
      private

      def format_string_handler(text_parts, expressions)
        formatted_expressions = expressions.map { |e| "{#{e}}" }
        parts = []
        text_parts.each_with_index do |text, i|
          parts << text
          parts << formatted_expressions[i] if formatted_expressions[i]
        end
        "f\"#{parts.join}\""
      end
    end

    DEFAULT_CONFIG = {
      var_keyword: '',
      supports_overloading: false,
      statement_terminator: '',
      file_extension: 'py',

      imports: [
        'import sys',
        'import os',
        'sys.path.append(os.path.join(os.path.dirname(__file__), "../../../data/language_files/python"))',
        'from splashkit_test import *',
        'import pytest',
        'from helpers import *',
        'import contextlib'
      ],

      identifier_cases: {
        cleanup:    :snake_case,
        types:      :pascal_case,
        functions:  :snake_case,
        variables:  :snake_case,
        fields:     :snake_case,
        constants:  :snake_case
      }.freeze,

      assert_conditions: {
        'equal'                   => ->(v1, v2, precision = nil) { precision ? "assert abs(#{v1} - #{v2}) <= #{precision}" : "assert #{v1} == #{v2}" },
        'not_equal'               => ->(v1, v2, _)    { "assert #{v1} != #{v2}" },
        'greater_than'            => ->(v1, v2, _)    { "assert #{v1} > #{v2}" },
        'less_than'               => ->(v1, v2, _)    { "assert #{v1} < #{v2}" },
        'null'                    => ->(v1, _, _)     { "assert #{v1} is None" },
        'not_null'                => ->(v1, _, _)     { "assert #{v1} is not None" },
        'range'                   => ->(v1, v2, v3)   { "assert #{v2} <= #{v1} <= #{v3}" },
        'true'                    => ->(v1, _, _)     { "assert #{v1}" },
        'false'                   => ->(v1, _, _)     { "assert not #{v1}" },
        'greater_than_or_equal'   => ->(v1, v2, _)    { "assert #{v1} >= #{v2}" },
        'less_than_or_equal'      => ->(v1, v2, _)    { "assert #{v1} <= #{v2}" },
        'throws'                  => ->(v1, _, _)     { "with pytest.raises(Exception):    #{v1}" },
        'not_empty'               => ->(v1, _, _)     { "assert len(#{v1}) > 0" },
        'contains'                => ->(v1, v2, _)    { "assert #{v1} in #{v2}" },
        'empty'                   => ->(v1, _, _)     { "assert len(#{v1}) == 0" }
      }.freeze,

      if_conditions: {
        'greater_than' => ->(v1, v2) { "#{v1} > #{v2}" },
        'true'         => ->(v1, _)  { "#{v1} is True" },
        'false'        => ->(v1, _)  { "#{v1} is False" },
        'equal'        => ->(v1, v2) { "#{v1} == #{v2}" },
        'not_equal'    => ->(v1, v2) { "#{v1} != #{v2}" }
      }.freeze,

      numeric_constants: {
        infinity: "float('inf')",
        negative_infinity: "float('-inf')",
        max_value: '3.4028235e+38'
      }.freeze,

      control_flow: {
        loop:      ->(iterations) { "for _ in range(#{iterations}):" },
        while:     ->(condition) { "while #{condition}:" },
        if:        ->(condition) { "if #{condition}:" },
        else:      -> { 'else:' },
        break:     -> { 'break' },
        new_line: "'\'",
        end:       -> { "python_end_block" },
        block_end: -> { "python_end_block" }
      }.freeze,

      string_handlers: {
        char:          ->(value) { "'#{value}'" },
        string_ref: ->(value) { value },
        format_string: method(:format_string_handler),
        string: ->(value) { "\"#{value}\"" }
      }.freeze,

      type_mapping: {
        'string' => 'str',
        'json' => 'Json',
        'line' => 'Line'
      }.freeze,

      boolean_mapping: {
        true => 'True',
        false => 'False'
      }.freeze,

      variable_handlers: {
        array_size: ->(arr) { "len(#{arr})" }
      }.freeze,

      function_handlers: {
        test: ->(_, name) { ["def test_#{name}_integration(self):"] }
      }.freeze,

      comment_syntax: {
        single: '#',
        multi_start: "'''",
        multi_end: "'''",
      }.freeze,

      class_wrapper: {
        header: [->(group) { "class Test#{group}:" }],
        constructor_wrapper: {
          header: ['def setup_method(self):'],
          footer: ['']
        },
        footer: []
      }.freeze,

      cleanup_handlers: {
        setup: ->(_, type, args = nil) { "with #{type}_cleanup(#{args}):" }
      }.freeze,

      indentation: {
        indent_after: [':'],
        unindent_before: ['finally:', 'except:', 'else:', 'elif:'],
        reset_on: {
          'def' => 1
        }
      }.freeze,

      terminal_handlers: {
        message: ->(text) { "print(\"#{text}\", end=\"\")" }
      }.freeze,

      array_handlers: {
        matrix_separator: ','
      }
    }.freeze
  end
end
