#pragma once
#include <vector>

namespace Math {

	class Matrix
	{
		public:
			static std::vector<std::vector<float>> Add(std::vector<std::vector<float>>, float);
			static std::vector<std::vector<float>> Add(std::vector<std::vector<float>>, std::vector<std::vector<float>>);
			static std::vector<std::vector<float>> Sub(std::vector<std::vector<float>>, float);
			static std::vector<std::vector<float>> Sub(std::vector<std::vector<float>>, std::vector<std::vector<float>>);
			static std::vector<std::vector<float>> Mul(std::vector<std::vector<float>>, float);
			static std::vector<std::vector<float>> MulCross(std::vector<std::vector<float>>, std::vector<std::vector<float>>);
			static std::vector<std::vector<float>> MulDot(std::vector<std::vector<float>>, std::vector<std::vector<float>>);
			static std::vector<float> MulDot(std::vector<std::vector<float>>, std::vector<float>);
			static std::vector<std::vector<float>> Transpose(std::vector<std::vector<float>>);
			static std::vector<std::vector<float>> Div(std::vector<std::vector<float>>, float);
			static std::vector<std::vector<float>> Div(std::vector<std::vector<float>>, std::vector<std::vector<float>>);
	};

}
