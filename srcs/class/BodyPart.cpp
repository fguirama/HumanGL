#include "class/BodyPart.hpp"

// CONSTRUCTOR - DESTRUCTOR ---------------------------------------------------
BodyPart::BodyPart(const std::string &n) : _name(n), _color("#ffffff") {
	this->_localPosition = Vector4(0.0, 0.0, 0.0);
	this->_localRotation = Vector4(0.0, 0.0, 0.0);
	this->_localScale = Vector4(1.0, 1.0, 1.0);
	this->_geometryOffset = Vector4(0.0, 0.0, 0.0);
}

BodyPart::~BodyPart() = default;


// SETTER ---------------------------------------------------------------------
void	BodyPart::setLocalPosition(const float x, const float y, const float z) { this->_localPosition = Vector4(x, y, z); }
void	BodyPart::setLocalRotation(const float x, const float y, const float z) { this->_localRotation = Vector4(x, y, z); }
void	BodyPart::setLocalScale(const float x, const float y, const float z) { this->_localScale = Vector4(x, y, z); }
void	BodyPart::setGeometryOffset(const float x, const float y, const float z) { this->_geometryOffset = Vector4(x, y, z); }
void	BodyPart::setColor(const std::string &str) { this->_color = Color(str); }

BodyPart	*BodyPart::addChild(std::unique_ptr<BodyPart> child) {
	child->_parent = this;
	BodyPart* rawPtr = child.get();
	_children.push_back(std::move(child));
	return (rawPtr);
}
