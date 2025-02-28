# Represents a parameter in a SplashKit function
class Parameter
  attr_reader :name, :param_type, :description, :is_array, :array_dimension_sizes

  def initialize(name:, param_type:, description: '', is_array: false, array_dimension_sizes: [])
    @name = name
    @param_type = param_type
    @description = description
    @is_array = is_array
    @array_dimension_sizes = array_dimension_sizes
  end
end
