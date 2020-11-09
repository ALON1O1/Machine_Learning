#include "Layer.h"

namespace NeuralNetwork {
	Layer* Layer::createLayer(std::string s) {
		return NULL;
	}
	void Layer::addLayer(int size[], ActivationFunction function, LayerType type) {

	}
	void Layer::addLayer(std::string s) {

	}
	std::string Layer::functionName() {
		switch (function) {
			case ActivationFunction::identity: return "identity";
			case ActivationFunction::sigmoid: return "sigmoid";
			case ActivationFunction::softmax: return "softmax";
			default: return "unknown";
		}
	}
}
