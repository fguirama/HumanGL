#include "class/Vector4.hpp"

Vector4::Vector4() {
    for (int i = 0; i < 3; i++)
        vector[i] = 0;
    vector[3] = 1;
}

Vector4::Vector4(double x, double y, double z) {
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    vector[3] = 1;
}

Vector4::Vector4(double x, double y, double z, double w) {
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    vector[3] = w;
}

Vector4::Vector4(double vec[4]) {
    for (int i = 0; i < 4; i++)
        vector[i] = vec[i];
}

Vector4::~Vector4() {}

Vector4::Vector4(Vector4 const& copy) {
    for (int i = 0; i < 4; i++)
        vector[i] = copy.vector[i];
}

Vector4& Vector4::operator=(Vector4 const& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            vector[i] = other.vector[i];
        }
    }

    return *this;
}
