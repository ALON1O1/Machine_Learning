#pragma once

#include <string>

namespace NeuralNetwork {
	enum class ActivationFunction {identity, sigmoid, softmax, unknown};
	enum class LayerType {ANN, unknown};
	enum class LossFunction {quadratic, unknown};

	class enumOperations {
		public:
			static std::string getName(ActivationFunction function);
			static std::string getName(LossFunction function);
			static std::string getName(LayerType type);
	
			static ActivationFunction getActivationFunction(std::string function);
			static LossFunction getLossFunction(std::string function);
			static LayerType getLayerType(std::string function);
	};
}