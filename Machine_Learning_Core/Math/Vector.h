#pragma once
#include <vector>

namespace Math {
	class Vector
	{
		public:
			static std::vector<float> Add(std::vector<float>, float);
			static std::vector<float> Add(std::vector<float>, std::vector<float>);
			static std::vector<float> Sub(std::vector<float>, float num);
			static std::vector<float> Sub(std::vector<float>, std::vector<float>);
			static std::vector<float> Mul(std::vector<float>, float);
			static std::vector<float> MulCross(std::vector<float>, std::vector<float>);
			static float MulDot(std::vector<float>, std::vector<float>);
			static std::vector<float> Div(std::vector<float>, float);
			static std::vector<float> Div(std::vector<float>, std::vector<float>);
			static float Sum(std::vector<float>);
	};
}

