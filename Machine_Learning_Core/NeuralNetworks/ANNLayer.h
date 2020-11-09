#pragma once
#include "Layer.h"

namespace NeuralNetwork {
	class ANNLayer: Layer
	{
		private:
			ActivationFunction function;
			float** weights;
			float* biases;

			float deriveLoss(float err, LossFunction function);
			float* activate(float* values);
			float* derive(float* values);

		public:
			ANNLayer(int num_of_inputs, int size, ActivationFunction function);
			ANNLayer(float** weights, float* biases, ActivationFunction function);
			float* feedForward(float* inputs) override;

			float* backPropagate(float* inputs, float* target_results, LossFunction loss_function, float rate_of_change) override;
			float** stochasticBackPropagation(float** inputs, float** target_results, LossFunction loss_function, float rate_of_change) override;
			
			std::string saveString() override;
			std::string toString();
	};
}

