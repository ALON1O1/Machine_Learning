#pragma once
#include "Layer.h"
#include <vector>

namespace NeuralNetwork {
	class ANNLayer: public Layer
	{
		private:
			ActivationFunction function;
			std::vector<std::vector<float>> weights;
			std::vector<float> biases;

			std::vector<float> deriveLoss(std::vector<float>, LossFunction);
			std::vector<float> activate(std::vector<float>);
			std::vector<float> derive(std::vector<float>);

		public:
			ANNLayer(int, int, ActivationFunction);
			ANNLayer(std::vector<std::vector<float>>, std::vector<float>, ActivationFunction);
			~ANNLayer();
			std::vector<float> feedForward(std::vector<float>) override;

			std::vector<float> backPropagate(std::vector<float>, std::vector<float>, LossFunction, float) override;
			std::vector< std::vector<float>> stochasticBackPropagation(std::vector<std::vector<float>>, std::vector< std::vector<float>>, LossFunction, float) override;
			
			std::string saveString() override;
			std::string toString();
	};
}

