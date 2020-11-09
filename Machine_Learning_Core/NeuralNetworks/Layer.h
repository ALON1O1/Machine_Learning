#pragma once

#include <string>
#include <vector>
#include "Enums.h"

namespace NeuralNetwork {
	
	class Layer
	{
		protected:
			Layer* next;
			ActivationFunction function;
			int num_of_outputs;
		public:
			static Layer* createLayer(std::string s);
			void addLayer(int size, ActivationFunction function, LayerType type);
			void addLayer(std::string s);
			virtual float* feedForward(float* inputs) = 0;
			virtual float* backPropagate(float* inputs, float* target_results, LossFunction loss_function, float rate_of_change) = 0;
			virtual float** stochasticBackPropagation(float** inputs, float** target_results, LossFunction loss_function, float rate_of_change) = 0;
			virtual std::string saveString() = 0;
			virtual std::string toString() = 0;

	};
}

