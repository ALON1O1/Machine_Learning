#define _USE_MATH_DEFINES
#include "ANNLayer.h"
#include <math.h>
#include <stdexcept>
#include "..\Math\Vector.h"
#include "..\Math\Matrix.h"
#include <iostream>

namespace NeuralNetwork {

	ANNLayer::ANNLayer(int num_of_inputs, int size, ActivationFunction function) {
		this->function = function;
		weights = std::vector<std::vector<float>>();
		biases = std::vector<float>();
		next = NULL;
		num_of_outputs = size;
		this->num_of_inputs = num_of_inputs;

		for (int i = 0; i < size; i++) {
			weights.push_back(std::vector<float>());
			biases.push_back((((float)rand()) / (float)RAND_MAX) + (((float)rand()) / (float)RAND_MAX) - 1);
			for (int j = 0; j < num_of_inputs; j++) {
				weights[i].push_back((((float)rand()) / (float)RAND_MAX) + (((float)rand()) / (float)RAND_MAX) - 1);
			}
		}
	}
	ANNLayer::ANNLayer(std::vector<std::vector<float>> weights, std::vector<float> biases, ActivationFunction function) {
		this->weights = std::vector<std::vector<float>>();
		this->biases = std::vector<float>();
		num_of_outputs = weights.size();
		num_of_inputs = weights[0].size();
		for (int i = 0; i < num_of_outputs; i++) {
			this->weights.push_back(std::vector<float>());
			this->biases.push_back(biases[i]);
			for (int j = 0; j < num_of_inputs; j++) {
				this->weights[i].push_back(weights[i][j]);
			}
		}
		this->function = function;
	}
	ANNLayer::~ANNLayer() {
		weights.~vector();
		biases.~vector();
		delete[] next;
	}

	std::vector<float> ANNLayer::deriveLoss(std::vector<float> err, LossFunction function) {
		switch (function) {
			case LossFunction::quadratic: return Math::Vector::MulCross(err, err);
			default: throw std::invalid_argument("could not recognize loss function");
		}
	}
	std::vector<float> ANNLayer::activate(std::vector<float> values) {
		switch (function) {
			case ActivationFunction::identity: return values;
			case ActivationFunction::sigmoid: {
				std::vector<float> return_values = std::vector<float>();
				for (int i = 0; i < values.size(); i++) {
					return_values.push_back(1 / (1 + pow(M_E, -values[i])));
					//std::cout << return_values[i] << std::endl;
				}
				return return_values;
				
			}
			case ActivationFunction::softmax: {
				std::vector<float> return_values = std::vector<float>();
				float counter = 0;
				for (unsigned int i = 0; i < values.size() ; i++) {
					return_values.push_back(powf((float)M_E, values[i]));
					counter += return_values[i];
				}
				for (unsigned int i = 0; i < return_values.size(); i++) {
					return_values[i] /= counter;
				}
				return return_values;
			}
			default: throw std::invalid_argument("could not recognize activation function!");
		}	
	}
	std::vector<float> ANNLayer::derive(std::vector<float> values) {
		std::vector<float> return_values = std::vector<float>();
		switch (function) {
			case ActivationFunction::identity: for (unsigned int i = 0; i < values.size(); i++) return_values.push_back(1); return return_values;
			case ActivationFunction::sigmoid:
				for (float i : values) {
					float sigmoid = 1 / (1 + powf((float)M_E, i));
					return_values.push_back(sigmoid * (1 - sigmoid));
				}
				return return_values;
			case ActivationFunction::softmax: {
				std::vector<float> temp = activate(values);
				for (float i : temp) {
					return_values.push_back(i * (1 - i));
				}
				return return_values;
			}
			default: throw std::invalid_argument("could not recognize activation function!");
		}
	}

	std::vector<float> ANNLayer::feedForward(std::vector<float> inputs) {
		if (inputs.size() != weights[0].size()) throw std::invalid_argument("Number of given inputs must be the same as the number of required inputs. Given inputs:" + std::to_string(inputs.size()) + " Required inputs:" + std::to_string(weights[0].size()));
		if (next == NULL) return activate(Math::Vector::Add(Math::Matrix::MulDot(weights, inputs), biases));
		return next->feedForward(activate(Math::Vector::Add(Math::Matrix::MulDot(weights, inputs), biases)));
	}

