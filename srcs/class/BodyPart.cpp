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

Matrix4 BodyPart::jointMatrix() const {
	Matrix4	translation;
	translation.translation(_localPosition.vector[0], _localPosition.vector[1], _localPosition.vector[2]);

	Matrix4	rotate_x;
	rotate_x.rotation(_localRotation.vector[0], X);
	Matrix4	rotate_y;
	rotate_y.rotation(_localRotation.vector[1], Y);
	Matrix4	rotate_z;
	rotate_z.rotation(_localRotation.vector[2], Z);

	return (translation * rotate_z * rotate_y * rotate_x);
}

Matrix4 BodyPart::drawMatrix() const {
	Matrix4 geometry_offset;
	geometry_offset.translation(_geometryOffset.vector[0], _geometryOffset.vector[1], _geometryOffset.vector[2]);

	Matrix4 scaling;
	scaling.scaling(_localScale.vector[0], _localScale.vector[1], _localScale.vector[2]);

	return (geometry_offset * scaling);
}

void BodyPart::draw(MatrixStack &stack, const Matrix4 &view_proj) const {
	Matrix4	joint = stack.top() * jointMatrix();
	Matrix4	model = joint * drawMatrix();
	Matrix4	model_proj = view_proj * model;
	drawCube(model_proj, _color);

	stack.push(joint);
	for (const auto &child : _children) {
		child->draw(stack, view_proj);
	}
	stack.pop();
}
