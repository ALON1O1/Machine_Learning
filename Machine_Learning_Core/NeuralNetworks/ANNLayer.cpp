#define _USE_MATH_DEFINES
#include "ANNLayer.h"
#include <math.h>
#include <stdexcept>

namespace NeuralNetwork {

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
					return_values[i] = 1 / (1 + powf(M_E, -values[i]));
				}
				return return_values;
				
			}
			case ActivationFunction::softmax: {
				const int size = sizeof(values);
				static float return_values[size];
				float counter = 0;
				for (int i = 0; i < size; i++) {
					return_values[i] = powf(M_E, values[i]);
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
					float sigmoid = 1 / (1 + powf(M_E, values[i]));
					return_values[i] = sigmoid * (1 - sigmoid);
				}
				return return_values;
			case ActivationFunction::softmax:
				float* temp = activate(values);
				for (int i = 0; i < size; i++) {
					return_values[i] = temp[i] * (1 - temp[i]);
				}
				return return_values;
			default: return NULL;
		}
	}

	/*void ANNLayer::feedForward(std::vector<float> inputs, std::vector<float>& results) {
		if (inputs.size() != weights[0].size()) throw std::invalid_argument("Number of given inputs must be the same as the number of required inputs. Given inputs:" + std::to_string(inputs.size()) + " Required inputs:" + std::to_string(weights[0].size()));
		if ()
	}*/
}
