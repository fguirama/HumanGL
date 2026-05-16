#include "class/BodyPart.hpp"

// CONSTRUCTOR - DESTRUCTOR ---------------------------------------------------
BodyPart::BodyPart(const std::string &n): _name(n) {
	this->_localPosition = Vector4(0.0, 0.0, 0.0);
	this->_localRotation = Vector4(0.0, 0.0, 0.0);
	this->_localScale    = Vector4(1.0, 1.0, 1.0);
	this->_geometryOffset = Vector4(0.0, 0.0, 0.0);
	this->_color = Vector4(0.8, 0.8, 0.8, 1.0);
}

BodyPart::~BodyPart() = default;


// SETTER ---------------------------------------------------------------------
void	BodyPart::setLocalPosition(const float x, const float y, const float z) { this->_localPosition = Vector4(x, y, z); }
void	BodyPart::setLocalRotation(const float x, const float y, const float z) { this->_localRotation = Vector4(x, y, z); }
void	BodyPart::setLocalScale(const float x, const float y, const float z) { this->_localScale = Vector4(x, y, z); }
void	BodyPart::setGeometryOffset(const float x, const float y, const float z) { this->_geometryOffset = Vector4(x, y, z); }
void	BodyPart::setColor(const float r, const float g, const float b) { this->_color = Vector4(r, g, b, 1.0); }

BodyPart	*BodyPart::addChild(std::unique_ptr<BodyPart> child) {
	child->_parent = this;
	BodyPart* rawPtr = child.get();
	_children.push_back(std::move(child));
	return (rawPtr);
}
