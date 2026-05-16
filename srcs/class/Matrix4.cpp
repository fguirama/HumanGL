#include "class/Matrix4.hpp"
#include <cmath>

Matrix4::Matrix4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->_matrix[i][j] = 0;
        }
    }
}

Matrix4::Matrix4(const double mat[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->_matrix[i][j] = mat[i][j];
        }
    }
}

Matrix4::~Matrix4() {}

Matrix4::Matrix4(Matrix4 const& copy) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->_matrix[i][j] = copy._matrix[i][j];
        }
    }
}

Matrix4& Matrix4::operator=(Matrix4 const& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this->_matrix[i][j] = other._matrix[i][j];
            }
        }
    }

    return *this;
}

void Matrix4::identity() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j)
                this->_matrix[i][j] = 1;
            else
                this->_matrix[i][j] = 0;
        }
    }
}

void Matrix4::translation(double x, double y, double z) {
    identity();
    this->_matrix[0][3] = x;
    this->_matrix[1][3] = y;
    this->_matrix[2][3] = z;
}

void Matrix4::scaling(double x, double y, double z) {
    identity();
    this->_matrix[0][0] = x;
    this->_matrix[1][1] = y;
    this->_matrix[2][2] = z;
}

void Matrix4::rotation(double angle, Axis axis) {
    identity();
    double cosinus = std::cos(angle);
    double sinus = std::sin(angle);
    switch (axis) {
        case X:
            this->_matrix[1][1] = cosinus;
            this->_matrix[2][2] = cosinus;
            this->_matrix[2][1] = sinus;
            this->_matrix[1][2] = -sinus;
            break;
        case Y:
            this->_matrix[0][0] = cosinus;
            this->_matrix[0][2] = sinus;
            this->_matrix[2][0] = -sinus;
            this->_matrix[2][2] = cosinus;
            break;
        case Z:
            this->_matrix[0][0] = cosinus;
            this->_matrix[1][1] = cosinus;
            this->_matrix[1][0] = sinus;
            this->_matrix[0][1] = -sinus;
    }
}

Matrix4 Matrix4::operator*(Matrix4 const& other) const {
    Matrix4 res;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += this->_matrix[i][k] * other._matrix[k][j];
            }
            res._matrix[i][j] = sum;
        }
    }

    return res;
}

Vector4 Matrix4::operator*(Vector4 const& vec) const {
    double res[4];

    for (int i = 0; i < 4; i++) {
        double sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += this->_matrix[i][j] * vec.vector[j];
        }
        res[i] = sum;
    }

    return Vector4(res);
}

void    Matrix4::toFloatArray(float res[16]) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i * 4 + j] = static_cast<float>(this->_matrix[i][j]);
        }
    }
}