	std::vector<float> ANNLayer::backPropagate(std::vector<float> inputs, std::vector<float> target_results, LossFunction loss_function, float rate_of_change) {
		if (sizeof(inputs) != sizeof(weights[0])) throw std::invalid_argument("Number of given inputs must be the same as the number of required inputs. Given inputs:" + std::to_string(sizeof(inputs)) + " Required inputs:" + std::to_string(sizeof(weights[0])));
		if (next == NULL && sizeof(weights) != sizeof(target_results)) throw std::invalid_argument("Number of target results must be equal to the number of perceptrons on the last layer. target_results size: " + std::to_string(sizeof(target_results)) + " number of perceptrons: " + std::to_string(sizeof(weights)));
		std::vector<float> raw_values = Math::Vector::Add(Math::Matrix::MulDot(weights, inputs), biases);
		std::vector<float> results = activate(raw_values);
		std::vector<float> err;
		if (next != NULL) err = next->backPropagate(results, target_results, loss_function, rate_of_change);
		else err = Math::Vector::Sub(target_results, results);

		std::vector<std::vector<float>> weight_changes = std::vector<std::vector<float>>();
		std::vector<float> bias_changes = Math::Vector::Mul(Math::Vector::MulCross(derive(raw_values), deriveLoss(err, loss_function)), rate_of_change);

		for (float i : bias_changes) weight_changes.push_back(Math::Vector::Mul(inputs, i));

		err = Math::Matrix::MulDot(weights, err);

		weights = Math::Matrix::Sub(weights, weight_changes);
		biases = Math::Vector::Sub(biases, bias_changes);
		
		return err;
	}
	std::vector<std::vector<float>> ANNLayer::stochasticBackPropagation(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> target_results, LossFunction loss_function, float rate_of_change) {
		if (inputs[0].size() != weights[0].size()) throw std::invalid_argument("Number of given inputs must be the same as the number of required inputs. Given inputs:" + std::to_string(inputs.size()) + " Required inputs:" + std::to_string(weights[0].size()));
		if (next == NULL && weights.size() != target_results[0].size()) throw std::invalid_argument("Number of target results must be equal to the number of perceptrons on the last layer. target_results size: " + std::to_string(target_results.size()) + " number of perceptrons: " + std::to_string(weights.size()));
		std::vector<std::vector<float>> raw_values = std::vector<std::vector<float>>();
		std::vector<std::vector<float>> results = std::vector<std::vector<float>>();
		for (unsigned int i = 0; i < inputs.size(); i++) {
			raw_values.push_back(Math::Vector::Add(Math::Matrix::MulDot(weights, inputs[i]), biases));
			results.push_back(activate(raw_values[i]));
		}

		std::vector<std::vector<float>> err;
		if (next != NULL) err = next->stochasticBackPropagation(results, target_results, loss_function, rate_of_change);
		else err = Math::Matrix::Sub(target_results, results);

		std::vector<std::vector<float>> weight_changes = std::vector<std::vector<float>>();
		std::vector<float> bias_changes = Math::Vector::Mul(Math::Vector::MulCross(derive(raw_values[0]), deriveLoss(err[0], loss_function)), rate_of_change);

		for (float i : bias_changes) weight_changes.push_back(Math::Vector::Mul(inputs[0], i));

		for (unsigned int i = 1; i < err.size(); i++) {
			std::vector<float> bc = Math::Vector::Mul(Math::Vector::MulCross(derive(raw_values[i]), deriveLoss(err[i], loss_function)), rate_of_change);
			for (float j : bc) weight_changes[i] = Math::Vector::Add(weight_changes[i], Math::Vector::Mul(inputs[i], j));
			bias_changes = Math::Vector::Add(bias_changes, bc);
		}
		
		err = Math::Matrix::MulDot(weights, err);

		weights = Math::Matrix::Sub(weights, Math::Matrix::Div(weight_changes, (float)weight_changes.size()));
		biases = Math::Vector::Sub(biases, Math::Vector::Div(bias_changes, (float)bias_changes.size()));

		return err;
	}

	std::string ANNLayer::toString() {
		std::string s = "Layer Type: ANN\nActivation Function: " + enumOperations::getName(function) +"\n";
		for (int i = 0; i < num_of_outputs; i++) {
			s += "neuron number:" + std::to_string(i) + "\nbias:" + std::to_string(biases[i]) + "\n";
			for (int j = 0; j < num_of_inputs ; j++) {
				s += "weight " + std::to_string(j) + ": " + std::to_string(weights[i][j]) + ",	";
			}
			s += "\n";
		}
		if (next != NULL) {
			s += "\n" + next->toString();
		}
		return s;
	}
	std::string ANNLayer::saveString() {
		std::string s = "ANN," + enumOperations::getName(function) + "," + std::to_string(num_of_outputs);
		for (int i = 0; i < num_of_outputs; i++) {
			s += "," + std::to_string(biases[i]) + "," + std::to_string(num_of_inputs);
			for (int j = 0; j < num_of_inputs; j++) {
				s += "," + std::to_string(weights[i][j]);
			}
		}
		if (next != NULL) s += "\n" + next->saveString();
		return s;
	}
}
