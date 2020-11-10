#pragma once

namespace Math {
	class Vector
	{
		public:
			static float* Add(float*, float, int length);
			static float* Add(float*, float*, int length);
			static float* Sub(float*, float, int length);
			static float* Sub(float*, float*, int length);
			static float* Mul(float*, float, int length);
			static float* MulCross(float*, float*, int length);
			static float MulDot(float*, float*, int length);
			static float* Div(float*, float, int length);
			static float* Div(float*, float*, int length);
			static float Sum(float*, int length);
	};
}

