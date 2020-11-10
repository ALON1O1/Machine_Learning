#include "Enums.h"
#include <stdexcept>

namespace NeuralNetwork {
	std::string enumOperations::getName(ActivationFunction function) {
		switch (function)
		{
			case NeuralNetwork::ActivationFunction::identity: return "identity";
			case NeuralNetwork::ActivationFunction::sigmoid: return "sigmoid";
			case NeuralNetwork::ActivationFunction::softmax: return "softmax";
			default: throw std::invalid_argument("activation function could not be recognized");
		}
	}
	std::string enumOperations::getName(LossFunction function) {
		switch (function)
		{
			case NeuralNetwork::LossFunction::quadratic: return "quadratic";
			default: throw std::invalid_argument("activation function could not be recognized");
		}
	}
	std::string enumOperations::getName(LayerType type) {
		switch (type)
		{
			case NeuralNetwork::LayerType::ANN: return "ANN";
			default: throw std::invalid_argument("activation function could not be recognized");
		}
	}

	ActivationFunction enumOperations::getActivationFunction(std::string function) {
		if (function._Equal("identity")) return ActivationFunction::identity;
		if (function._Equal("sigmoid")) return ActivationFunction::sigmoid;
		if (function._Equal("softmax")) return ActivationFunction::softmax;
		throw std::invalid_argument("activation function could not be recognized: " + function);
	}
	LossFunction enumOperations::getLossFunction(std::string function) {
		if (function._Equal("quadratic")) return LossFunction::quadratic;
		throw std::invalid_argument("loss function could not be recognized:" + function);
	}
	LayerType enumOperations::getLayerType(std::string type) {
		if (type._Equal("ANN")) return LayerType::ANN;
		throw std::invalid_argument("layer type could not be recognized: " + type);
	}
}