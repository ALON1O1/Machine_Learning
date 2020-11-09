#include "Matrix.h"
#include "Vector.h"

namespace Math {
	float** Matrix::Add(float** mat, float num) {
		static float** new_mat = new float*[sizeof(mat)];
		for (int i = 0; i < sizeof(mat); i++) {
			new_mat[i] = new float[sizeof(mat[i])];
			for (int j = 0; j < sizeof(mat[i]); i++) {
				new_mat[i][j] = mat[i][j] + num;
			}
		}
		return new_mat;
	}
	float** Matrix::Add(float** mat1, float** mat2) {
		static float** new_mat = new float* [sizeof(mat1)];
		for (int i = 0; i < sizeof(mat1); i++) {
			new_mat[i] = new float[sizeof(mat1[i])];
			for (int j = 0; j < sizeof(mat1[i]); i++) {
				new_mat[i][j] = mat1[i][j] + mat2[i][j];
			}
		}
		return new_mat;
	}
	float** Matrix::Sub(float** mat, float num) {
		static float** new_mat = new float* [sizeof(mat)];
		for (int i = 0; i < sizeof(mat); i++) {
			new_mat[i] = new float[sizeof(mat[i])];
			for (int j = 0; j < sizeof(mat[i]); i++) {
				new_mat[i][j] = mat[i][j] - num;
			}
		}
		return new_mat;
	}
	float** Matrix::Sub(float** mat1, float** mat2) {
		static float** new_mat = new float* [sizeof(mat1)];
		for (int i = 0; i < sizeof(mat1); i++) {
			new_mat[i] = new float[sizeof(mat1[i])];
			for (int j = 0; j < sizeof(mat1[i]); i++) {
				new_mat[i][j] = mat1[i][j] - mat2[i][j];
			}
		}
		return new_mat;
	}
	float** Matrix::Mul(float** mat, float num) {
		static float** new_mat = new float* [sizeof(mat)];
		for (int i = 0; i < sizeof(mat); i++) {
			new_mat[i] = new float[sizeof(mat[i])];
			for (int j = 0; j < sizeof(mat[i]); i++) {
				new_mat[i][j] = mat[i][j] * num;
			}
		}
		return new_mat;
	}
	float** Matrix::MulCross(float** mat1, float** mat2) {
		static float** new_mat = new float* [sizeof(mat1)];
		for (int i = 0; i < sizeof(mat1); i++) {
			new_mat[i] = new float[sizeof(mat1[i])];
			for (int j = 0; j < sizeof(mat1[i]); i++) {
				new_mat[i][j] = mat1[i][j] + mat2[i][j];
			}
		}
		return new_mat;
	}
	float** Matrix::MulDot(float** mat1, float** mat2) {
		float** temp = Transpose(mat2);
		float** new_mat = new float* [sizeof(mat1)];
		for (int i = 0; i < sizeof(new_mat); i++) {
			new_mat[i] = new float[sizeof(temp)];
			for (int j = 0; j < sizeof(new_mat[i]); j++) {
				new_mat[i][j] = Vector::MulDot(mat1[i], temp[j]);
			}
		}
		return new_mat;
	}
	float* Matrix::MulDot(float** mat, float* vec) {
		float* new_vec = new float[sizeof(mat)];
		for (int i = 0; i < sizeof(new_vec); i++) {
			new_vec[i] = Vector::MulDot(mat[i], vec);
		}
		return new_vec;
	}
	float** Matrix::Transpose(float** mat) {
		float** new_mat = new float* [sizeof(mat[0])];
		for (int i = 0; i < sizeof(new_mat); i++) {
			new_mat[i] = new float[sizeof(mat)];
			for (int j = 0; j < sizeof(new_mat[i]); j++) {
				new_mat[i][j] = mat[j][i];
			}
		}
		return new_mat;
	}
	float** Matrix::Div(float** mat, float num) {
		static float** new_mat = new float* [sizeof(mat)];
		for (int i = 0; i < sizeof(mat); i++) {
			new_mat[i] = new float[sizeof(mat[i])];
			for (int j = 0; j < sizeof(mat[i]); i++) {
				new_mat[i][j] = mat[i][j] / num;
			}
		}
		return new_mat;
	}
	float** Matrix::Div(float** mat1, float** mat2) {
		static float** new_mat = new float* [sizeof(mat1)];
		for (int i = 0; i < sizeof(mat1); i++) {
			new_mat[i] = new float[sizeof(mat1[i])];
			for (int j = 0; j < sizeof(mat1[i]); i++) {
				new_mat[i][j] = mat1[i][j] / mat2[i][j];
			}
		}
		return new_mat;
	}
}