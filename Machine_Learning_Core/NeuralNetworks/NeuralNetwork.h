#pragma once

#include "Layer.h"

namespace NeuralNetwork {
	class NeuralNetwork
	{
		private:
			Layer* layers;
			LossFunction function;
			static std::string split(std::string& string, std::string token);
		public:
			NeuralNetwork(std::vector<int> layers, std::vector<LayerType> layer_types, std::vector<ActivationFunction> activation_functions, int num_of_inputs, LossFunction loss_function);
			NeuralNetwork(std::string s);
			float* feedForward(float* inputs);
			void backPropagation(float* inputs, float* target_results, float rate_of_change);
			void stochasticBackPropagation(float** inputs, float** target_results, float rate_of_change, int batch_size);
			std::string toString();
			std::string getSaveString();
			float getCost(float* inputs, float* target_results);
			float getAverageCost(float** inputs, float** target_results);
	};
}

