#include "Enums.h"
#include <stdexcept>

namespace NeuralNetwork {
	std::string getName(ActivationFunction function) {
		switch (function)
		{
			case NeuralNetwork::ActivationFunction::identity: return "identity";
			case NeuralNetwork::ActivationFunction::sigmoid: return "sigmoid";
			case NeuralNetwork::ActivationFunction::softmax: return "softmax";
			default: throw std::invalid_argument("activation function could not be recognized");
		}
	}
	std::string getName(LossFunction function) {
		switch (function)
		{
			case NeuralNetwork::LossFunction::quadratic: return "quadratic";
			default: throw std::invalid_argument("activation function could not be recognized");
		}
	}
	std::string getName(LayerType type) {
		switch (type)
		{
			case NeuralNetwork::LayerType::ANN: return "ANN";
			default: throw std::invalid_argument("activation function could not be recognized");
		}
	}

	ActivationFunction getActivationFunction(std::string function) {
		if (function._Equal("identity")) return ActivationFunction::identity;
		if (function._Equal("sigmoid")) return ActivationFunction::sigmoid;
		if (function._Equal("softmax")) return ActivationFunction::softmax;
		throw std::invalid_argument("activation function could not be recognized");
	}
	LossFunction getLossFunction(std::string function) {
		if (function._Equal("quadratic")) return LossFunction::quadratic;
		throw std::invalid_argument("activation function could not be recognized");
	}
	LayerType getLayerType(std::string type) {
		if (type._Equal("ANN")) return LayerType::ANN;
		throw std::invalid_argument("activation function could not be recognized");
	}
}