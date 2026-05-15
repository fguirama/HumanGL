#include "class/BodyPart.hpp"

// CONSTRUCTOR - DESTRUCTOR ---------------------------------------------------
BodyPart::BodyPart(const std::string &n): _name(n) {
	this->_localPosition = {0, 0, 0};
	this->_localRotation = {0, 0, 0};
	this->_localScale    = {1, 1, 1};
}

BodyPart::~BodyPart() = default;


// SETTER ---------------------------------------------------------------------
void	BodyPart::setLocalPosition(const float x, const float y, const float z) { this->_localPosition = {x, y, z}; }
void	BodyPart::setLocalRotation(const float x, const float y, const float z) { this->_localRotation = {x, y, z}; }
void	BodyPart::setLocalScale(const float x, const float y, const float z) { this->_localScale = {x, y, z}; }

BodyPart	*BodyPart::addChild(std::unique_ptr<BodyPart> child) {
	child->_parent = this;
	BodyPart* rawPtr = child.get();
	_children.push_back(std::move(child));
	return (rawPtr);
}
