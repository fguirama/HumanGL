#ifndef HUMANDGL_BODYPART_HPP
# define HUMANDGL_BODYPART_HPP

#include "humanGL.h"
#include <vector>

class BodyPart {
public:
	explicit BodyPart(const std::string& n);
	~BodyPart();

	void	setLocalPosition(float x, float y, float z);
	void	setLocalRotation(float x, float y, float z);
	void	setLocalScale(float x, float y, float z);

	BodyPart	*addChild(std::unique_ptr<BodyPart> child);

private:
	std::string	_name;
	Vec3		_localPosition{};
	Vec3		_localRotation{};
	Vec3		_localScale{};
	BodyPart								*_parent = nullptr;
	std::vector<std::unique_ptr<BodyPart>>	_children;
};

#endif
