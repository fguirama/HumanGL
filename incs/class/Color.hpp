#ifndef HUMANDGL_COLOR_HPP
# define HUMANDGL_COLOR_HPP

#include <string>

class Color {
public:
	explicit Color(const std::string &str);
	Color(const Color &src);
	~Color();

	Color &operator=(const Color &rhs);

	[[nodiscard]] float	getRed() const;
	[[nodiscard]] float	getGreen() const;
	[[nodiscard]] float	getBlue() const;

private:
	float	_r;
	float	_g;
	float	_b;
};

#endif
