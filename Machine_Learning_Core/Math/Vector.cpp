#include "Vector.h"
#include <stdexcept>
#include <string>

namespace Math {
	std::vector<float> Vector::Add(std::vector<float> vec, float num) {
		std::vector<float> new_vec = std::vector<float>();
		for (float i : vec) new_vec.push_back(i + num);
		return new_vec;
	}
	std::vector<float> Vector::Add(std::vector<float> vec1, std::vector<float> vec2) {
		if (vec1.size() != vec2.size()) throw std::invalid_argument("Add: vec1 size must be same as vec2 size! vec1:" + std::to_string(vec1.size()) + ", vec2:" + std::to_string(vec2.size()));
		std::vector<float> new_vec = std::vector<float>();
		for (int i = 0; i < vec1.size(); i++) new_vec.push_back(vec1[i] + vec2[i]);
		return new_vec;
	}
	std::vector<float> Vector::Sub(std::vector<float> vec, float num) {
		std::vector<float> new_vec = std::vector<float>();
		for (float i : vec) new_vec.push_back(i - num);
		return new_vec;
	}
	std::vector<float> Vector::Sub(std::vector<float> vec1, std::vector<float> vec2) {
		if (vec1.size() != vec2.size()) throw std::invalid_argument("Sub: vec1 size must be same as vec2 size! vec1:" + std::to_string(vec1.size()) + ", vec2:" + std::to_string(vec2.size()));
		std::vector<float> new_vec = std::vector<float>();
		for (int i = 0; i < vec1.size(); i++) new_vec.push_back(vec1[i] - vec2[i]);
		return new_vec;
	}
	std::vector<float> Vector::Mul(std::vector<float> vec, float num) {
		std::vector<float> new_vec = std::vector<float>();
		for (float i : vec) new_vec.push_back(i * num);
		return new_vec;
	}
	std::vector<float> Vector::MulCross(std::vector<float> vec1, std::vector<float> vec2) {
		if (vec1.size() != vec2.size()) throw std::invalid_argument("MulCross: vec1 size must be same as vec2 size! vec1:" + std::to_string(vec1.size()) + ", vec2:" + std::to_string(vec2.size()));
		std::vector<float> new_vec = std::vector<float>();
		for (int i = 0; i < vec1.size(); i++) new_vec.push_back(vec1[i] * vec2[i]);
		return new_vec;
	}
	float Vector::MulDot(std::vector<float> vec1, std::vector<float> vec2) {
		if (vec1.size() != vec2.size()) throw std::invalid_argument("MulDot: vec1 size must be same as vec2 size! vec1:" + std::to_string(vec1.size()) + ", vec2:" + std::to_string(vec2.size()));
		float counter = 0;
		for (int i = 0; i < vec1.size(); i++) {
			counter += vec1[i] * vec2[i];
		}
		return counter;
	}
	std::vector<float> Vector::Div(std::vector<float> vec, float num) {
		std::vector<float> new_vec = std::vector<float>();
		for (float i : vec) new_vec.push_back(i / num);
		return new_vec;
	}
	std::vector<float> Vector::Div(std::vector<float> vec1, std::vector<float> vec2) {
		if (vec1.size() != vec2.size()) throw std::invalid_argument("Div: vec1 size must be same as vec2 size! vec1:" + std::to_string(vec1.size()) + ", vec2:" + std::to_string(vec2.size()));
		std::vector<float> new_vec = std::vector<float>();
		for (int i = 0; i < vec1.size(); i++) new_vec.push_back(vec1[i] / vec2[i]);
		return new_vec;
	}
	float Vector::Sum(std::vector<float> vec) {
		float counter = 0;
		for (float i : vec) counter += i;
		return counter;
	}
}
