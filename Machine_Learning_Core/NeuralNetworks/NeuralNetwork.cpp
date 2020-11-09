#include "NeuralNetwork.h"
#include "ANNLayer.h"
#include <stdexcept>
#include "Enums.h"

namespace NeuralNetwork {
	NeuralNetwork::NeuralNetwork(int* layers, LayerType* layer_types, ActivationFunction* activation_functions, int num_of_inputs, LossFunction loss_function) {
		if (sizeof(layers) != sizeof(layer_types)) throw std::invalid_argument("layers array must be the same size as layer_types array. layers:" + std::to_string(sizeof(layers)) + " layer_types:" + std::to_string(sizeof(layer_types)));
		if (sizeof(layers) != sizeof(activation_functions)) throw std::invalid_argument("layers array must be the same size as activation_functions array. layers:" + std::to_string(sizeof(layers)) + " activation_functions:" + std::to_string(sizeof(activation_functions)));
		switch (layer_types[0]) {
			case LayerType::ANN:
				this->layers = new ANNLayer(num_of_inputs, layers[0], activation_functions[0]);
		}
		for (int i = 1; i < sizeof(layers); i++) {
			this->layers->addLayer(layers[i], activation_functions[i], layer_types[i]);
		}
		function = loss_function;
	}

	float* NeuralNetwork::feedForward(float* inputs) {
		return layers->feedForward(inputs);
	}

	void NeuralNetwork::backPropagation(float* inputs, float* target_results, float rate_of_change) {
		layers->backPropagate(inputs, target_results, function, rate_of_change);
	}
	void NeuralNetwork::stochasticBackPropagation(float** inputs, float** target_results, float rate_of_change, int batch_size) {
		if (batch_size >= sizeof(inputs)) layers->stochasticBackPropagation(inputs, target_results, function, rate_of_change);
		else {
			int i;
			for (i = 0; i < sizeof(inputs); i += batch_size) {
				float** batch_inputs = new float*[batch_size];
				float** batch_target_results = new float* [batch_size];
				for (int j = 0; j < batch_size; j++) {
					batch_inputs[j] = inputs[i * batch_size + j];
					batch_target_results[j] = target_results[i * batch_size + j];
				}
				layers->stochasticBackPropagation(batch_inputs, batch_target_results, function, rate_of_change);
			}
			float** batch_inputs = new float* [sizeof(inputs) - i];
			float** batch_target_results = new float* [sizeof(target_results) - i];
			for (int j = 0; j < sizeof(batch_inputs); j++) {
				batch_inputs[j] = inputs[i + j];
				batch_target_results[j] = target_results[i + j];
			}
			layers->stochasticBackPropagation(batch_inputs, batch_target_results, function, rate_of_change);
		}
	}

	std::string NeuralNetwork::toString() {
		return "loss function: " + enumOperations::getName(function) + "\n" + layers->toString();
	}
	std::string NeuralNetwork::getSaveString() {
		return enumOperations::getName(function) + "\n" + layers->saveString();
	}

	float NeuralNetwork::getCost(float* inputs, float* target_results) {
		switch (function)
		{
		case LossFunction::quadratic:{
			float* results = feedForward(inputs);
			float cost = 0;
			for (int i = 0; i < sizeof(results); i++) {
				cost += (results[i] - target_results[i]) * (results[i] - target_results[i]);
			}
			return cost;
		}
		default: throw std::invalid_argument("activation function could not be recognized");
		}
	}
	float NeuralNetwork::getAverageCost(float** inputs, float** target_results) {
		switch (function)
		{
		case LossFunction::quadratic: {
			float cost = 0;
			for (int i = 0; i < sizeof(inputs); i++) {
				float* results = feedForward(inputs[i]);
				for (int j = 0; j < sizeof(results); j++) {
					cost += (results[j] - target_results[i][j]) * (results[j] - target_results[i][j]);
				}
			}
			return cost / sizeof(inputs);
		}
		default: throw std::invalid_argument("activation function could not be recognized");
		}
	}
}