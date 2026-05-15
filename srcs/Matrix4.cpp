#include "../incs/Matrix4.hpp"
#include <iostream>

Matrix4::Matrix4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = 0;
        }
    }
}

Matrix4::Matrix4(int mat[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = mat[i][j];
        }
    }
}

Matrix4::~Matrix4() {}

Matrix4::Matrix4(Matrix4 const& copy) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = copy.matrix[i][j];
        }
    }
}

Matrix4& Matrix4::operator=(Matrix4 const& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }

    return *this;
}

void Matrix4::identity() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
    }
}

void Matrix4::translation(int x, int y, int z) {
    identity();
    matrix[0][3] = x;
    matrix[1][3] = y;
    matrix[2][3] = z;
}

void Matrix4::scaling(int x, int y, int z) {
    matrix[0][0] = x;
    matrix[1][1] = y;
    matrix[2][2] = z;
    matrix[3][3] = 1;
}

void Matrix4::rotation(float angle, Axis axis) {
    identity();
    double cosinus = cos(angle);
    double sinus = sin(angle);
    switch (axis) {
        case X:
            matrix[1][1] = cosinus;
            matrix[2][2] = cosinus;
            matrix[2][1] = sinus;
            matrix[1][2] = -sinus;
            break;
        case Y:
            matrix[0][0] = cosinus;
            matrix[0][2] = sinus;
            matrix[2][0] = -sinus;
            matrix[2][2] = cosinus;
            break;
        case Z:
            matrix[0][0] = cosinus;
            matrix[1][1] = cosinus;
            matrix[1][0] = sinus;
            matrix[0][1] = -sinus;
    }
}
