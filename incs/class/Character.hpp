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
};

#endif
