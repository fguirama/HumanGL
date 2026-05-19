#ifndef HUMANDGL_CHARACTER_HPP
# define HUMANDGL_CHARACTER_HPP

#include "MatrixStack.hpp"
#include "class/BodyPart.hpp"

enum class AnimationState {
	Idle,
	Walk,
	Jump
};

class Character {
public:
	Character();
	~Character();

	void	init();
	void	reset();
	void	update(float time_seconds, AnimationState state) const;
	void	draw(MatrixStack &stack, const Matrix4 &view_proj) const;

private:
	std::unique_ptr<BodyPart>	torso;
	BodyPart	*head = nullptr;
	BodyPart	*leftUpperArm = nullptr;
	BodyPart	*leftForearm = nullptr;
	BodyPart	*rightUpperArm = nullptr;
	BodyPart	*rightForearm = nullptr;
	BodyPart	*leftThigh = nullptr;
	BodyPart	*leftLowerLeg = nullptr;
	BodyPart	*rightThigh = nullptr;
	BodyPart	*rightLowerLeg = nullptr;
};

#endif
