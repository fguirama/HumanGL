#include "class/Matrix4.hpp"
#include "class/Vector4.hpp"

Matrix4 multiply_matrices(Matrix4 first, Matrix4 second) {
	int res[4][4];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += first.matrix[i][k] * second.matrix[k][j];
			}
			res[i][j] = sum;
		}
	}

	return Matrix4(res);
}

Vector4 multiply(Matrix4 mat, Vector4 init_vec) {
	double vec[4] = {init_vec.vector[0], init_vec.vector[1], init_vec.vector[2], 1};
	double res[4];

	for (int i = 0; i < 4; i++) {
		int sum = 0;
		for (int j = 0; j < 4; j++) {
			sum += mat.matrix[i][j] * vec[j];
		}
		res[i] = sum;
	}

	return Vector4(res);
}
