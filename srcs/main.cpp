#include "../incs/humanGL.h"
#include <iostream>

static void print_matrix(Matrix4 mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

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

int main() {
    Matrix4 m = Matrix4();
    MatrixStack stack = MatrixStack();
    stack.push(m);
    m.identity();
    stack.push(m);
    print_matrix(stack.pop());
    std::cout << "\n";
    print_matrix(stack.pop());
    int m1[4][4] = {{1, 2, 3, 0}, {2, 3, 4, 4}, {1, 2, 3, 3}, {3, 4, 6, 5}};

    Matrix4 m2 = Matrix4(m1);
    Matrix4 m3 = multiply_matrices(m, m1);
    // print_matrix(m);
}