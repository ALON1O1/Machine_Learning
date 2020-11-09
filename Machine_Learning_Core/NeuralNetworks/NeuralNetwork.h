#pragma once

#include "Layer.h"

namespace NeuralNetwork {
	class NeuralNetwork
	{
		private:
			Layer* layers;
			LossFunction function;
		public:
			NeuralNetwork(int* layers, LayerType* layer_types, ActivationFunction* activation_functions, int num_of_inputs, LossFunction loss_function);
			float* feedForward(float* inputs);
			void backPropagation(float* inputs, float* target_results, float rate_of_change);
			void stochasticBackPropagation(float** inputs, float** target_results, float rate_of_change, int batch_size);
			std::string toString();
			std::string getSaveString();
			float getCost(float* inputs, float* target_results);
			float getAverageCost(float** inputs, float** target_results);
	};
}

