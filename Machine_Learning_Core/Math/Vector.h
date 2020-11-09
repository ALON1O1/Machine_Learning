#pragma once

namespace Math {
	class Vector
	{
		public:
			static float* Add(float*, float);
			static float* Add(float*, float*);
			static float* Sub(float*, float);
			static float* Sub(float*, float*);
			static float* Mul(float*, float);
			static float* MulCross(float*, float*);
			static float MulDot(float*, float*);
			static float* Div(float*, float);
			static float* Div(float*, float*);
			static float Sum(float*);
	};
}

