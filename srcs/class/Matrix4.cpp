#include "class/Matrix4.hpp"
#include <cmath>

Matrix4::Matrix4(): _matrix() {
    for (auto & i : this->_matrix) {
        for (double & j : i) {
            j = 0;
        }
    }
}

Matrix4::Matrix4(const double matrix[4][4]): _matrix() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->_matrix[i][j] = matrix[i][j];
        }
    }
}

Matrix4::~Matrix4() = default;

Matrix4::Matrix4(const Matrix4 &copy): _matrix() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->_matrix[i][j] = copy._matrix[i][j];
        }
    }
}

Matrix4 &Matrix4::operator=(const Matrix4 &other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this->_matrix[i][j] = other._matrix[i][j];
            }
        }
    }

    return (*this);
}

void    Matrix4::identity() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j)
                this->_matrix[i][j] = 1;
            else
                this->_matrix[i][j] = 0;
        }
    }
}

void    Matrix4::translation(const double x, const double y, const double z) {
    identity();
    this->_matrix[0][3] = x;
    this->_matrix[1][3] = y;
    this->_matrix[2][3] = z;
}

void    Matrix4::scaling(const double x, const double y, const double z) {
    identity();
    this->_matrix[0][0] = x;
    this->_matrix[1][1] = y;
    this->_matrix[2][2] = z;
}

void    Matrix4::rotation(const double angle, const Axis axis) {
    identity();
    const double  cosinus = std::cos(angle);
    const double  sinus = std::sin(angle);

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

    return (res);
}

Vector4 Matrix4::operator*(Vector4 const& vec) const {
    double  res[4];

    for (int i = 0; i < 4; i++) {
        double sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += this->_matrix[i][j] * vec[j];
        }
        res[i] = sum;
    }

    return (Vector4(res));
}

void    Matrix4::toFloatArray(float res[16]) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i * 4 + j] = static_cast<float>(this->_matrix[i][j]);
        }
    }
}

Matrix4 Matrix4::perspective(const double fov_y_radians, const double aspect, const double near_z, const double far_z) {
    Matrix4         result;
    const double    f = 1.0 / std::tan(fov_y_radians / 2.0);

    result._matrix[0][0] = f / aspect;
    result._matrix[1][1] = f;
    result._matrix[2][2] = (far_z + near_z) / (near_z - far_z);
    result._matrix[2][3] = (2.0 * far_z * near_z) / (near_z - far_z);
    result._matrix[3][2] = -1.0;
    return (result);
}

Matrix4 Matrix4::lookAt(Vector4 const& eye, Vector4 const& center, Vector4 const& up) {
    Vector4 f = center - eye;
    f.normalize();
    Vector4 s = f * up;
    s.normalize();
    const   Vector4 u = s * f;

    Matrix4 result;
    result._matrix[0][0] = s[0];
    result._matrix[0][1] = s[1];
    result._matrix[0][2] = s[2];
    result._matrix[0][3] = -s.dot(eye);

    result._matrix[1][0] = u[0];
    result._matrix[1][1] = u[1];
    result._matrix[1][2] = u[2];
    result._matrix[1][3] = - u.dot(eye);

    result._matrix[2][0] = -f[0];
    result._matrix[2][1] = -f[1];
    result._matrix[2][2] = -f[2];
    result._matrix[2][3] = f.dot(eye);

    result._matrix[3][3] = 1.0;
    return (result);
}
