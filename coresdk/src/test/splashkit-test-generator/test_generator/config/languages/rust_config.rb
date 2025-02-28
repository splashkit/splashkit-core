module LanguageConfig
  # Configuration class for generating Rust test files
  class RustConfig < BaseConfig
    def initialize
      super(DEFAULT_CONFIG)
    end

    class << self
      private

      def format_string_handler(text_parts, expressions)
        format_str = "\"#{text_parts.join('{}')}{}\""
        format_args = expressions.join(', ')
        "format!(#{format_str}, #{format_args})"
      end
    end

    DEFAULT_CONFIG = {
      identifier_cases: {
        cleanup:    :pascal_case,
        types:      :pascal_case,
        functions:  :snake_case,
        variables:  :snake_case,
        fields:     :snake_case,
        constants:  :pascal_case
      }.freeze,

      var_keyword: 'let',
      var_mut_keyword: 'mut',
      supports_overloading: false,
      statement_terminator: ';',
      file_extension: 'rs',

      imports: [
        'use std::*;',
        'use splashkit_backend::*;',
        'use splashkit_tests::helpers::*;',
        'use ctor::ctor;',
        '#[cfg(test)]'
      ],

      assert_conditions: {
        'equal'                   => ->(v1, v2, precision = nil) { precision ? "assert!((#{v1} - #{v2}).abs() <= #{precision});" : "assert_eq!(#{v1}, #{v2});" },
        'not_equal'               => ->(v1, v2, _)    { "assert_ne!(#{v1}, #{v2});" },
        'greater_than'            => ->(v1, v2, _)    { "assert!(#{v1} > #{v2});" },
        'less_than'               => ->(v1, v2, _)    { "assert!(#{v1} < #{v2});" },
        'null'                    => ->(v1, _, _)     { "assert!(#{v1}.is_null());" },
        'not_null'                => ->(v1, _, _)     { "assert!(!#{v1}.is_null());" },
        'range'                   => ->(v1, v2, v3)   { "assert!((#{v2}..=#{v3}).contains(&#{v1}));" },
        'true'                    => ->(v1, _, _)     { "assert!(#{v1});" },
        'false'                   => ->(v1, _, _)     { "assert!(!#{v1});" },
        'greater_than_or_equal'   => ->(v1, v2, _)    { "assert!(#{v1} >= #{v2});" },
        'less_than_or_equal'      => ->(v1, v2, _)    { "assert!(#{v1} <= #{v2});" },
        'throws'                  => ->(v1, _, _)     { "assert!(std::panic::catch_unwind(|| { #{v1} }).is_err());" },
        'not_empty'               => ->(v1, _, _)     { "assert!(!#{v1}.is_empty());" },
        'contains'                => ->(v1, v2, _)    { "assert!(#{v2}.contains(#{v1}));" },
        'empty'                   => ->(v1, _, _)     { "assert!(#{v1}.is_empty());" }
      }.freeze,

      if_conditions: {
        'greater_than' => ->(v1, v2) { "#{v1} > #{v2}" },
        'true'         => ->(v1, _)  { "#{v1} == true" },
        'false'        => ->(v1, _)  { "#{v1} == false" },
        'equal'        => ->(v1, v2) { "#{v1} == #{v2}" },
        'not_equal'    => ->(v1, v2) { "#{v1} != #{v2}" }
      }.freeze,

      numeric_constants: {
        infinity: 'f64::INFINITY',
        negative_infinity: 'f64::NEG_INFINITY',
        max_value: 'f32::MAX'
      }.freeze,

      control_flow: {
        loop:      ->(iterations) { "for _ in 0..#{iterations} {" },
        while:     ->(condition) { "while #{condition} {" },
        if:        ->(condition) { "if #{condition} {" },
        else:      -> { 'else {' },
        break:     -> { 'break;' },
        end:       -> { '}' },
        new_line: "'\'"
      }.freeze,

      string_handlers: {
        char:          ->(value) { "'#{value}'" },
        string_ref:    ->(value) { "#{value}.clone()" },
        format_string: method(:format_string_handler),
        string: ->(value) { "\"#{value}\".to_string()" }
      }.freeze,

      type_mapping:   {
        'double' => 'f64',
        'json'   => 'Json',
        'line'   => 'Line'
      }.freeze,

      literal_cast: {
        unsigned_int: ->(value) { "#{value} as u32" },
        float: ->(value) { "#{value} as f32" },
        double: ->(value) { "#{value} as f64" },
      }.freeze,

      comparison_cast: {
        unsigned_int: ->(value) { "#{value} as u32" },
        float: ->(value) { "#{value} as f32" },
        double: ->(value) { "#{value} as f64" }
      }.freeze,

      variable_handlers: {
        array_size: ->(arr) { "#{arr}.len()" },
        reference_operator: ->(var) { "&mut #{var}" }
      }.freeze,

      function_handlers: {
        test: ->(_, name) { ['#[test]', "fn test_#{name}_integration() {"] }
      }.freeze,

      comment_syntax: {
        single: '//',
        multi_start: '/*',
        multi_end: '*/'
      }.freeze,

      class_wrapper: {
        header: [
          ->(group) { "mod test_#{group} {" },
          'use super::*;'
        ],
        constructor_wrapper: {
          header: ['#[ctor]', 'fn setup()', '{'],
          footer: ['}']
        },
        footer: ['}']
      }.freeze,

      cleanup_handlers: {
        setup: ->(name, type, arg = nil) { "let _#{name} = #{type}Cleanup::new(#{arg});" }
      }.freeze,

      indentation: {
        indent_after: ['{'],
        unindent_before: ['}']
      }.freeze,

      terminal_handlers: {
        message: ->(text) { "println!(\"#{text}\");" }
      }.freeze,

      list_handlers: {
        prefix: ->(_) { 'vec![' },
        suffix: ']',
        separator: ', '
      },

      enum_handlers: {
        separator: '::'
      },

      class_handlers: {
        prefix: ->(name) { "#{name}::new(" },
        suffix: ')',
        separator: ', '
      }.freeze
    }.freeze
  end
end
