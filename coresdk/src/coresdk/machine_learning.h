#ifndef machine_learning_h
#define machine_learning_h

#include <iostream>
#include <memory>

namespace splashkit_lib
{
	enum ActivationFunction
	{
		ReLu, // Rectified Linear Unit
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
		 * @brief The derivative of the activation function.
		 * 
		 * @param input The input that was passed to the activation function.
		 * @return matrix_2d 
		 */
		virtual matrix_2d derivative(const matrix_2d &output, const matrix_2d &delta) { throw std::logic_error("not implemented"); };
	};

	enum ErrorFunction
	{
		RSS, // Residual Sum of Squares
	};

	struct _ErrorFunction
	{
		/**
		 * @brief The enum identifier for this error function.
		 * This is used to distinguish between different error functions for saving/debugging purposes.
		 */
		static const ErrorFunction type;

		/**
		 * @brief Apply the error function to the given output and target output.
		 * 
		 * @param output The output of the model.
		 * @param target_output The target output.
		 * @return double 
		 */
		virtual double apply(const matrix_2d &output, const matrix_2d &target_output) { throw std::logic_error("not implemented"); };

		/**
		 * @brief The derivative of the error function.
		 * 
		 * @param output The output that was passed to the error function.
		 * @return matrix_2d 
		 */
		virtual double derivative(const matrix_2d &input) { throw std::logic_error("not implemented"); };
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
		std::pair<size_t, size_t> input_shape;
		/**
		 * @brief The expected shape to be outputted from this layer.
		 */
		std::pair<size_t, size_t> output_shape;

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
		 * @param next_delta The delta/derivative of the next layer during feed-forward.
		 * @return matrix_2d 
		 */
		virtual matrix_2d backward(const matrix_2d &input, const matrix_2d &before_activation, const matrix_2d &output, const matrix_2d &next_delta) { throw std::logic_error("not implemented"); };
		virtual void update_weights(const matrix_2d &input, const matrix_2d &output, const matrix_2d &delta) { throw std::logic_error("not implemented"); };
	};

	/**
	 * @brief Fully connected layer, slowest type, but can be used for any purpose.
	 * 
	 */
	class Dense : public Layer
	{
		matrix_2d weights;
		matrix_2d biases;

		size_t input_size;
		size_t output_size;
	public:
		Dense(size_t input_size, size_t output_size, ActivationFunction activation_function);
		matrix_2d get_weights() { return weights; };
		matrix_2d forward(const matrix_2d &input) override;
		matrix_2d backward(const matrix_2d &input, const matrix_2d &before_activation, const matrix_2d &output, const matrix_2d &next_delta) override;
		void update_weights(const matrix_2d &input, const matrix_2d &output, const matrix_2d &delta) override;
		void compute_error(const matrix_2d &output, const matrix_2d &target_output);
	};

	/**
	 * @brief A Machine Learning model
	 * 
	 */
	class Model
	{
	private:
		std::shared_ptr<_ErrorFunction> error_function;

		double learning_rate;

		vector<std::shared_ptr<Layer>> layers;
		void forward(const matrix_2d &input);
	public:
		Model(ErrorFunction error_function, double learning_rate=0.01);
		void add_layer(Layer *layer);
		matrix_2d predict(const matrix_2d &input);
		void train(const matrix_2d &input, const matrix_2d &target_output);

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