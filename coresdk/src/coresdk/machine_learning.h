#ifndef machine_learning_h
#define machine_learning_h

#include <iostream>
#include <memory>

namespace splashkit_lib
{
	matrix_2d to_categorical(const matrix_2d &m);

	enum ActivationFunction
	{
		ReLu, // Rectified Linear Unit
		Sigmoid,
		Softmax, // Softmax
	};

	struct _ActivationFunction
	{
		/**
		 * @brief The enum identifier for this activation function. 
		 * This is used to distinguish between different activation functions for saving/debugging purposes.
		 */
		static const ActivationFunction type;

		/**
		 * @brief Apply the activation function to the given input.
		 * 
		 * @param input The layer output to apply the activation function to.
		 * @return matrix_2d 
		 */
		virtual matrix_2d apply(const matrix_2d &input) { throw std::logic_error("not implemented"); };

		/**
		 * @brief The backward of the activation function.
		 * 
		 * @param input The input that was passed to the activation function.
		 * @return matrix_2d 
		 */
		virtual matrix_2d backward(const matrix_2d &input, const matrix_2d &output, const matrix_2d &delta) { throw std::logic_error("not implemented"); };
	};

	enum LossFunction
	{
		MSE, // Residual Sum of Squares
	};

	struct _LossFunction
	{
		/**
		 * @brief The enum identifier for this loss function.
		 * This is used to distinguish between different loss functions for saving/debugging purposes.
		 */
		static const LossFunction type;

		/**
		 * @brief Apply the loss function to the given output and target output.
		 * 
		 * @param output The output of the model.
		 * @param target_output The target output.
		 * @return double 
		 */
		virtual double loss(const matrix_2d &output, const matrix_2d &target_output) { throw std::logic_error("not implemented"); };

		/**
		 * @brief The backward pass of the loss function.
		 * Calculates dE/dO where E is the loss and O is the output.
		 * 
		 * @param output The output of the model.
		 * @param target_output The target output.
		 * @return matrix_2d 
		 */
		virtual matrix_2d backward(const matrix_2d &output, const matrix_2d &target_output) { throw std::logic_error("not implemented"); };
	};

	/**
	 * @brief Hidden layer for Machine Learning models
	 * 
	 */
	struct Layer
	{
		/**
		 * @brief The name of the layer, used for debugging.
		 */
		std::string name;
		
		/**
		 * @brief The expected shape to be inputted into this layer.
		 */
		size_t input_size;
		/**
		 * @brief The expected shape to be outputted from this layer.
		 */
		size_t output_size;

		/**
		 * @brief The activation function to use for this layer.
		 */
		std::shared_ptr<_ActivationFunction> activation_function;

		/**
		 * @brief The learning_rate to use for this layer. This value is initialised when the layer is added to a Model.
		 */
		double learning_rate;

		/**
		 * @brief Feed-forward function
		 * 
		 * @param input 
		 * @return matrix_2d 
		 */
		virtual matrix_2d forward(const matrix_2d &input) { throw std::logic_error("not implemented"); };
		/**
		 * @brief Back-propagation function
		 * 
		 * @param input 
		 * @param output 
		 * @param delta The delta/derivative of the previous layer during back propagation.
		 * @return matrix_2d 
		 */
		virtual matrix_2d backward(const matrix_2d &input, const matrix_2d &before_activation, const matrix_2d &output, matrix_2d &delta) { throw std::logic_error("not implemented"); };
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
		matrix_2d get_weights() { return weights; };
		matrix_2d forward(const matrix_2d &input) override;
		matrix_2d backward(const matrix_2d &input, const matrix_2d &before_activation, const matrix_2d &output, matrix_2d &delta) override;
	};

	/**
	 * @brief A Machine Learning model
	 * 
	 */
	class Model
	{
	private:
		std::shared_ptr<_LossFunction> error_function;

		double learning_rate;

		vector<std::shared_ptr<Layer>> layers;
		void forward(const matrix_2d &input);
	public:
		Model(LossFunction error_function, double learning_rate=0.01);
		void add_layer(Layer *layer);
		matrix_2d predict(const matrix_2d &input);
		vector<double> train(const matrix_2d &input, const matrix_2d &target_output);

		/**
		 * @brief Save a trained model to disk so that it can be loaded later using the model.load() function.
		 * 
		 * @param filename 
		 */
		void save(const string &filename);

		/**
		 * @brief Load a model that was saved to disk using the model.save() function.
		 * 
		 * @param filename 
		 */
		void load(const string &filename);
	};
}

#endif