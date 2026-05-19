#ifndef HUMANDGL_CHARACTER_HPP
# define HUMANDGL_CHARACTER_HPP

#include "MatrixStack.hpp"
#include "class/BodyPart.hpp"

class Character {
public:
	Character();
	~Character();

	void	init();
	void	reset();
	void	update(float time_seconds, AnimationState state) const;
	void	draw(MatrixStack &stack, const Matrix4 &view_proj) const;

private:
	std::unique_ptr<BodyPart>	_torso;
	BodyPart	*_head = nullptr;
	BodyPart	*_leftUpperArm = nullptr;
	BodyPart	*_leftForearm = nullptr;
	BodyPart	*_rightUpperArm = nullptr;
	BodyPart	*_rightForearm = nullptr;

	BodyPart	*_leftThigh = nullptr;
	BodyPart	*_leftLowerLeg = nullptr;
	BodyPart	*_leftFoot = nullptr;

	BodyPart	*_rightThigh = nullptr;
	BodyPart	*_rightLowerLeg = nullptr;
	BodyPart	*_rightFoot = nullptr;
};

#endif
