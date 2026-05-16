#include "class/Character.hpp"

// CONSTRUCTOR - DESTRUCTOR ---------------------------------------------------
Character::Character() {
	this->init();
}

Character::~Character() = default;

// METHOD ---------------------------------------------------------------------
void	Character::init() {
	constexpr float torso_width = 1.0f;
	constexpr float torso_height = 2.0f;
	constexpr float torso_depth = 0.4f;

	constexpr float head_size = 0.6f;

	constexpr float upper_arm_length = 1.0f;
	constexpr float upper_arm_width = 0.3f;
	constexpr float forearm_length = 0.8f;
	constexpr float forearm_width = 0.25f;

	constexpr float thigh_length = 1.2f;
	constexpr float thigh_width = 0.35f;
	constexpr float lower_leg_length = 1.0f;
	constexpr float lower_leg_width = 0.3f;

    // TORSO
    torso = std::make_unique<BodyPart>("torso");
    torso->setLocalPosition(0.0f, 0.0f, 0.0f);
    torso->setLocalScale(torso_width, torso_height, torso_depth);
    torso->setColor("#2B641A");

    // HEAD
    auto head_part = std::make_unique<BodyPart>("head");
    head_part->setLocalPosition(0.0f, torso_height * 0.5f, 0.0f);
    head_part->setLocalScale(head_size, head_size, head_size);
    head_part->setGeometryOffset(0.0f, head_size * 0.5f, 0.0f);
    head_part->setColor("#D8AD98");

    // LEFT ARM
	constexpr float shoulder_height = torso_height * 0.5f;
	constexpr float shoulder_offset = torso_width * 0.5f;
    auto left_arm = std::make_unique<BodyPart>("leftUpperArm");
    left_arm->setLocalPosition(-shoulder_offset, shoulder_height, 0.0f);
    left_arm->setLocalScale(upper_arm_width, upper_arm_length, upper_arm_width);
    left_arm->setGeometryOffset(upper_arm_width * -0.5f, -upper_arm_length * 0.5f, 0.0f);
    left_arm->setColor("#D8AD98");

    auto left_forearm = std::make_unique<BodyPart>("leftForearm");
    left_forearm->setLocalPosition(0.0f, -upper_arm_length, 0.0f);
    left_forearm->setLocalScale(forearm_width, forearm_length, forearm_width);
    left_forearm->setGeometryOffset(upper_arm_width * -0.5f, -forearm_length * 0.5f, 0.0f);
    left_forearm->setColor("#D8AD98");

    // RIGHT ARM
    auto right_arm = std::make_unique<BodyPart>("rightUpperArm");
    right_arm->setLocalPosition(shoulder_offset, shoulder_height, 0.0f);
    right_arm->setLocalScale(upper_arm_width, upper_arm_length, upper_arm_width);
    right_arm->setGeometryOffset(upper_arm_width * 0.5f, -upper_arm_length * 0.5f, 0.0f);
    right_arm->setColor("#D8AD98");

    auto right_forearm = std::make_unique<BodyPart>("rightForearm");
    right_forearm->setLocalPosition(0.0f, -upper_arm_length, 0.0f);
    right_forearm->setLocalScale(forearm_width, forearm_length, forearm_width);
    right_forearm->setGeometryOffset(upper_arm_width * 0.5f, -forearm_length * 0.5f, 0.0f);
    right_forearm->setColor("#D8AD98");

    // LEFT LEG
	constexpr float hip_height = -torso_height * 0.5f;
	constexpr float hip_offset = torso_width * 0.25f;
    auto left_thigh = std::make_unique<BodyPart>("leftThigh");
    left_thigh->setLocalPosition(-hip_offset, hip_height, 0.0f);
    left_thigh->setLocalScale(thigh_width, thigh_length, thigh_width);
    left_thigh->setGeometryOffset(0.0f, -thigh_length * 0.5f, 0.0f);
    left_thigh->setColor("#1F4B94");

    auto left_lower_leg = std::make_unique<BodyPart>("leftLowerLeg");
    left_lower_leg->setLocalPosition(0.0f, -thigh_length, 0.0f);
    left_lower_leg->setLocalScale(lower_leg_width, lower_leg_length, lower_leg_width);
    left_lower_leg->setGeometryOffset(0.0f, -lower_leg_length * 0.5f, 0.0f);
    left_lower_leg->setColor("#1F4B94");

    // RIGHT LEG
    auto right_thigh = std::make_unique<BodyPart>("rightThigh");
    right_thigh->setLocalPosition(hip_offset, hip_height, 0.0f);
    right_thigh->setLocalScale(thigh_width, thigh_length, thigh_width);
    right_thigh->setGeometryOffset(0.0f, -thigh_length * 0.5f, 0.0f);
    right_thigh->setColor("#1F4B94");

    auto right_lower_leg = std::make_unique<BodyPart>("rightLowerLeg");
    right_lower_leg->setLocalPosition(0.0f, -thigh_length, 0.0f);
    right_lower_leg->setLocalScale(lower_leg_width, lower_leg_length, lower_leg_width);
    right_lower_leg->setGeometryOffset(0.0f, -lower_leg_length * 0.5f, 0.0f);
    right_lower_leg->setColor("#1F4B94");

    // HIERARCHY
    head = torso->addChild(std::move(head_part));

    leftUpperArm = torso->addChild(std::move(left_arm));
    leftForearm = leftUpperArm->addChild(std::move(left_forearm));

    rightUpperArm = torso->addChild(std::move(right_arm));
    rightForearm = rightUpperArm->addChild(std::move(right_forearm));

    leftThigh = torso->addChild(std::move(left_thigh));
    leftLowerLeg = leftThigh->addChild(std::move(left_lower_leg));

    rightThigh = torso->addChild(std::move(right_thigh));
    rightLowerLeg = rightThigh->addChild(std::move(right_lower_leg));
}

void	Character::reset() {
	torso.reset();
	this->init();
}
