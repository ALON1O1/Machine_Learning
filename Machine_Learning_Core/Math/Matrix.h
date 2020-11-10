#pragma once

namespace Math {

	class Matrix
	{
		public:
			static float** Add(float** mat, float num, int width, int height);
			static float** Add(float** mat1, float** mat2, int width, int height);
			static float** Sub(float** mat, float num, int width, int height);
			static float** Sub(float** mat1, float** mat2, int width, int height);
			static float** Mul(float** mat, float num, int width, int height);
			static float** MulCross(float** mat1, float** mat2, int width, int height);
			static float** MulDot(float** mat1, float** mat2, int mutual, int height1, int width2);
			static float* MulDot(float** mat, float* vec, int width, int height);
			static float** Transpose(float** mat, int width, int height);
			static float** Div(float** mat, float num, int width, int height);
			static float** Div(float** mat1, float** mat2, int width, int height);
	};

}
