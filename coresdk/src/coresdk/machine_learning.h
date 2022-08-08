#ifndef machine_learning_h
#define machine_learning_h

#include <iostream>
#include <memory>

namespace splashkit_lib
{
	enum ActivationFunction
	{
		ReLu, // Rectified Linear Unit
	};

	struct _ActivationFunction
	{
		virtual matrix_2d apply(const matrix_2d &input) { throw std::logic_error("not implemented"); };
		virtual matrix_2d derivative(const matrix_2d &input) { throw std::logic_error("not implemented"); };
	};

	enum ErrorFunction
	{
		RSS, // Residual Sum of Squares
	};

	struct _ErrorFunction
	{
		virtual double apply(const matrix_2d &output, const matrix_2d &target_output) { throw std::logic_error("not implemented"); };
		virtual double derivative(const matrix_2d &input) { throw std::logic_error("not implemented"); };
	};

	/**
	 * @brief Hidden layer for Machine Learning models
	 * 
	 */
	struct Layer
	{
		matrix_2d input_shape;
		matrix_2d output_shape;

		std::shared_ptr<_ActivationFunction> activation_function;

		virtual matrix_2d forward(const matrix_2d &input) { throw std::logic_error("not implemented"); };
	};

	/**
	 * @brief Fully connected layer, slowest type, but can be used for any purpose.
	 * 
	 */
	class Dense : public Layer
	{
		matrix_2d weights;
		matrix_2d biases;
	public:
		Dense(size_t input_size, size_t output_size, ActivationFunction activation_function);
		matrix_2d forward(const matrix_2d &input) override;
		matrix_2d backward(const matrix_2d &input);
		void compute_error(const matrix_2d &input, const matrix_2d &output, const matrix_2d &target_output);
	};

	/**
	 * @brief A Machine Learning model
	 * 
	 */
	class Model
	{
	private:
		std::shared_ptr<_ErrorFunction> error_function;

		vector<Layer> layers;
		void forward(const matrix_2d &input);
	public:
		Model(ErrorFunction error_function);
		void add_layer(Layer layer);
		matrix_2d predict(const matrix_2d &input);
		void train(const matrix_2d &input, const matrix_2d &target_output);
		void save(const string &filename);
		void load(const string &filename);
	};
}

#endif