module LanguageConfig
  # Configuration class for generating Csharp test files
  class CsharpConfig < BaseConfig
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
        "$\"#{parts.join}\""
      end
    end

    DEFAULT_CONFIG = {
      var_keyword: 'var',
      supports_overloading: true,
      statement_terminator: ';',
      file_extension: 'cs',

      imports: [
        'using Xunit;',
        'using SplashKitSDK;',
        'using static SplashKitSDK.SplashKit;',
        'using HttpMethod = SplashKitSDK.HttpMethod;'
      ],

      identifier_cases: {
        cleanup:    :pascal_case,
        types:      :pascal_case,
        functions:  :pascal_case,
        variables:  :camel_case,
        fields:     :pascal_case,
        constants:  :pascal_case
      }.freeze,

      assert_conditions: {
        'equal'                   => ->(v1, v2, precision = nil)    { "Assert.Equal(#{v1}, #{v2}#{precision ? ", #{precision}" : ''});" },
        'not_equal'               => ->(v1, v2, _)    { "Assert.NotEqual(#{v1}, #{v2});" },
        'greater_than'            => ->(v1, v2, _)    { "Assert.True(#{v1} > #{v2});" },
        'less_than'               => ->(v1, v2, _)    { "Assert.True(#{v1} < #{v2});" },
        'null'                    => ->(v1, _, _)     { "Assert.Null(#{v1});" },
        'not_null'                => ->(v1, _, _)     { "Assert.NotNull(#{v1});" },
        'range'                   => ->(v1, v2, v3)   { "Assert.InRange(#{v1}, #{v2}, #{v3});" },
        'true'                    => ->(v1, _, _)     { "Assert.True(#{v1});" },
        'false'                   => ->(v1, _, _)     { "Assert.False(#{v1});" },
        'greater_than_or_equal'   => ->(v1, v2, _)    { "Assert.True(#{v1} >= #{v2});" },
        'less_than_or_equal'      => ->(v1, v2, _)    { "Assert.True(#{v1} <= #{v2});" },
        'throws'                  => ->(v1, _, _)     { "Assert.Throws<Exception>(() => { #{v1} });" },
        'not_empty'               => ->(v1, _, _)     { "Assert.NotEmpty(#{v1});" },
        'contains'                => ->(v1, v2, _)    { "Assert.Contains(#{v1}, #{v2});" },
        'empty'                   => ->(v1, _, _)     { "Assert.Empty(#{v1});" }
      }.freeze,

      if_conditions: {
        'greater_than' => ->(v1, v2) { "#{v1} > #{v2}" },
        'true'         => ->(v1, _)  { "#{v1}" },
        'false'        => ->(v1, _)  { "!#{v1}" },
        'equal'        => ->(v1, v2) { "#{v1} == #{v2}" },
        'not_equal'    => ->(v1, v2) { "#{v1} != #{v2}" }
      }.freeze,

      numeric_constants: {
        infinity: 'float.PositiveInfinity',
        negative_infinity: 'float.NegativeInfinity',
        max_value: 'float.MaxValue'
      }.freeze,

      control_flow: {
        loop:      ->(iterations) { "for (int i = 0; i < #{iterations}; i++) {" },
        while:     ->(condition) { "while (#{condition}) {" },
        if:        ->(condition) { "if (#{condition}) {" },
        else:      -> { 'else {' },
        break:     -> { 'break;' },
        end:       -> { '}' },
        new_line: 'Environment.NewLine'
      }.freeze,

      string_handlers: {
        char: ->(value) { "'#{value}'" },
        string_ref: ->(value) { value.to_camel_case },
        format_string: method(:format_string_handler),
        string: ->(value) { "\"#{value}\"" }
      }.freeze,

      type_mapping: {
        'json' => 'Json',
        'line' => 'Line'
      }.freeze,

      literal_cast: {
        unsigned_int: ->(value) { "#{value}u" },
        float: ->(value) { "#{value}f" }
      }.freeze,

      variable_handlers: {
        array_size: ->(arr) { "#{arr}.Count" },
        reference_operator: ->(var) { "ref #{var}" }
      }.freeze,

      array_handlers: {
        matrix_separator: ', '
      },

      function_handlers: {
        test: ->(_, name) { ['[Fact]', "public void Test#{name}Integration() {"] }
      }.freeze,

      comment_syntax: {
        single: '//',
        multi_start: '/*',
        multi_end: '*/'
      }.freeze,

      class_wrapper: {
        header: [
          'namespace SplashKitTests',
          '{',
          ->(group) { "public class Test#{group}" },
          '{'
        ],
        constructor_wrapper: {
          header: ->(group) { ["public Test#{group}()", '{'] },
          footer: ['}']
        },
        footer: [
          '}',
          '}'
        ]
      }.freeze,

      cleanup_handlers: {
        setup: ->(name, type, args = nil) { "using var #{name} = new #{type}Cleanup#{args ? "(#{args})" : '()'};" }
      }.freeze,

      indentation: {
        indent_after: ['{'],
        unindent_before: ['}']
      }.freeze,

      terminal_handlers: {
        message: ->(text) { "Console.WriteLine(\"#{text}\");" }
      }.freeze,

      list_handlers: {
        prefix: ->(type) { "new List<#{type}> {" },
        suffix: '}',
        separator: ', '
      },

      class_handlers: {
        prefix: ->(name) { "new #{name}(" },
        suffix: ')',
        separator: ', '
      }.freeze
    }.freeze
  end
end
