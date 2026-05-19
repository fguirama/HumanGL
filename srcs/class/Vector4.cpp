#include "class/Vector4.hpp"
#include <cmath>


Vector4::Vector4(): _vector() {
    for (int i = 0; i < 3; i++)
        this->_vector[i] = 0;
    this->_vector[3] = 1;
}

Vector4::Vector4(const double x, const double y, const double z): _vector() {
    this->_vector[0] = x;
    this->_vector[1] = y;
    this->_vector[2] = z;
    this->_vector[3] = 1;
}

Vector4::Vector4(const double x, const double y, const double z, const double w): _vector() {
    this->_vector[0] = x;
    this->_vector[1] = y;
    this->_vector[2] = z;
    this->_vector[3] = w;
}

Vector4::Vector4(const double vec[4]): _vector() {
    for (int i = 0; i < 4; i++)
        this->_vector[i] = vec[i];
}

Vector4::~Vector4() = default;

Vector4::Vector4(Vector4 const& copy): _vector() {
    for (int i = 0; i < 4; i++)
        this->_vector[i] = copy._vector[i];
}

Vector4 Vector4::operator+(Vector4 const &vec) const {
    return {this->_vector[0] + vec._vector[0], this->_vector[1] + vec._vector[1], this->_vector[2] + vec._vector[2]};
}

Vector4 Vector4::operator-(Vector4 const &vec) const {
    return {this->_vector[0] - vec._vector[0], this->_vector[1] - vec._vector[1], this->_vector[2] - vec._vector[2]};
}

Vector4 Vector4::operator*(Vector4 const & vec) const {
    return {this->_vector[1] * vec._vector[2] - this->_vector[2] * vec._vector[1],
        this->_vector[2] * vec._vector[0] - this->_vector[0] * vec._vector[2],
        this->_vector[0] * vec._vector[1] - this->_vector[1] * vec._vector[0]};
}

double  Vector4::dot(Vector4 const & vec) const {
    return (this->_vector[0] * vec._vector[0] + this->_vector[1] * vec._vector[1] + this->_vector[2] * vec._vector[2]);
}

void    Vector4::normalize() {
    if (const double div = std::sqrt(this->_vector[0] * this->_vector[0] + this->_vector[1] * this->_vector[1] + this->_vector[2] * this->_vector[2]); div != 0) {
        this->_vector[0] /= div;
        this->_vector[1] /= div;
        this->_vector[2] /= div;
    }
}

Vector4&    Vector4::operator=(Vector4 const& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            this->_vector[i] = other._vector[i];
        }
    }

    return (*this);
}

double Vector4::operator[](const int axes) const {
    return (this->_vector[axes]);
}
