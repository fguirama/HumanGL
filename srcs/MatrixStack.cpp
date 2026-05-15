#include "../incs/MatrixStack.hpp"

MatrixStack::MatrixStack() {}

MatrixStack::~MatrixStack() {}

MatrixStack::MatrixStack(MatrixStack const& copy) {
    stack = copy.stack;
}

MatrixStack& MatrixStack::operator=(MatrixStack const& other) {
    if (this != &other) {
        stack = other.stack;
    }

    return *this;
}

void MatrixStack::push(Matrix4 matrix) {
    stack.push(matrix);
}

Matrix4 MatrixStack::pop() {
    Matrix4 top = stack.top();
    stack.pop();
    return top;
}