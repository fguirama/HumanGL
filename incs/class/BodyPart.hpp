#ifndef HUMANDGL_BODYPART_HPP
# define HUMANDGL_BODYPART_HPP

#include <memory>
#include <string>
#include <vector>
#include "Color.hpp"
#include "humanGL.h"

class BodyPart {
public:
	explicit BodyPart(const std::string &n);
	~BodyPart();

	void	setLocalPosition(float x, float y, float z);
	void	setLocalRotation(float x, float y, float z);
	void	setLocalScale(float x, float y, float z);

	BodyPart	*addChild(std::unique_ptr<BodyPart> child);

private:
	std::string	_name;
	Vector4		_localPosition;
	Vector4		_localRotation;
	Vector4		_localScale;
	Color		_color;
	BodyPart								*_parent = nullptr;
	std::vector<std::unique_ptr<BodyPart>>	_children;
};

#endif
