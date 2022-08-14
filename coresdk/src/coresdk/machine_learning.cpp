#include "random.h"
#include "matrix_2d.h"
#include "machine_learning.h"

#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

namespace splashkit_lib
{
	matrix_2d matrix_exp(const matrix_2d &m)
	{
		matrix_2d result(m.x, m.y);

		for (size_t x = 0; x < m.x; x++)
			for (size_t y = 0; y < m.y; y++)
					result.elements[x][y] = exp(m.elements[x][y]);

		return result;
	}

	matrix_2d inline sq(const matrix_2d &m)
	{
		return matrix_multiply_components(m, m);
	}

	double max(const matrix_2d &m)
	{
		double result = m.elements[0][0];
		for (size_t i = 0; i < m.x; i++)
			for (size_t j = 0; j < m.y; j++)
				if (m.elements[i][j] > result)
					result = m.elements[i][j];
		return result;
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

		for (size_t x = 0; x < m.x; x++)
		{
			result[x] = 0;
			for (size_t y = 1; y < m.y; y++)
				if (m.elements[x][y] > result[x])
					result[x] = y;
		}

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
		static const ActivationFunction type = ReLu;

		matrix_2d apply(const matrix_2d &input) override
		{
			return input[input > 0];
		}

		matrix_2d derivative(const matrix_2d &output, const matrix_2d &delta) override
		{
			return output > 0;
		}
	};

	struct f_Softmax : public _ActivationFunction
	{
		static const ActivationFunction type = Softmax;

		matrix_2d apply(const matrix_2d &input) override
		{
			// assert input.x == 1

			double exp_sum = 0;
			double max_input = max(input);

			for (size_t y = 0; y < input.y; y++)
				exp_sum += exp(input.elements[0][y] - max_input);
			
			double constant = max_input + log(exp_sum);
			matrix_2d result(1, input.y);

			for (size_t y = 0; y < input.y; y++)
				result.elements[0][y] = exp(input.elements[0][y] - constant);

			return result;
		}

		matrix_2d derivative(const matrix_2d &output, const matrix_2d &delta) override
		{
			matrix_2d result(output.y, output.y); // n^2 matrix

			for (size_t x = 0; x < result.x; x++)
				for (size_t y = 0; y < result.y; y++)
				{
					if (x == y)
						result.elements[x][y] = output.elements[0][x] * (1 - output.elements[0][x]);
					else
						result.elements[x][y] = -output.elements[0][x] * output.elements[0][y];
				}
			return result;
			/* idk
			matrix_2d result(output.x, output.y);
			for (size_t x = 0; x < output.x; x++)
			{
				for (size_t y = 0; y < output.y; y++)
				{
					double sum = 0.0;
					const double neg_sft_i = -output.elements[x][y];

					for (size_t x1 = 0; x1 < output.x; x1++)
						for (size_t y1 = 0; y1 < output.y; y1++)
							sum += delta.elements[x1][y1] * output.elements[x1][y1] * neg_sft_i;

					result.elements[x][y] = sum + output.elements[x][y] * delta.elements[x][y];
				}
			}
			return result; //*/
		}
	};

	shared_ptr<_ActivationFunction> get_activation_function(ActivationFunction name)
	{
		switch (name)
		{
		case ActivationFunction::ReLu:
			return shared_ptr<_ActivationFunction>(new f_ReLu());
		case ActivationFunction::Softmax:
			return shared_ptr<_ActivationFunction>(new f_Softmax());
		default:
			throw invalid_argument("Unknown activation function");
		}
	}
	/* #endregion */

	/* #region  ErrorFunctions */
	class f_RSS : public _ErrorFunction
	{
		static const ErrorFunction type = RSS;

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
			throw invalid_argument("Unknown error function");
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
			outputs[i + 1] = layers[i]->forward(outputs[i]);
		}
	}

	Model::Model(ErrorFunction error_function, double learning_rate)
	{
		this->learning_rate = learning_rate;
		this->error_function = get_error_function(error_function);
	}

	void Model::add_layer(Layer *layer)
	{
		layer->learning_rate = learning_rate;
		layers.push_back(shared_ptr<Layer>(layer));
	}

	/// predicts rows of matrix and returns the result
	matrix_2d Model::predict(const matrix_2d &input)
	{
		matrix_2d result(input.x, layers.back()->output_shape.second);
		for (size_t i = 0; i < input.x; i++)
		{
			matrix_2d row = matrix_slice(input, i, i);
			for (auto &layer : layers)
			{
				row = layer->forward(row);
			}
			for (size_t j = 0; j < layers.back()->output_shape.second; j++)
			{
				result.elements[i][j] = row.elements[0][j];
			}
		}
		return result;
	}

	void Model::train(const matrix_2d &input, const matrix_2d &target_output)
	{
		for (size_t i = 0; i < input.x; i++)
		{
			matrix_2d row = matrix_slice(input, i, i);

			/* #region Forward Propagation */
			vector<matrix_2d> outputs(layers.size()*2+1);
			outputs[0] = row;
			for (size_t i = 0; i < layers.size(); i ++)
			{
				outputs[i*2+1] = layers[i]->forward(outputs[i*2]); // weights * x + bias
				outputs[i*2+2] = layers[i]->activation_function->apply(outputs[i*2+1]);
			}
			/* #endregion */

			matrix_2d target_output_row = matrix_slice(target_output, i, i);
			matrix_2d difference = target_output_row - outputs[layers.size()];
			vector<matrix_2d> delta(layers.size() + 1);

			delta[layers.size()] = matrix_multiply_components(layers.back()->activation_function->derivative(outputs[layers.size()], difference), difference); // error_function->derivative(difference); // TODO look at this line
			for (size_t i = layers.size(); i > 0; i--)
			{
				if (i == layers.size()) {
					layers.back()->update_weights(outputs[i*2-2], outputs[i*2], delta[i]); // first pass uses difference as delta
					// delta[i-1] = NULL; // pass delta backwards
				} else {
					delta[i-1] = layers[i-1]->backward(outputs[i*2-2], outputs[i*2-1], outputs[i*2], delta[i]);
				}
			}
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
		this->name = "Dense";
		this->biases = fill_matrix(1, output_size, 0);
		this->weights = matrix_2d(input_size, output_size);

		this->input_shape = { 1, input_size };
		this->output_shape = { 1, output_size };

		this->input_size = input_size;
		this->output_size = output_size;

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
		return matrix_multiply(input, weights) + biases;
	}

	matrix_2d Dense::backward(const matrix_2d &input, const matrix_2d &before_activation, const matrix_2d &output, const matrix_2d &next_delta)
	{
		matrix_2d delta = matrix_2d(1, input.y);
		matrix_2d derivative = activation_function->derivative(before_activation, next_delta);
		for (size_t x = 0; x < input_size; x++)
		{
			double error = 0.0;
			for (size_t y = 0; y < output_size; y++)
			{
				error += weights.elements[x][y] * next_delta.elements[0][y] * derivative.elements[0][y]; // TODO: This could be the wrong line
			}
			delta.elements[0][x] = error; // Could be changed
		}
		update_weights(input, output, delta);
		return delta;
	}

	inline void Dense::update_weights(const matrix_2d &input, const matrix_2d &output, const matrix_2d &delta)
	{
		for (size_t x = 0; x < input_size; x++)
		{
			for (size_t y = 0; y < output_size; y++)
			{
				weights.elements[x][y] -= learning_rate * delta.elements[0][y] * input.elements[0][x];
			}
		}
	}

	void Dense::compute_error(const matrix_2d &output, const matrix_2d &target_output)
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