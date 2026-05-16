#ifndef MATRIXSTACK_HPP
# define MATRIXSTACK_HPP

#include <stack>
#include "Matrix4.hpp"

class MatrixStack {
    public:
        std::stack<Matrix4>	stack;

        MatrixStack();
        ~MatrixStack();
        MatrixStack(MatrixStack const& copy);
        MatrixStack	&operator=(MatrixStack const& other);

        void	push(Matrix4 matrix);
        Matrix4	pop();
        Matrix4 const& top() const;
        bool	empty() const;
        void	clear();
};

#endif
