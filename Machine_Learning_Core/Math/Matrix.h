#pragma once

namespace Math {

	class Matrix
	{
		public:
			float** Add(float** mat, float num);
			float** Add(float** mat1, float** mat2);
			float** Sub(float** mat, float num);
			float** Sub(float** mat1, float** mat2);
			float** Mul(float** mat, float num);
			float** MulCross(float** mat1, float** mat2);
			float** MulDot(float** mat1, float** mat2);
			float* MulDot(float** mat, float* vec);
			float** Transpose(float** mat);
			float** Div(float** mat, float num);
			float** Div(float** mat1, float** mat2);
	};

}
