#include "class/Character.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

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

	constexpr float thigh_length = 1.2f;
	constexpr float thigh_width = 0.35f;
	constexpr float lower_leg_length = 1.0f;

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
    left_forearm->setLocalScale(upper_arm_width, forearm_length, upper_arm_width);
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
    right_forearm->setLocalScale(upper_arm_width, forearm_length, upper_arm_width);
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
    left_lower_leg->setLocalScale(thigh_width, lower_leg_length, thigh_width);
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
    right_lower_leg->setLocalScale(thigh_width, lower_leg_length, thigh_width);
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

void Character::update(const float time_seconds, const AnimationState state) const {
	if (!torso || !head || !leftUpperArm || !rightUpperArm || !leftForearm || !rightForearm || !leftThigh || !rightThigh || !leftLowerLeg || !rightLowerLeg)
		return ;

	torso->setLocalPosition(0.0f, 0.0f, 0.0f);
	head->setLocalRotation(0.0f, 0.0f, 0.0f);
	leftUpperArm->setLocalRotation(0.0f, 0.0f, 0.0f);
	rightUpperArm->setLocalRotation(0.0f, 0.0f, 0.0f);
	leftForearm->setLocalRotation(0.0f, 0.0f, 0.0f);
	rightForearm->setLocalRotation(0.0f, 0.0f, 0.0f);
	leftThigh->setLocalRotation(0.0f, 0.0f, 0.0f);
	rightThigh->setLocalRotation(0.0f, 0.0f, 0.0f);
	leftLowerLeg->setLocalRotation(0.0f, 0.0f, 0.0f);
	rightLowerLeg->setLocalRotation(0.0f, 0.0f, 0.0f);

	// TODO AI --------
	if (state == AnimationState::Walk) {

		constexpr float knee_bend = 0.45f;
		constexpr float forearm_bend = 0.35f;
		constexpr float walk_amplitude = 0.7f;
		constexpr float walk_speed = 2.8f;
		const float phase = std::sin(time_seconds * walk_speed);
		const float swing = phase * walk_amplitude;
		const float bend = std::max(0.0f, std::sin(time_seconds * walk_speed)) * forearm_bend;
		const float knee = std::max(0.0f, -std::sin(time_seconds * walk_speed)) * knee_bend;

		leftUpperArm->setLocalRotation(swing, 0.0f, 0.0f);
		rightUpperArm->setLocalRotation(-swing, 0.0f, 0.0f);
		leftThigh->setLocalRotation(-swing, 0.0f, 0.0f);
		rightThigh->setLocalRotation(swing, 0.0f, 0.0f);
		leftForearm->setLocalRotation(-bend, 0.0f, 0.0f);
		rightForearm->setLocalRotation(-bend, 0.0f, 0.0f);
		leftLowerLeg->setLocalRotation(knee, 0.0f, 0.0f);
		rightLowerLeg->setLocalRotation(knee, 0.0f, 0.0f);
	}

	if (state == AnimationState::Jump) {
		constexpr float jump_height = 0.7f;
		constexpr float jump_speed = 2.2f;
		const float jump_phase = std::max(0.0f, std::sin(time_seconds * jump_speed));

		torso->setLocalPosition(0.0f, jump_phase * jump_height, 0.0f);
		leftUpperArm->setLocalRotation(-0.6f, 0.0f, 0.0f);
		rightUpperArm->setLocalRotation(-0.6f, 0.0f, 0.0f);
		leftForearm->setLocalRotation(-0.3f, 0.0f, 0.0f);
		rightForearm->setLocalRotation(-0.3f, 0.0f, 0.0f);
		leftThigh->setLocalRotation(0.6f, 0.0f, 0.0f);
		rightThigh->setLocalRotation(0.6f, 0.0f, 0.0f);
		leftLowerLeg->setLocalRotation(-0.6f, 0.0f, 0.0f);
		rightLowerLeg->setLocalRotation(-0.6f, 0.0f, 0.0f);
	}
	// TODO ENDOF AI --------
}

void Character::draw(MatrixStack &stack, const Matrix4 &view_proj) const {
	if (!torso)
		return;
	torso->draw(stack, view_proj);
}
