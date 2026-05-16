#include "class/Color.hpp"

#include <iostream>

// CONSTRUCTOR - DESTRUCTOR ---------------------------------------------------
Color::Color(const std::string &str) {
	this->_r = std::stoi(str.substr(1, 2), nullptr, 16) / 255.0f;
	this->_g = std::stoi(str.substr(3, 2), nullptr, 16) / 255.0f;
	this->_b = std::stoi(str.substr(5, 2), nullptr, 16) / 255.0f;
	std::cout << "str" << str << " r" << this->_r << " g" << this->_g << " b" << this->_b << std::endl;
}

Color::Color(const Color &src) { *this = src; }

Color::~Color() {}

// OPERATOR OVERLOADING -------------------------------------------------------
Color &Color::operator=(const Color &rhs) {
	if (this != &rhs) {
		this->_r = rhs._r;
		this->_g = rhs._g;
		this->_b = rhs._b;
	}
	return (*this);
}

// GETTER ---------------------------------------------------------------------
float	Color::getRed() const { return (this->_r); }
float	Color::getGreen() const { return (this->_g); }
float	Color::getBlue() const { return (this->_b); }
