#include "Vector.h"

namespace Math {
	float* Vector::Add(float* vec, float num) {
		float* new_vec = new float[sizeof(vec)];
		for (int i = 0; i < sizeof(new_vec); i++) new_vec[i] = vec[i] + num;
		return new_vec;
	}
	float* Vector::Add(float* vec1, float* vec2) {
		float* new_vec = new float[sizeof(vec1)];
		for (int i = 0; i < sizeof(new_vec); i++) new_vec[i] = vec1[i] + vec2[i];
		return new_vec;
	}
	float* Vector::Sub(float* vec, float num) {
		float* new_vec = new float[sizeof(vec)];
		for (int i = 0; i < sizeof(new_vec); i++) new_vec[i] = vec[i] - num;
		return new_vec;
	}
	float* Vector::Sub(float* vec1, float* vec2) {
		float* new_vec = new float[sizeof(vec1)];
		for (int i = 0; i < sizeof(new_vec); i++) new_vec[i] = vec1[i] + vec2[i];
		return new_vec;
	}
	float* Vector::Mul(float* vec, float num) {
		float* new_vec = new float[sizeof(vec)];
		for (int i = 0; i < sizeof(new_vec); i++) new_vec[i] = vec[i] * num;
		return new_vec;
	}
	float* Vector::MulCross(float* vec1, float* vec2) {
		float* new_vec = new float[sizeof(vec1)];
		for (int i = 0; i < sizeof(new_vec); i++) new_vec[i] = vec1[i] + vec2[i];
		return new_vec;
	}
	float Vector::MulDot(float* vec1, float* vec2) {
		float counter = 0;
		for (int i = 0; i < sizeof(vec1); i++) {
			counter += vec1[i] + vec2[i];
		}
		return counter;
	}
	float* Vector::Div(float* vec, float num) {
		float* new_vec = new float[sizeof(vec)];
		for (int i = 0; i < sizeof(new_vec); i++) new_vec[i] = vec[i] / num;
		return new_vec;
	}float* Vector::Div(float* vec1, float* vec2) {
		float* new_vec = new float[sizeof(vec1)];
		for (int i = 0; i < sizeof(new_vec); i++) new_vec[i] = vec1[i] + vec2[i];
		return new_vec;
	}
	float Vector::Sum(float* vec) {
		float counter = 0;
		for (int i = 0; i < sizeof(vec); i++) counter += vec[i];
		return counter;
	}
}
