#include "class/Character.hpp"

// CONSTRUCTOR - DESTRUCTOR ---------------------------------------------------
Character::Character() {
	this->init();
}

Character::~Character() = default;

// METHOD ---------------------------------------------------------------------
void	Character::init() {
    // TORSO
    torso = std::make_unique<BodyPart>("torso");
    torso->setLocalPosition(0.0f, 0.0f, 0.0f);
    torso->setLocalScale(1.0f, 2.0f, 0.5f);

    // HEAD
    auto head = std::make_unique<BodyPart>("head");
    head->setLocalPosition(0.0f, 1.5f, 0.0f);
    head->setLocalScale(0.6f, 0.6f, 0.6f);

    // LEFT ARM
    auto leftArm = std::make_unique<BodyPart>("leftArm");
    leftArm->setLocalPosition(-0.8f, 0.8f, 0.0f);
    leftArm->setLocalScale(0.3f, 1.0f, 0.3f);

    auto leftForearm = std::make_unique<BodyPart>("leftForearm");
    leftForearm->setLocalPosition(0.0f, -1.0f, 0.0f);
    leftForearm->setLocalScale(0.25f, 0.8f, 0.25f);

    // RIGHT ARM
    auto rightArm = std::make_unique<BodyPart>("rightArm");
    rightArm->setLocalPosition(0.8f, 0.8f, 0.0f);
    rightArm->setLocalScale(0.3f, 1.0f, 0.3f);

    auto rightForearm = std::make_unique<BodyPart>("rightForearm");
    rightForearm->setLocalPosition(0.0f, -1.0f, 0.0f);
    rightForearm->setLocalScale(0.25f, 0.8f, 0.25f);

    // LEFT LEG
    auto leftLeg = std::make_unique<BodyPart>("leftLeg");
    leftLeg->setLocalPosition(-0.4f, -1.2f, 0.0f);
    leftLeg->setLocalScale(0.35f, 1.2f, 0.35f);

    auto leftLowerLeg = std::make_unique<BodyPart>("leftLowerLeg");
    leftLowerLeg->setLocalPosition(0.0f, -1.1f, 0.0f);
    leftLowerLeg->setLocalScale(0.3f, 1.0f, 0.3f);

    // RIGHT LEG
    auto rightLeg = std::make_unique<BodyPart>("rightLeg");
    rightLeg->setLocalPosition(0.4f, -1.2f, 0.0f);
    rightLeg->setLocalScale(0.35f, 1.2f, 0.35f);

    auto rightLowerLeg = std::make_unique<BodyPart>("rightLowerLeg");
    rightLowerLeg->setLocalPosition(0.0f, -1.1f, 0.0f);
    rightLowerLeg->setLocalScale(0.3f, 1.0f, 0.3f);

    // HIERARCHY
    torso->addChild(std::move(head));

    BodyPart	*leftArmPtr = torso->addChild(std::move(leftArm));
    leftArmPtr->addChild(std::move(leftForearm));

    BodyPart	*rightArmPtr = torso->addChild(std::move(rightArm));
    rightArmPtr->addChild(std::move(rightForearm));

    BodyPart	*leftLegPtr = torso->addChild(std::move(leftLeg));
    leftLegPtr->addChild(std::move(leftLowerLeg));

    BodyPart	*rightLegPtr = torso->addChild(std::move(rightLeg));
    rightLegPtr->addChild(std::move(rightLowerLeg));
}

void	Character::reset() {
	torso.reset();
	this->init();
}
