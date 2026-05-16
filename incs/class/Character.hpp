#ifndef HUMANDGL_CHARACTER_HPP
# define HUMANDGL_CHARACTER_HPP

#include "class/BodyPart.hpp"

class Character {
public:
	Character();
	~Character();

	void	init();
	void	reset();

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
