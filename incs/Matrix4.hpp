#ifndef Matrix4_HPP
# define Matrix4_HPP

enum Axis {
    X,
    Y,
    Z,
};

class Matrix4 {
    public:
        double matrix[4][4];

        Matrix4();
        Matrix4(int matrix[4][4]);
        ~Matrix4();
        Matrix4(Matrix4 const& copy);
        Matrix4& operator=(Matrix4 const& other);

        // create a null matrix with constructor then call the following functions
        void identity();
        void translation(int x, int y, int z);
        void scaling(int x, int y, int z);
        void rotation(float angle, Axis axis);
        

};

#endif