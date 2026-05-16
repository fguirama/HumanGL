#ifndef HUMANDGL_BODYPART_HPP
# define HUMANDGL_BODYPART_HPP

#include <memory>
#include <string>
#include <vector>
#include "Color.hpp"
#include "humanGL.h"
#include "MatrixStack.hpp"

class BodyPart {
public:
	explicit BodyPart(const std::string &n);
	~BodyPart();

	void	setLocalPosition(float x, float y, float z);
	void	setLocalRotation(float x, float y, float z);
	void	setLocalScale(float x, float y, float z);
	void	setGeometryOffset(float x, float y, float z);
	void	setColor(const std::string &str);

	BodyPart	*addChild(std::unique_ptr<BodyPart> child);
	void		draw(MatrixStack &stack, const Matrix4 &view_proj) const;

private:
	Matrix4		jointMatrix() const;
	Matrix4		drawMatrix() const;

	std::string	_name;
	Vector4		_localPosition;
	Vector4		_localRotation;
	Vector4		_localScale;
	Vector4		_geometryOffset;
	Color		_color;
	BodyPart								*_parent = nullptr;
	std::vector<std::unique_ptr<BodyPart>>	_children;
};

#endif
