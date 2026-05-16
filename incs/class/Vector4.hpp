#ifndef VECTOR4_HPP
# define VECTOR4_HPP

class Vector4 {
    public:
        Vector4();
        Vector4(double x, double y, double z);
		explicit Vector4(double vec[4]);
        Vector4(Vector4 const& copy);
        Vector4	&operator=(Vector4 const& other);
        ~Vector4();
        double	vector[4];
};

#endif