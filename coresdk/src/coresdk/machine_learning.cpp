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

	matrix_2d to_categorical(const matrix_2d &m)
	{
		matrix_2d result(m.x, 1);

		for (size_t x = 0; x < m.x; x++)
		{
			int max = 0;
			for (size_t y = 1; y < m.y; y++)
				if (m.elements[x][y] > m.elements[x][max])
					max = y;
			result[x][0] = max;
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
	struct f_Sigmoid : public _ActivationFunction
	{
		static const ActivationFunction type = Sigmoid;

		matrix_2d apply(const matrix_2d &input) override
		{
			matrix_2d result(1, input.y);

			for (size_t y = 0; y < input.y; y++)
				result.elements[0][y] = 1 / (1 + exp(-input.elements[0][y]));

			return result;
		}

		matrix_2d backward(const matrix_2d &input, const matrix_2d &output, const matrix_2d &delta) override
		{
			return delta * output * (-output + 1); // element wise delta * output * (1 - output)
		}
	};

	struct f_ReLu : public _ActivationFunction
	{
		static const ActivationFunction type = ReLu;

		matrix_2d apply(const matrix_2d &input) override
		{
			return input[input > 0];
		}

		matrix_2d backward(const matrix_2d &input, const matrix_2d &output, const matrix_2d &delta) override
		{
			return input > 0;
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

		matrix_2d backward(const matrix_2d &input, const matrix_2d &output, const matrix_2d &delta) override
		{
			matrix_2d result(input.y, input.y); // n^2 matrix

			for (size_t x = 0; x < result.x; x++)
				for (size_t y = 0; y < result.y; y++)
				{
					if (x == y)
						result.elements[x][y] = input.elements[0][x] * (1 - input.elements[0][x]);
					else
						result.elements[x][y] = -input.elements[0][x] * input.elements[0][y];
				}
			return result;
			/* idk
			matrix_2d result(input.x, input.y);
			for (size_t x = 0; x < input.x; x++)
			{
				for (size_t y = 0; y < input.y; y++)
				{
					double sum = 0.0;
					const double neg_sft_i = -input.elements[x][y];

					for (size_t x1 = 0; x1 < input.x; x1++)
						for (size_t y1 = 0; y1 < input.y; y1++)
							sum += delta.elements[x1][y1] * input.elements[x1][y1] * neg_sft_i;

					result.elements[x][y] = sum + input.elements[x][y] * delta.elements[x][y];
				}
			}
			return result; //*/
		}
	};

	// Simple factory
	shared_ptr<_ActivationFunction> get_activation_function(ActivationFunction name)
	{
		switch (name)
		{
		case ActivationFunction::ReLu:
			return shared_ptr<_ActivationFunction>(new f_ReLu());
		case ActivationFunction::Sigmoid:
			return shared_ptr<_ActivationFunction>(new f_Sigmoid());
		case ActivationFunction::Softmax:
			return shared_ptr<_ActivationFunction>(new f_Softmax());
		default:
			throw invalid_argument("Unknown activation function");
		}
	}
	/* #endregion */

	/* #region  ErrorFunctions */
	class f_MSE : public _LossFunction
	{
		static const LossFunction type = MSE;

		double loss(const matrix_2d &output, const matrix_2d &target_output) override
		{
			return sum(sq(target_output - output)) / (2.0 * output.y);
		}

		matrix_2d backward(const matrix_2d &output, const matrix_2d &target_output) override
		{
			return (output - target_output) / output.y; // -(target_output - output)/m is derivative of (1/2)*MSE
		}
	};

	// Simple factory
	shared_ptr<_LossFunction> get_error_function(LossFunction name)
	{
		switch (name)
		{
		case LossFunction::MSE:
			return shared_ptr<_LossFunction>(new f_MSE());
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

	Model::Model(LossFunction error_function, double learning_rate)
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
		matrix_2d result(input.x, layers.back()->output_size);
		for (size_t i = 0; i < input.x; i++)
		{
			matrix_2d row = matrix_slice(input, i, i);
			for (auto &layer : layers)
			{
				row = layer->forward(row);
				row = layer->activation_function->apply(row);
			}
			for (size_t j = 0; j < layers.back()->output_size; j++)
			{
				result.elements[i][j] = row.elements[0][j];
			}
		}
		return result;
	}

	vector<double> Model::train(const matrix_2d &input, const matrix_2d &target_output)
	{
		vector<double> losses;
		for (int i = 0; i < input.x; i++)
		{
			matrix_2d row = matrix_slice(input, i, i);

			/* #region Forward Propagation */
			vector<matrix_2d> outputs(layers.size()*2+1);
			outputs[0] = row;
			for (int j = 0; j < layers.size(); j++)
			{
				outputs[j*2+1] = layers[j]->forward(outputs[j*2]); // weights * x + bias
				outputs[j*2+2] = layers[j]->activation_function->apply(outputs[j*2+1]);
			}
			/* #endregion */

			matrix_2d target_output_row = matrix_slice(target_output, i, i);
			matrix_2d difference = target_output_row - outputs[layers.size()*2];

			losses.push_back(error_function->loss(outputs[layers.size()*2], target_output_row));

			matrix_2d delta = error_function->backward(outputs[layers.size()*2], target_output_row);
			for (int j = layers.size(); j > 0; j--)
			{
				delta = layers[j-1]->backward(outputs[j*2-2], outputs[j*2-1], outputs[j*2], delta);
			}
		}
		return losses;
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

	matrix_2d Dense::backward(const matrix_2d &input, const matrix_2d &before_activation, const matrix_2d &output, matrix_2d &delta)
	{
		matrix_2d new_delta = matrix_2d(1, input.y);

		delta = activation_function->backward(before_activation, output, delta);
		for (int x = 0; x < input_size; x++)
		{
			double error = 0.0;
			for (int y = 0; y < output_size; y++)
			{
				error += weights.elements[x][y] * delta.elements[0][y];
				weights.elements[x][y] -= learning_rate * delta.elements[0][y] * input.elements[0][x];
			}
			new_delta.elements[0][x] = error;
		}
		return new_delta;
	}
	/* #endregion Dense */
}