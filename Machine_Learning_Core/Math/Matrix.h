#pragma once

namespace Math {

	class Matrix
	{
		public:
			static float** Add(float** mat, float num);
			static float** Add(float** mat1, float** mat2);
			static float** Sub(float** mat, float num);
			static float** Sub(float** mat1, float** mat2);
			static float** Mul(float** mat, float num);
			static float** MulCross(float** mat1, float** mat2);
			static float** MulDot(float** mat1, float** mat2);
			static static float* MulDot(float** mat, float* vec);
			static float** Transpose(float** mat);
			static float** Div(float** mat, float num);
			static float** Div(float** mat1, float** mat2);
	};

}
