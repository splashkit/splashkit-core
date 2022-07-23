#include "random.h"
#include "matrix_2d.h"

#include <iostream>

using namespace std;

namespace splashkit_lib
{
	matrix_2d matrix_kronecker_product(const matrix_2d &m1, const matrix_2d &m2)
	{
		matrix_2d result(m1.x * m2.x, m1.y * m2.y);

		for (size_t i = 0; i < m1.x; i++)
			for (size_t k = 0; k < m2.x; k++)
				for (size_t j = 0; j < m1.y; j++)
					for (size_t l = 0; l < m2.y; l++)
						result.elements[i * m2.x + k][j * m2.y + l] = m1.elements[i][j] * m2.elements[k][l];

		return result;
	}

	vector<int> to_categorical(const matrix_2d &m)
	{
		vector<int> result(m.x);

		for (size_t i = 0; i < m.x; i++)
			for (size_t j = 0; j < m.y; j++)
				if (m.elements[i][j] == 1)
					result[i] = j;

		return result;
	}

	matrix_2d from_categorical(const vector<int> &v, int max_val)
	{
		matrix_2d result(v.size(), max_val);

		for (size_t i = 0; i < v.size(); i++)
			result.elements[i][v[i]] = 1;

		return result;
	}

	template <typename inT, typename ouT>
	struct Function
	{
		virtual ouT apply(inT input);

		virtual ouT df(inT input);
	};

	class Model
	{
	private:
		matrix_2d input_shape;
		matrix_2d output_shape;
	public:
		Model(const matrix_2d &input_shape, const matrix_2d &output_shape)
		{
			this->input_shape = input_shape;
			this->output_shape = output_shape;
		}

		matrix_2d predict(const matrix_2d &input);
		void train(const matrix_2d &input, const matrix_2d &output);
		void save(const string &filename);
		void load(const string &filename);
	};

	class Layer
	{
	public:
		matrix_2d input_shape;
		matrix_2d output_shape;
	};

	class Dense : public Layer
	{
		matrix_2d weights;
		matrix_2d biases;

		Function<matrix_2d, matrix_2d> activation_function;
		Function<matrix_2d, double> error_function;

		Dense(size_t input_size, size_t output_size, Function<matrix_2d, matrix_2d> activation_function, Function<matrix_2d, double> error_function)
		{
			this->biases = fill_matrix(input_size, 1, 1);
			this->weights = matrix_2d(output_size, 1);

			// initialise weights
			constexpr double max_weight = 1;
			for (double &cell : weights)
			{
				cell = rnd() * max_weight * 2 - max_weight;
			}

			this->activation_function = activation_function;
			this->error_function = error_function;
		}

		matrix_2d forward(const matrix_2d &input)
		{
			matrix_2d net = matrix_multiply(weights, matrix_horizontal_concat(input, biases));
			return activation_function.apply(net);
		}
	};
}