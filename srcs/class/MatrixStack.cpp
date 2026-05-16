#include "class/MatrixStack.hpp"

MatrixStack::MatrixStack() {}

MatrixStack::~MatrixStack() {}

MatrixStack::MatrixStack(MatrixStack const& copy) {
    this->_stack = copy._stack;
}

MatrixStack& MatrixStack::operator=(MatrixStack const& other) {
    if (this != &other) {
        this->_stack = other._stack;
    }

    return (*this);
}

void MatrixStack::push(Matrix4 matrix) {
    this->_stack.push(matrix);
}

Matrix4 MatrixStack::pop() {
    Matrix4 top = this->_stack.top();
    this->_stack.pop();
    return (top);
}

Matrix4 const& MatrixStack::top() const {
    return (this->_stack.top());
}

bool MatrixStack::empty() const {
    return (this->_stack.empty());
}

void MatrixStack::clear() {
    while (!this->_stack.empty()) {
        this->_stack.pop();
    }
}
