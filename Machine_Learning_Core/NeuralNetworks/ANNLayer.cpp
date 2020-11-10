#define _USE_MATH_DEFINES
#include "ANNLayer.h"
#include <math.h>
#include <stdexcept>
#include "..\Math\Vector.h"
#include "..\Math\Matrix.h"

namespace NeuralNetwork {

	ANNLayer::ANNLayer(int num_of_inputs, int size, ActivationFunction function) {
		this->function = function;
		weights = new float*[size];
		biases = new float[size];
		next = NULL;
		num_of_outputs = size;
		this->num_of_inputs = num_of_inputs;

		for (int i = 0; i < size; i++) {
			weights[i] = new float[num_of_inputs];
			biases[i] = (((float)rand()) / (float)RAND_MAX) + (((float)rand()) / (float)RAND_MAX) - 1;
			for (int j = 0; j < num_of_inputs; j++) {
				weights[i][j] = (((float)rand()) / (float)RAND_MAX) + (((float)rand()) / (float)RAND_MAX) - 1;
			}
		}
	}
	ANNLayer::ANNLayer(std::vector<std::vector<float>> weights, std::vector<float> biases, ActivationFunction function) {
		this->weights = new float*[weights.size()];
		this->biases = new float[biases.size()];
		num_of_outputs = weights.size();
		num_of_inputs = weights[0].size();
		for (int i = 0; i < num_of_outputs; i++) {
			this->weights[i] = new float[weights[i].size()];
			this->biases[i] = biases[i];
			for (int j = 0; j < num_of_inputs; j++) {
				this->weights[i][j] = weights[i][j];
			}
		}
		this->function = function;
	}
	ANNLayer::~ANNLayer() {
		delete[] weights;
		delete[] biases;
		delete[] next;
	}

	float ANNLayer::deriveLoss(float err, LossFunction function) {
		switch (function) {
			case LossFunction::quadratic: return err * 2;
			default: return 0;
		}
	}
	float* ANNLayer::activate(float* values) {
		switch (function) {
			case ActivationFunction::identity: return values;
			case ActivationFunction::sigmoid: {
				const int size = sizeof(values);
				static float return_values[size];
				for (int i = 0; i < size; i++) {
					return_values[i] = 1 / (1 + powf((float)M_E, -values[i]));
				}
				return return_values;
				
			}
			case ActivationFunction::softmax: {
				const int size = sizeof(values);
				static float return_values[size];
				float counter = 0;
				for (int i = 0; i < size; i++) {
					return_values[i] = powf((float)M_E, values[i]);
					counter += return_values[i];
				}
				for (int i = 0; i < size; i++) {
					return_values[i] /= counter;
				}
				return return_values;
			}
			default: return NULL;
		}	
	}
	float* ANNLayer::derive(float* values) {
		const int size = sizeof(values);
		static float return_values[size];
		switch (function) {
			case ActivationFunction::identity: for (int i = 0; i < size; i++) return_values[i] = 1; return return_values;
			case ActivationFunction::sigmoid:
				for (int i = 0; i < size; i++) {
					float sigmoid = 1 / (1 + powf((float)M_E, values[i]));
					return_values[i] = sigmoid * (1 - sigmoid);
				}
				return return_values;
			case ActivationFunction::softmax: {
				float* temp = activate(values);
				for (int i = 0; i < size; i++) {
					return_values[i] = temp[i] * (1 - temp[i]);
				}
				return return_values;
			}
			default: return NULL;
		}
	}

	float* ANNLayer::feedForward(float* inputs) {
		if (sizeof(inputs) != sizeof(weights[0])) throw std::invalid_argument("Number of given inputs must be the same as the number of required inputs. Given inputs:" + std::to_string(sizeof(inputs)) + " Required inputs:" + std::to_string(sizeof(weights[0])));
		if (next == NULL) return activate(inputs);
		return next->feedForward(inputs);
	}

