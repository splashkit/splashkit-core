module LanguageConfig
  # Configuration class for generating Pascal test files
  class PascalConfig < BaseConfig
    def initialize
      super(DEFAULT_CONFIG)
    end

    class << self
      private

      def format_string_handler(text_parts, expressions)
        parts = []
        text_parts.each_with_index do |text, i|
          parts << "'#{text}'"
          parts << "ToStr(#{expressions[i]})" if expressions[i]
        end
        parts.join(' + ')
      end
    end

    DEFAULT_CONFIG = {
      var_keyword: '',
      assignment_operator: ':=',
      supports_overloading: true,
      statement_terminator: ';',
      file_extension: 'pas',

      imports: [
        ->(group) { "unit #{group}_tests;" },
        'interface',
        'uses splashkit_test, fpcunit, testutils, testregistry, Helpers, Math;',
        'procedure RegisterTests;'
      ],

      identifier_cases: {
        cleanup:    :pascal_case,
        types:      :pascal_case,
        functions:  :pascal_case,
        variables:  :camel_case,
        fields:     :camel_case,
        constants:  :upper_case
      }.freeze,

      assert_conditions: {
        'equal'                   => ->(v1, v2, precision = nil) { precision ? "AssertTrue(Abs(#{v1} - #{v2}) <= #{precision});" : "AssertTrue(#{v1} = #{v2});" },
        'not_equal'               => ->(v1, v2, _)    { "AssertTrue(#{v1} <> #{v2});" },
        'greater_than'            => ->(v1, v2, _)    { "AssertTrue(#{v1} > #{v2});" },
        'less_than'               => ->(v1, v2, _)    { "AssertTrue(#{v1} < #{v2});" },
        'null'                    => ->(v1, _, _)     { "AssertNull(#{v1});" },
        'not_null'                => ->(v1, _, _)     { "AssertNotNull(#{v1});" },
        'range'                   => ->(v1, v2, v3)   { "AssertTrue((#{v1} >= #{v2}) and (#{v1} <= #{v3}));" },
        'true'                    => ->(v1, _, _)     { "AssertTrue(#{v1});" },
        'false'                   => ->(v1, _, _)     { "AssertFalse(#{v1});" },
        'greater_than_or_equal'   => ->(v1, v2, _)    { "AssertTrue(#{v1} >= #{v2});" },
        'less_than_or_equal'      => ->(v1, v2, _)    { "AssertTrue(#{v1} <= #{v2});" },
        'throws'                  => ->(v1, _, _)     { "try#{v1}exceptend;" },
        'not_empty'               => ->(v1, _, _)     { "AssertTrue(Length(#{v1}) > 0);" },
        'contains'                => ->(v1, v2, _)    { "AssertTrue(Pos(#{v1}, #{v2}) > 0);" },
        'empty'                   => ->(v1, _, _)     { "AssertTrue(Length(#{v1}) = 0);" }
      }.freeze,

      if_conditions: {
        'greater_than' => ->(v1, v2) { "#{v1} > #{v2}" },
        'true'         => ->(v1, _)  { "#{v1} = true" },
        'false'        => ->(v1, _)  { "#{v1} = false" },
        'equal'        => ->(v1, v2) { "#{v1} = #{v2}" },
        'not_equal'    => ->(v1, v2) { "#{v1} <> #{v2}" }
      }.freeze,

      numeric_constants: {
        infinity: 'MaxDouble',
        negative_infinity: '-MaxDouble',
        max_value: 'MaxSingle'
      }.freeze,

      control_flow: {
        loop:      ->(iterations) { "for i := 0 to #{iterations - 1} do begin" },
        while:     ->(condition) { "while #{condition} do begin" },
        if:        ->(condition) { "if #{condition} then begin" },
        else:      -> { 'else begin' },
        break:     -> { 'break;' },
        end:       -> { 'end;' },
        new_line: 'LineEnding'
      }.freeze,

      string_handlers: {
        char: ->(value) { "'#{value}'" },
        string_ref: ->(value) { value.to_camel_case },
        format_string: method(:format_string_handler),
        string: ->(value) { "'#{value}'" }
      }.freeze,

      type_mapping: {
        'double' => 'Double',
        'string' => 'String',
        'json'   => 'Json',
        'line'   => 'Line',
        'float'  => 'Single',
        'bool'   => 'Boolean',
        'int'    => 'Integer',
        'string_ref' => 'String',
        'unsigned int' => 'Cardinal'
      }.freeze,

      boolean_mapping: {
        true => 'True',
        false => 'False'
      }.freeze,

      variable_handlers: {
        array_size: ->(arr) { "Length(#{arr})" }
      }.freeze,

      function_handlers: {
        test: ->(group, name) { ["procedure TTest#{group}.Test#{name}Integration;"] }
      }.freeze,

      comment_syntax: {
        single: '//',
        multi_start: '{',
        multi_end: '}',
      }.freeze,

      class_wrapper: {
        header: [
          'type',
          ->(group) { "TTest#{group} = class(TTestCase)" },
          'private_vars',
          'published',
          'published_functions',
          'end;',
          '',
          'implementation',
          '',
          ->(group) { "{ TTest#{group} }" },
          ''
        ],
        publish: {
          setup: 'procedure Setup; override;',
          tear_down: 'procedure TearDown; override;'
        },
        constructor_wrapper: {
          header: ->(group) { [
            "procedure TTest#{group}.Setup;",
            'begin',
            'inherited;'
          ] },
          footer: ['end;']
        },
        footer: [
          'procedure RegisterTests;',
          'begin',
          ->(group) { "RegisterTest(TTest#{group});" },
          'end;',
          'end.'
        ]
      }.freeze,

      tear_down: {
        header: ->(group) { ["procedure TTest#{group}.TearDown;", 'begin'] },
        footer: ['inherited;', 'end;']
      },

      cleanup_handlers: {
        setup: ->(_, type, arg = nil) { "cleanup#{type} := #{type}Cleanup.Create#{arg ? "(#{arg})" : ''};"},
        free: ->(name) { ["if Assigned(cleanup#{name}) then", "cleanup#{name}.Free;"] }
      }.freeze,

      indentation: {
        indent_after: %w[begin type protected published do private],
        unindent_before: %w[end; end. protected published inherited],
        reset_on: {
          'implementation' => 0
        }
      }.freeze,

      terminal_handlers: {
        message: ->(text) { "Write('#{text}');" }
      }.freeze,

      array_handlers: {
        separator: ', '
      },

      method_handlers: {
        prefix: ->(var, method) { "#{var}.#{method}" },
        suffix: '',
        separator: ', '
      },

      list_handlers: {
        prefix: ->(type) { "Create#{type}Array([" },
        suffix: '])',
        separator: ', '
      },

      class_handlers: {
        prefix: ->(name) { "T#{name}.Create(" },
        suffix: ')',
        separator: ', '
      }.freeze
    }.freeze
  end
end

