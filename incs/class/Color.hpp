#ifndef HUMANDGL_COLOR_HPP
# define HUMANDGL_COLOR_HPP

#include <string>

class Color {
public:
	Color(const std::string &str);
	Color(const Color &src);
	~Color();

	Color &operator=(const Color &rhs);

	float	getRed() const;
	float	getGreen() const;
	float	getBlue() const;

private:
	float	_r;
	float	_g;
	float	_b;
};

#endif
