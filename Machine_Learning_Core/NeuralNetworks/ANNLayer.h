#pragma once
#include "Layer.h"
namespace NeuralNetwork {
	class ANNLayer: Layer
	{
		private:
			std::vector<std::vector<float>> weights;
			std::vector<float> biases;

			float deriveLoss(float err, LossFunction function);
			void activate(std::vector<float> values, std::vector<float>& return_values);
			void derive(std::vector<float> values, std::vector<float>& return_values);

		public:
			ANNLayer(int num_of_inputs, int size, ActivationFunction function);
			ANNLayer(std::vector<std::vector<float>> weights, std::vector<float> biases, ActivationFunction function);
			void feedForward(std::vector<float> inputs, std::vector<float>& results) override;

			void backPropagate(std::vector<float> inputs, std::vector<float> target_results, std::vector<float>& error, LossFunction loss_function, float rate_of_change) override;
			void stochasticBackPropagation(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> target_results, std::vector<std::vector<float>>& errors, LossFunction loss_function, float rate_of_change) override;
			
			std::string saveString() override;
			std::string toString();
	};
}

