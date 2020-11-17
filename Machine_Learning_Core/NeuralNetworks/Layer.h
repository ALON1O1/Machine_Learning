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
			int num_of_inputs;
			static std::string split(std::string&, std::string);
		public:
			static Layer* createLayer(std::string);
			void addLayer(int size, ActivationFunction, LayerType);
			void addLayer(std::string);
			virtual std::vector<float> feedForward(std::vector<float>) = 0;
			virtual std::vector<float> backPropagate(std::vector<float>, std::vector<float>, LossFunction, float) = 0;
			virtual std::vector< std::vector<float>> stochasticBackPropagation(std::vector< std::vector<float>>, std::vector< std::vector<float>>, LossFunction, float) = 0;
			virtual std::string saveString() = 0;
			virtual std::string toString() = 0;

	};
}

