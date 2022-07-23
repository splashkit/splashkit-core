#ifndef machine_learning_h
#define machine_learning_h

#include <iostream>

namespace splashkit_lib
{
	/**
	 * @brief Hidden layer for Machine Learning models
	 * 
	 */
	class Layer
	{
	public:
		matrix_2d input_shape;
		matrix_2d output_shape;
		virtual matrix_2d forward(const matrix_2d &input) { throw std::logic_error("not implemented"); };
	};

	enum ActivationFunction
	{
		ReLu, // Rectified Linear Unit
	};

	class _ActivationFunction
	{
	public:
		virtual matrix_2d apply(const matrix_2d &input) { throw std::logic_error("not implemented"); };
	};

	enum ErrorFunction
	{
		RSS, // Residual Sum of Squares
	};

	class _ErrorFunction
	{
	public:
		virtual matrix_2d apply(const matrix_2d &input) { throw std::logic_error("not implemented"); };
	};

	/**
	 * @brief Fully connected layer, slowest type, but can be used for any purpose.
	 * 
	 */
	
	class Dense : public Layer
	{
		matrix_2d weights;
		matrix_2d biases;

		_ActivationFunction activation_function;
		_ErrorFunction error_function;
	public:
		Dense(size_t input_size, size_t output_size, ActivationFunction activation_function, ErrorFunction error_function);
		matrix_2d forward(const matrix_2d &input);
		matrix_2d backward(const matrix_2d &input);
		void compute_error(const matrix_2d &input, const matrix_2d &target_output);
	};

	/**
	 * @brief A Machine Learning model
	 * 
	 */
	class Model
	{
	private:
		size_t input_x;
		size_t input_y;
		size_t output_x;
		size_t output_y;

		vector<Layer> layers;
		void forward(const matrix_2d &input);
	public:
		Model(size_t input_x, size_t input_y, size_t output_x, size_t output_y);
		matrix_2d predict(const matrix_2d &input);
		void train(const matrix_2d &input, const matrix_2d &output);
		void save(const string &filename);
		void load(const string &filename);
	};
}

#endif