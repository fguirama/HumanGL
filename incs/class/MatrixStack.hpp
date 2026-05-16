#ifndef MATRIXSTACK_HPP
# define MATRIXSTACK_HPP

#include <stack>
#include "Matrix4.hpp"

class MatrixStack {
    public:

        MatrixStack();
        ~MatrixStack();
        MatrixStack(MatrixStack const& copy);
        MatrixStack	&operator=(MatrixStack const& other);

        void			push(Matrix4 matrix);
        Matrix4			pop();
        const Matrix4	&top() const;
        bool			empty() const;
        void			clear();
	private:
        std::stack<Matrix4>	_stack;
};

#endif
