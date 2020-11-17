#include "NeuralNetwork.h"
#include "ANNLayer.h"
#include <stdexcept>
#include "Enums.h"
#include <iostream>

namespace NeuralNetwork {
	NeuralNetwork::NeuralNetwork(std::vector<int> layers, std::vector<LayerType> layer_types, std::vector<ActivationFunction> activation_functions, int num_of_inputs, LossFunction loss_function) {
		if (sizeof(layers) != sizeof(layer_types)) throw std::invalid_argument("layers array must be the same size as layer_types array. layers:" + std::to_string(sizeof(layers)) + " layer_types:" + std::to_string(sizeof(layer_types)));
		if (sizeof(layers) != sizeof(activation_functions)) throw std::invalid_argument("layers array must be the same size as activation_functions array. layers:" + std::to_string(sizeof(layers)) + " activation_functions:" + std::to_string(sizeof(activation_functions)));
		switch (layer_types[0]) {
			case LayerType::ANN: this->layers = new ANNLayer(num_of_inputs, layers[0], activation_functions[0]); break;
			default: throw std::invalid_argument("could not recognize layer type!");
		}
		for (unsigned int i = 1; i < layers.size(); i++) {
			this->layers->addLayer(layers[i], activation_functions[i], layer_types[i]);
		}
		function = loss_function;
	}
	NeuralNetwork::NeuralNetwork(std::string s) {
		function = enumOperations::getLossFunction(split(s, "\n"));
		layers = Layer::createLayer(split(s, "\n"));
		while (!s.empty()) {
			layers->addLayer(split(s, "\n"));

		}
	}

	std::vector<float> NeuralNetwork::feedForward(std::vector<float> inputs) {
		return layers->feedForward(inputs);
	}

	void NeuralNetwork::backPropagation(std::vector<float> inputs, std::vector<float> target_results, float rate_of_change) {
		layers->backPropagate(inputs, target_results, function, rate_of_change);
	}
	void NeuralNetwork::stochasticBackPropagation(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> target_results, float rate_of_change, unsigned int batch_size) {
		if (batch_size >= inputs.size()) layers->stochasticBackPropagation(inputs, target_results, function, rate_of_change);
		else {
			std::vector<std::vector<std::vector<float>>> batch_inputs = std::vector<std::vector<std::vector<float>>>();
			std::vector<std::vector<std::vector<float>>> batch_target_results = std::vector<std::vector<std::vector<float>>>();
			unsigned int batches_num = inputs.size() / batch_size;
			if (inputs.size() % batch_size != 0) batches_num++;
			for (unsigned int i = 0; i < batches_num; i++) {
				batch_inputs.push_back(std::vector<std::vector<float>>());
				batch_target_results.push_back(std::vector<std::vector<float>>());
			}
			for (unsigned int i = 0; i < inputs.size(); i ++) {
				batch_inputs[i / batch_size].push_back(inputs[i]);
				batch_target_results[i / batch_size].push_back(target_results[i]);
			}
			for(unsigned int i = 0 ; i < batch_inputs.size() ; i++) layers->stochasticBackPropagation(batch_inputs[i], batch_target_results[i], function, rate_of_change);
		}
	}

	std::string NeuralNetwork::toString() {
		return "loss function: " + enumOperations::getName(function) + "\n" + layers->toString();
	}
	std::string NeuralNetwork::getSaveString() {
		return enumOperations::getName(function) + "\n" + layers->saveString();
	}

	float NeuralNetwork::getCost(std::vector<float> inputs, std::vector<float> target_results) {
		switch (function)
		{
		case LossFunction::quadratic:{
			std::vector<float> results = feedForward(inputs);
			float cost = 0;
			for (unsigned int i = 0; i < results.size(); i++) {
				cost += (results[i] - target_results[i]) * (results[i] - target_results[i]);
			}
			return cost;
		}
		default: throw std::invalid_argument("activation function could not be recognized");
		}
	}
	float NeuralNetwork::getAverageCost(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> target_results) {
		switch (function)
		{
		case LossFunction::quadratic: {
			float cost = 0;
			for (unsigned int i = 0; i < sizeof(inputs); i++) {
				std::vector<float> results = feedForward(inputs[i]);
				for (unsigned int j = 0; j < results.size(); j++) {
					cost += (results[j] - target_results[i][j]) * (results[j] - target_results[i][j]);
				}
			}
			return cost / sizeof(inputs);
		}
		default: throw std::invalid_argument("activation function could not be recognized");
		}
	}

	std::string NeuralNetwork::split(std::string& string, std::string token) {
		int index = string.find_first_of(token);
		if (index == -1) index = string.size();
		std::string return_value = string.substr(0, index);
		string.erase(0, index + token.size());
		return return_value;
	}
}