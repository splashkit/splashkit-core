class String
  #
  # Converts from snake_case to camelCase
  #
  def to_camel_case
    human_case = to_human_words
    human_case[0] = human_case[0].downcase
    human_case.join('')
  end

  #
  # Converts from snake_case to PascalCase
  #
  def to_pascal_case
    to_human_case.tr(' ', '')
  end

  #
  # Converts from snake_case to humanised words
  #
  def to_human_words
    gsub(/_([0-9])([a-zA-Z])/) { |match| "_#{$1}_#{$2}" }.split('_').map(&:capitalize).map do |input|
      input.gsub(/^(Rgb|Hsb|Css|Ip|Tcp|Udp|Uri|Rgba)$/){ |match| "#{match.to_upper_case}" } #Dont do Html or Http
    end
  end

  #
  # Converts from snake_case to Humanised Case
  #
  def to_human_case
    to_human_words.join(' ')
  end

  #
  # Converts from snake_case to snake_case (all lower)
  #
  def to_snake_case
    downcase
  end

  #
  # Converts to UPPER_CASE (snake but uppercase)
  #
  def to_upper_case
    upcase
  end


  #
  # Converts from snake_case to kebab-case
  #
  def to_kebab_case
    to_human_case.downcase.tr(' ', '-')
  end
end
