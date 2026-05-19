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

// TODO AI --------
static Vector4 vector_sub(Vector4 const& a, Vector4 const& b) {
    return Vector4(a.vector[0] - b.vector[0], a.vector[1] - b.vector[1], a.vector[2] - b.vector[2]);
}

static double vector_dot(Vector4 const& a, Vector4 const& b) {
    return a.vector[0] * b.vector[0] + a.vector[1] * b.vector[1] + a.vector[2] * b.vector[2];
}

static Vector4 vector_cross(Vector4 const& a, Vector4 const& b) {
    return Vector4(
        a.vector[1] * b.vector[2] - a.vector[2] * b.vector[1],
        a.vector[2] * b.vector[0] - a.vector[0] * b.vector[2],
        a.vector[0] * b.vector[1] - a.vector[1] * b.vector[0]);
}

static Vector4 vector_normalize(Vector4 const& v) {
    double length = std::sqrt(v.vector[0] * v.vector[0] + v.vector[1] * v.vector[1] + v.vector[2] * v.vector[2]);
    if (length == 0.0)
        return Vector4(0.0, 0.0, 0.0);
    return Vector4(v.vector[0] / length, v.vector[1] / length, v.vector[2] / length);
}

Matrix4 Matrix4::perspective(double fov_y_radians, double aspect, double near_z, double far_z) {
    Matrix4 result;
    double f = 1.0 / std::tan(fov_y_radians / 2.0);
    result._matrix[0][0] = f / aspect;
    result._matrix[1][1] = f;
    result._matrix[2][2] = (far_z + near_z) / (near_z - far_z);
    result._matrix[2][3] = (2.0 * far_z * near_z) / (near_z - far_z);
    result._matrix[3][2] = -1.0;
    return result;
}

Matrix4 Matrix4::lookAt(Vector4 const& eye, Vector4 const& center, Vector4 const& up) {
    Vector4 f = vector_normalize(vector_sub(center, eye));
    Vector4 s = vector_normalize(vector_cross(f, up));
    Vector4 u = vector_cross(s, f);

    Matrix4 result;
    result._matrix[0][0] = s.vector[0];
    result._matrix[0][1] = s.vector[1];
    result._matrix[0][2] = s.vector[2];
    result._matrix[0][3] = -vector_dot(s, eye);

    result._matrix[1][0] = u.vector[0];
    result._matrix[1][1] = u.vector[1];
    result._matrix[1][2] = u.vector[2];
    result._matrix[1][3] = -vector_dot(u, eye);

    result._matrix[2][0] = -f.vector[0];
    result._matrix[2][1] = -f.vector[1];
    result._matrix[2][2] = -f.vector[2];
    result._matrix[2][3] = vector_dot(f, eye);

    result._matrix[3][3] = 1.0;
    return result;
}
// TODO ENDOF AI --------
