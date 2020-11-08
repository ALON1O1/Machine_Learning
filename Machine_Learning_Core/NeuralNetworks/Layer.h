#pragma once

#include <string>
#include <vector>
#include "Enums.h"

namespace NeuralNetwork {
	
	class Layer
	{
		private:
			Layer* next;
			ActivationFunction function;
			int num_of_outputs;
		public:
			static Layer* createLayer(std::string s);
			void addLayer(int size[], ActivationFunction function, LayerType type);
			void addLayer(std::string s);
			virtual void feedForward(std::vector<float> inputs, std::vector<float>& results) = 0;
			virtual void backPropagate(std::vector<float> inputs, std::vector<float> target_results, std::vector<float>& error, LossFunction loss_function, float rate_of_change) = 0;
			virtual void stochasticBackPropagation(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> target_results, std::vector<std::vector<float>>& errors, LossFunction loss_function, float rate_of_change) = 0;
			virtual std::string saveString() = 0;

	};
}

