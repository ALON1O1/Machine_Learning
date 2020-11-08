#define _USE_MATH_DEFINES
#include "ANNLayer.h"
#include <math.h>

namespace NeuralNetwork {
	float ANNLayer::deriveLoss(float err, LossFunction function) {
		switch (function) {
			case LossFunction::quadratic: return err * 2;
			default: return 0;
		}
	}
	bool ANNLayer::activate(std::vector<float> values, std::vector<float>& return_values) {
		switch (function) {
			case ActivationFunction::identity: return_values = values; return true;
			case ActivationFunction::sigmoid:
				for (float v : values) {
					return_values.push_back(1 / (1 + pow(M_E, -v)));
				}
				return true;
			case ActivationFunction::softmax:
				float counter = 0;
				for (int i = 0; i < values.size(); i++) {
					return_values.push_back(pow(M_E, values[i]));
					counter += return_values[i];
				}
				for (int i = 0; i < return_values.size(); i++) {
					return_values[i] /= counter;
				}
				return true;
			default: return false;
		}	
	}
	bool ANNLayer::derive(std::vector<float> values, std::vector<float>& return_values) {
		switch (function) {
			case ActivationFunction::identity: for (float v : values) return_values.push_back(1); return true;
			case ActivationFunction::sigmoid:
				for (float v : values) {
					float sigmoid = 1 / (1 + pow(M_E, -v));
					return_values.push_back(sigmoid * (1 - sigmoid));
				}
				return true;
			case ActivationFunction::softmax:
				activate(values, return_values);
				for (int i = 0; i < return_values.size(); i++) {
					return_values[i] = return_values[i] * (1 - return_values[i]);
				}
				return true;
			default: return false;
		}
	}

}
