#ifndef Matrix4_HPP
# define Matrix4_HPP

enum Axis {
    X,
    Y,
    Z,
};

class Matrix4 {
    public:
        double  matrix[4][4];

        Matrix4();
        explicit Matrix4(const double matrix[4][4]);
        ~Matrix4();
        Matrix4(Matrix4 const& copy);
        Matrix4 &operator=(Matrix4 const& other);

        // create a null matrix with constructor then call the following functions
        void    identity();
        void    translation(double x, double y, double z);
        void    scaling(double x, double y, double z);
        void    rotation(double angle, Axis axis);
};

#endif