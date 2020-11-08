#include "ANNLayer.h"

namespace NeuralNetwork {
	float deriveLoss(float err, LossFunction function) {
		switch (function) {
			case quadratic: return err * 2;
			default: return 0;
		}
	}
}
