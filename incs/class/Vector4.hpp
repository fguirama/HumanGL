#ifndef VECTOR4_HPP
# define VECTOR4_HPP

class Vector4 {
    public:
        Vector4();
        ~Vector4();

        Vector4(double x, double y, double z);
        Vector4(double x, double y, double z, double w);
		explicit Vector4(const double vec[4]);
        Vector4(Vector4 const& copy);

        Vector4	&operator=(const Vector4 &other);
		Vector4	operator+(const Vector4 &vec) const;
		Vector4	operator-(const Vector4 &vec) const;
		Vector4	operator*(const Vector4 &vec) const;
		double	operator[](int axes) const;

		[[nodiscard]] double	dot(const Vector4 &vec) const;
		void					normalize();

	private:
        double	_vector[4];
};

#endif
