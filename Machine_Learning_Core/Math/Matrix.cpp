#include "Matrix.h"
#include "Vector.h"
#include <stdexcept>
#include <string>

namespace Math {
	std::vector<std::vector<float>> Matrix::Add(std::vector<std::vector<float>> mat, float num) {
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (std::vector<float> i : mat) new_mat.push_back(Vector::Add(i, num));
		return new_mat;
	}
	std::vector<std::vector<float>> Matrix::Add(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2) {
		if (mat1.size() != mat2.size()) throw new std::invalid_argument("mat1 size is different that mat2 size! mat1:" + std::to_string(mat1.size()) + " , mat2:" + std::to_string(mat2.size()));
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (int i = 0; i < mat1.size(); i++) new_mat.push_back(Vector::Add(mat1[i], mat2[i]));
		return new_mat;
	}
	std::vector<std::vector<float>> Matrix::Sub(std::vector<std::vector<float>> mat, float num) {
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (std::vector<float> i : mat) new_mat.push_back(Vector::Sub(i, num));
		return new_mat;
	}
	std::vector<std::vector<float>> Matrix::Sub(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2) {
		if (mat1.size() != mat2.size()) throw new std::invalid_argument("mat1 size is different that mat2 size! mat1:" + std::to_string(mat1.size()) + " , mat2:" + std::to_string(mat2.size()));
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (int i = 0; i < mat1.size(); i++) new_mat.push_back(Vector::Sub(mat1[i], mat2[i]));
		return new_mat;
	}
	std::vector<std::vector<float>> Matrix::Mul(std::vector<std::vector<float>> mat, float num) {
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (std::vector<float> i : mat) new_mat.push_back(Vector::Mul(i, num));
		return new_mat;
	}
	std::vector<std::vector<float>> Matrix::MulCross(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2) {
		if (mat1.size() != mat2.size()) throw new std::invalid_argument("mat1 size is different that mat2 size! mat1:" + std::to_string(mat1.size()) + " , mat2:" + std::to_string(mat2.size()));
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (int i = 0; i < mat1.size(); i++) new_mat.push_back(Vector::MulCross(mat1[i], mat2[i]));
		return new_mat;
	}
	std::vector<std::vector<float>> Matrix::MulDot(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2) {
		std::vector<std::vector<float>> temp = Transpose(mat2);
		if (mat1.size() != temp.size()) throw new std::invalid_argument("mat1 size is different that mat2 size! mat1:" + std::to_string(mat1.size()) + " , mat2:" + std::to_string(temp.size()));
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (int i = 0; i < mat1.size(); i++) {
			new_mat.push_back(std::vector<float>());
			for (int j = 0; j < temp.size(); j++) {
				new_mat[i].push_back(Vector::MulDot(mat1[i], temp[j]));
			}
		}
		return new_mat;
	}
	std::vector<float> Matrix::MulDot(std::vector<std::vector<float>> mat, std::vector<float> vec) {
		std::vector<float> new_vec = std::vector<float>();
		for (std::vector<float> i : mat) new_vec.push_back(Vector::MulDot(i, vec));
		return new_vec;
	}
	std::vector<std::vector<float>> Matrix::Transpose(std::vector<std::vector<float>> mat) {
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (int i = 0; i < mat[0].size(); i++) {
			new_mat.push_back(std::vector<float>());
			for (int j = 0; j < mat.size(); j++) {
				new_mat[i].push_back(mat[j][i]);
			}
		}
		return new_mat;
	}
	std::vector<std::vector<float>> Matrix::Div(std::vector<std::vector<float>> mat, float num) {
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (std::vector<float> i : mat) new_mat.push_back(Vector::Div(i, num));
		return new_mat;
	}
	std::vector<std::vector<float>> Matrix::Div(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2) {
		if (mat1.size() != mat2.size()) throw new std::invalid_argument("mat1 size is different that mat2 size! mat1:" + std::to_string(mat1.size()) + " , mat2:" + std::to_string(mat2.size()));
		std::vector<std::vector<float>> new_mat = std::vector<std::vector<float>>();
		for (int i = 0; i < mat1.size(); i++) new_mat.push_back(Vector::Div(mat1[i], mat2[i]));
		return new_mat;
	}
}