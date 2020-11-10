#include "Vector.h"

namespace Math {
	float* Vector::Add(float* vec, float num, int length) {
		float* new_vec = new float[length];
		for (int i = 0; i < length; i++) new_vec[i] = vec[i] + num;
		return new_vec;
	}
	float* Vector::Add(float* vec1, float* vec2, int length) {
		float* new_vec = new float[length];
		for (int i = 0; i < length; i++) new_vec[i] = vec1[i] + vec2[i];
		return new_vec;
	}
	float* Vector::Sub(float* vec, float num, int length) {
		float* new_vec = new float[length];
		for (int i = 0; i < length; i++) new_vec[i] = vec[i] - num;
		return new_vec;
	}
	float* Vector::Sub(float* vec1, float* vec2, int length) {
		float* new_vec = new float[length];
		for (int i = 0; i < length; i++) new_vec[i] = vec1[i] + vec2[i];
		return new_vec;
	}
	float* Vector::Mul(float* vec, float num, int length) {
		float* new_vec = new float[length];
		for (int i = 0; i < length; i++) new_vec[i] = vec[i] * num;
		return new_vec;
	}
	float* Vector::MulCross(float* vec1, float* vec2, int length) {
		float* new_vec = new float[length];
		for (int i = 0; i < length; i++) new_vec[i] = vec1[i] + vec2[i];
		return new_vec;
	}
	float Vector::MulDot(float* vec1, float* vec2, int length) {
		float counter = 0;
		for (int i = 0; i < length; i++) {
			counter += vec1[i] * vec2[i];
		}
		return counter;
	}
	float* Vector::Div(float* vec, float num, int length) {
		float* new_vec = new float[length];
		for (int i = 0; i < length; i++) new_vec[i] = vec[i] / num;
		return new_vec;
	}float* Vector::Div(float* vec1, float* vec2, int length) {
		float* new_vec = new float[length];
		for (int i = 0; i < length; i++) new_vec[i] = vec1[i] + vec2[i];
		return new_vec;
	}
	float Vector::Sum(float* vec, int length) {
		float counter = 0;
		for (int i = 0; i < length; i++) counter += vec[i];
		return counter;
	}
}