	float* ANNLayer::backPropagate(float* inputs, float* target_results, LossFunction loss_function, float rate_of_change) {
		if (sizeof(inputs) != sizeof(weights[0])) throw std::invalid_argument("Number of given inputs must be the same as the number of required inputs. Given inputs:" + std::to_string(sizeof(inputs)) + " Required inputs:" + std::to_string(sizeof(weights[0])));
		if (next == NULL && sizeof(weights) != sizeof(target_results)) throw std::invalid_argument("Number of target results must be equal to the number of perceptrons on the last layer. target_results size: " + std::to_string(sizeof(target_results)) + " number of perceptrons: " + std::to_string(sizeof(weights)));
		float* raw_values = Math::Vector::Add(Math::Matrix::MulDot(weights, inputs), biases);
		float* results = activate(raw_values);
		float* err;
		if (next != NULL) err = next->backPropagate(results, target_results, loss_function, rate_of_change);
		else err = Math::Vector::Sub(target_results, results);

		float* weight_changes[sizeof(weights)];
		float* bias_changes = derive(raw_values);

		for (int i = 0; i < sizeof(weight_changes); i++) {
			bias_changes[i] *= deriveLoss(err[i], loss_function) * -rate_of_change;
			weight_changes[i] = Math::Vector::Mul(inputs, bias_changes[i]);
		}

		err = Math::Matrix::MulDot(weights, err);

		weights = Math::Matrix::Sub(weights, weight_changes);
		biases = Math::Vector::Sub(biases, bias_changes);
		
		return err;
	}
	float** ANNLayer::stochasticBackPropagation(float** inputs, float** target_results, LossFunction loss_function, float rate_of_change) {
		if (sizeof(inputs[0]) != sizeof(weights[0])) throw std::invalid_argument("Number of given inputs must be the same as the number of required inputs. Given inputs:" + std::to_string(sizeof(inputs)) + " Required inputs:" + std::to_string(sizeof(weights[0])));
		if (next == NULL && sizeof(weights) != sizeof(target_results[0])) throw std::invalid_argument("Number of target results must be equal to the number of perceptrons on the last layer. target_results size: " + std::to_string(sizeof(target_results)) + " number of perceptrons: " + std::to_string(sizeof(weights)));
		float* raw_values[sizeof(inputs)];
		float* results[sizeof(inputs)];
		for (int i = 0; i < sizeof(results); i++) {
			raw_values[i] = Math::Vector::Add(Math::Matrix::MulDot(weights, inputs[i]), biases);
			results[i] = activate(raw_values[i]);
		}

		float** err;
		if (next != NULL) err = next->stochasticBackPropagation(results, target_results, loss_function, rate_of_change);
		else err = Math::Matrix::Sub(target_results, results);

		float* weight_changes[sizeof(weights)];
		float* bias_changes = derive(raw_values[0]);

		for (int i = 0; i < sizeof(weight_changes); i++) {
			bias_changes[i] *= deriveLoss(err[0][i], loss_function) * -rate_of_change;
			weight_changes[i] = Math::Vector::Mul(inputs[0], bias_changes[i]);
		}

		for (int i = 1; i < sizeof(err); i++) {
			float* bc = derive(raw_values[i]);
			for (int j = 0; j < sizeof(weight_changes); j++) {
				bc[j] *= deriveLoss(err[i][j], loss_function) * -rate_of_change;
				weight_changes[i] = Math::Vector::Div(Math::Vector::Add(weight_changes[i], Math::Vector::Mul(inputs[i], bc[j])), sizeof(err));
			}
			bias_changes = Math::Vector::Div(Math::Vector::Add(bias_changes, bc), sizeof(err));
		}
		
		err = Math::Matrix::MulDot(weights, err);

		weights = Math::Matrix::Sub(weights, weight_changes);
		biases = Math::Vector::Sub(biases, bias_changes);

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
