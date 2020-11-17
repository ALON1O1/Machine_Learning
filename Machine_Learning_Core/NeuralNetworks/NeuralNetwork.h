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
			std::vector<float> feedForward(std::vector<float> inputs);
			void backPropagation(std::vector<float> inputs, std::vector<float> target_results, float rate_of_change);
			void stochasticBackPropagation(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> target_results, float rate_of_change, unsigned int batch_size);
			std::string toString();
			std::string getSaveString();
			float getCost(std::vector<float> inputs, std::vector<float> target_results);
			float getAverageCost(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> target_results);
	};
}

