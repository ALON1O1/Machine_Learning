#pragma once
#include <vector>

namespace Math {

	class Matrix
	{
		public:
			static std::vector<std::vector<float>> Add(std::vector<std::vector<float>> mat, float num);
			static std::vector<std::vector<float>> Add(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);
			static std::vector<std::vector<float>> Sub(std::vector<std::vector<float>> mat, float num);
			static std::vector<std::vector<float>> Sub(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);
			static std::vector<std::vector<float>> Mul(std::vector<std::vector<float>> mat, float num);
			static std::vector<std::vector<float>> MulCross(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);
			static std::vector<std::vector<float>> MulDot(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);
			static std::vector<float> MulDot(std::vector<std::vector<float>> mat, std::vector<float> vec);
			static std::vector<std::vector<float>> Transpose(std::vector<std::vector<float>> mat);
			static std::vector<std::vector<float>> Div(std::vector<std::vector<float>> mat, float num);
			static std::vector<std::vector<float>> Div(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);
	};

}
