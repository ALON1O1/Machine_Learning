#include "Layer.h"
#include "ANNLayer.h"
#include <stdexcept>
#include <vector>

namespace NeuralNetwork {
	Layer* Layer::createLayer(std::string s) {
		LayerType type = enumOperations::getLayerType(split(s, ","));
		ActivationFunction function = enumOperations::getActivationFunction(split(s, ","));
		switch (type)
		{
			case NeuralNetwork::LayerType::ANN:
			{
				std::vector<std::vector<float>> weights = std::vector<std::vector<float>>();
				std::vector<float> biases = std::vector<float>();
				int size = std::stoi(split(s, ","));
				for (int i = 0; i < size; i++) {
					biases.push_back(std::stof(split(s, ",")));
					weights.push_back(std::vector<float>());
					int inputs = std::stoi(split(s, ","));
					for (int j = 0; j < inputs; j++) {
						weights[i].push_back(std::stof(split(s, ",")));
					}
				}
				return new ANNLayer(weights, biases, function);
			}
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
			//std::cout << s << std::endl;
			LayerType type = enumOperations::getLayerType(split(s, ","));
			ActivationFunction function = enumOperations::getActivationFunction(split(s, ","));
			switch (type)
			{
				case LayerType::ANN: {
					std::vector<std::vector<float>> weights = std::vector<std::vector<float>>();
					std::vector<float> biases = std::vector<float>();
					int size = std::stoi(split(s, ","));
					for (int i = 0; i < size; i++) {
						biases.push_back(std::stof(split(s, ",")));
						weights.push_back(std::vector<float>());
						int inputs = std::stoi(split(s, ","));
						for (int j = 0; j < inputs; j++) {
							weights[i].push_back(std::stof(split(s, ",")));
						}
					}
					next = new ANNLayer(weights, biases, function);
					break;
				}
				default:
					break;
			}
		}
		else next->addLayer(s);
	}

	std::string Layer::split(std::string& string, std::string token) {
		int index = string.find_first_of(token);
		if (index == -1) index = string.size();
		std::string return_value = string.substr(0, index);
		string.erase(0, index + token.size());
		return return_value;
	}
}
