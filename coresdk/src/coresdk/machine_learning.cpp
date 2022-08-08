#include "random.h"
#include "matrix_2d.h"
#include "machine_learning.h"

#include <iostream>
#include <memory>

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

	matrix_2d sq(const matrix_2d &m)
	{
		return matrix_multiply_components(m, m);
	}

	double sum(const matrix_2d &m)
	{
		double result = 0;
		for (size_t i = 0; i < m.x; i++)
			for (size_t j = 0; j < m.y; j++)
				result += m.elements[i][j];
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

	/* #region  ActivationFunctions */
	struct f_ReLu : public _ActivationFunction
	{
		matrix_2d apply(const matrix_2d &input) override
		{
			return input[input > 0];
		}

		matrix_2d derivative(const matrix_2d &input) override
		{
			return input > 0;
		}
	};

	shared_ptr<_ActivationFunction> get_activation_function(ActivationFunction name)
	{
		switch (name)
		{
		case ActivationFunction::ReLu:
			return shared_ptr<_ActivationFunction>(new f_ReLu());
		default:
			throw logic_error("Unknown activation function");
		}
	}
	/* #endregion */

	/* #region  ErrorFunctions */
	class f_RSS : public _ErrorFunction
	{
		double apply(const matrix_2d &output, const matrix_2d &target_output) override
		{
			return sum(sq(target_output - output));
		}
	};

	shared_ptr<_ErrorFunction> get_error_function(ErrorFunction name)
	{
		switch (name)
		{
		case ErrorFunction::RSS:
			return shared_ptr<_ErrorFunction>(new f_RSS());
		default:
			throw logic_error("Unknown error function");
		}
	}
	/* #endregion */

	/* #region  Model */
	void Model::forward(const matrix_2d &input)
	{
		vector<matrix_2d> outputs(layers.size() + 1);
		outputs[0] = input;
		for (size_t i = 0; i < layers.size(); i++)
		{
			outputs[i + 1] = layers[i].forward(outputs[i]);
		}
	}

	Model::Model(ErrorFunction error_function)
	{
		this->error_function = get_error_function(error_function);
	}

	void Model::add_layer(Layer layer)
	{
		layers.push_back(layer);
	}

	matrix_2d Model::predict(const matrix_2d &input)
	{
		matrix_2d result = input;
		for (Layer &layer : layers)
		{
			result = layer.forward(result);
		}
		return result;
	}

	void Model::train(const matrix_2d &input, const matrix_2d &target_output)
	{
		while (true)
		{
			/* #region Forward Propagation */
			vector<matrix_2d> outputs(layers.size() + 1);
			outputs[0] = input;
			for (size_t i = 0; i < layers.size(); i++)
			{
				outputs[i + 1] = layers[i].forward(outputs[i]);
			}
			/* #endregion */

			matrix_2d difference = target_output - outputs[layers.size()];
			// matrix_2d delta = matrix_multiply_components(difference, activation_diff(net)); // sensitivity

		}
	}

	void Model::save(const string &filename)
	{
		// Write weights and biases to file
	}

	void Model::load(const string &filename)
	{
		// Read weights and biases from a file
	}
	/* #endregion Model */

	/* #region Dense */
	Dense::Dense(size_t input_size, size_t output_size, ActivationFunction activation_function)
	{
		this->biases = fill_matrix(1, output_size, 0);
		this->weights = matrix_2d(input_size, output_size);

		// initialise weights
		constexpr double max_weight = 1;
		for (double &cell : weights)
		{
			cell = rnd() * max_weight * 2 - max_weight;
		}

		this->activation_function = get_activation_function(activation_function);
	}

	matrix_2d Dense::forward(const matrix_2d &input)
	{
		matrix_2d net = matrix_multiply(input, weights) + biases;
		return activation_function->apply(net);
	}

	matrix_2d Dense::backward(const matrix_2d &input)
	{
		return weights;
	}

	void Dense::compute_error(const matrix_2d &input, const matrix_2d &output, const matrix_2d &target_output)
	{
		matrix_2d error = sum(sq(target_output - output)); // Residual sum of squares, RSS

		vector<int> target_classes = to_categorical(target_output);
		vector<int> classes = to_categorical(output);

		double class_error = 0;
		for (size_t i = 0; i < target_classes.size(); i++)
			if (classes[i] == target_classes[i])
				class_error++;
		class_error /= target_classes.size();
	}
	/* #endregion Dense */
}