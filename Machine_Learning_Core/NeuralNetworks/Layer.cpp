#include "Layer.h"
#include "ANNLayer.h"
#include <stdexcept>

namespace NeuralNetwork {
	Layer* Layer::createLayer(std::string s) {
		LayerType type = enumOperations::getLayerType(split(s, ","));
		ActivationFunction function = enumOperations::getActivationFunction(split(s, ","));
		switch (type)
		{
			case NeuralNetwork::LayerType::ANN:
				float** weights = new float*[std::stoi(split(s, ","))];
				float* biases = new float[sizeof(weights)];
				for (int i = 0; i < sizeof(biases); i++) {
					biases[i] = std::stof(split(s, ","));
					weights[i] = new float[std::stoi(split(s, ","))];
					for (int j = 0; j < sizeof(weights[i]); j++) {
						weights[i][j] = std::stof(split(s, ","));
					}
				}
				return new ANNLayer(weights, biases, function);
			default:
				break;
		}
		return NULL;
	}
	void Layer::addLayer(int size, ActivationFunction function, LayerType type) {
		if (next == NULL) {
			switch (type) {
			case LayerType::ANN: next = new ANNLayer(num_of_outputs, size, function); break;
			}
		}
		else next->addLayer(size, function, type);
	}
	void Layer::addLayer(std::string s) {
		if (next == NULL) {
			LayerType type = enumOperations::getLayerType(split(s, ","));
			ActivationFunction function = enumOperations::getActivationFunction(split(s, ","));
			float** weights;
			float* biases;
			switch (type)
			{
				biases = new float[std::stoi(split(s, ","))];
				weights = new float* [sizeof(biases)];
				for (int i = 0; i < sizeof(biases); i++) {
					biases[i] = std::stof(split(s, ","));
					weights[i] = new float[std::stoi(split(s, ","))];
					for (int j = 0 ; j < sizeof(weights[i]) ; j++) {
						weights[i][j] = std::stof(split(s, ","));
					}
				}
				next = new ANNLayer(weights, biases, function);
				break;
			default:
				break;
			}
		}
		else next->addLayer(s);
	}

	std::string split(std::string& string, std::string token) {
		int index = string.find_first_of(",");
		if (index == -1) throw std::invalid_argument("string syntax error!");
		std::string return_value = string.substr(0, index);
		string.erase(0, index + 1);
		return return_value;
	}
}
