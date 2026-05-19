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
	constexpr float feet_height = 0.2f;
	constexpr float feet_depth = 0.7f;
	constexpr float z_feet = -feet_depth / 2 + thigh_width / 2;

	const std::string	c_torso = "#2B641A";
	const std::string	c_skin = "#D8AD98";
	const std::string	c_pants = "#1F4B94";

    // TORSO
    this->_torso = std::make_unique<BodyPart>("torso");
    this->_torso->setLocalPosition(0.0f, 0.0f, 0.0f);
    this->_torso->setLocalScale(torso_width, torso_height, torso_depth);
    this->_torso->setColor(c_torso);

    // HEAD
    auto head_part = std::make_unique<BodyPart>("head");
    head_part->setLocalPosition(0.0f, torso_height * 0.5f, 0.0f);
    head_part->setLocalScale(head_size, head_size, head_size);
    head_part->setGeometryOffset(0.0f, head_size * 0.5f, 0.0f);
    head_part->setColor(c_skin);

    // LEFT ARM
	constexpr float shoulder_height = torso_height * 0.5f;
	constexpr float shoulder_offset = torso_width * 0.5f;
    auto left_arm = std::make_unique<BodyPart>("leftUpperArm");
    left_arm->setLocalPosition(-shoulder_offset, shoulder_height, 0.0f);
    left_arm->setLocalScale(upper_arm_width, upper_arm_length, upper_arm_width);
    left_arm->setGeometryOffset(upper_arm_width * -0.5f, -upper_arm_length * 0.5f, 0.0f);
    left_arm->setColor(c_skin);

    auto left_forearm = std::make_unique<BodyPart>("leftForearm");
    left_forearm->setLocalPosition(0.0f, -upper_arm_length, 0.0f);
    left_forearm->setLocalScale(upper_arm_width, forearm_length, upper_arm_width);
    left_forearm->setGeometryOffset(upper_arm_width * -0.5f, -forearm_length * 0.5f, 0.0f);
    left_forearm->setColor(c_skin);

    // RIGHT ARM
    auto right_arm = std::make_unique<BodyPart>("rightUpperArm");
    right_arm->setLocalPosition(shoulder_offset, shoulder_height, 0.0f);
    right_arm->setLocalScale(upper_arm_width, upper_arm_length, upper_arm_width);
    right_arm->setGeometryOffset(upper_arm_width * 0.5f, -upper_arm_length * 0.5f, 0.0f);
    right_arm->setColor(c_skin);

    auto right_forearm = std::make_unique<BodyPart>("rightForearm");
    right_forearm->setLocalPosition(0.0f, -upper_arm_length, 0.0f);
    right_forearm->setLocalScale(upper_arm_width, forearm_length, upper_arm_width);
    right_forearm->setGeometryOffset(upper_arm_width * 0.5f, -forearm_length * 0.5f, 0.0f);
    right_forearm->setColor(c_skin);

    // LEFT LEG
	constexpr float hip_height = -torso_height * 0.5f;
	constexpr float hip_offset = torso_width * 0.25f;
    auto left_thigh = std::make_unique<BodyPart>("leftThigh");
    left_thigh->setLocalPosition(-hip_offset, hip_height, 0.0f);
    left_thigh->setLocalScale(thigh_width, thigh_length, thigh_width);
    left_thigh->setGeometryOffset(0.0f, -thigh_length * 0.5f, 0.0f);
    left_thigh->setColor(c_pants);

    auto left_lower_leg = std::make_unique<BodyPart>("leftLowerLeg");
    left_lower_leg->setLocalPosition(0.0f, -thigh_length, 0.0f);
    left_lower_leg->setLocalScale(thigh_width, lower_leg_length, thigh_width);
    left_lower_leg->setGeometryOffset(0.0f, -lower_leg_length * 0.5f, 0.0f);
    left_lower_leg->setColor(c_pants);

    auto left_foot = std::make_unique<BodyPart>("leftFoot");
    left_foot->setLocalPosition(0.0f, -lower_leg_length, z_feet);
    left_foot->setLocalScale(thigh_width, feet_height, feet_depth);
    left_foot->setGeometryOffset(0.0f, -feet_height * 0.5f, 0.0f);
    left_foot->setColor(c_skin);

    // RIGHT LEG
    auto right_thigh = std::make_unique<BodyPart>("rightThigh");
    right_thigh->setLocalPosition(hip_offset, hip_height, 0.0f);
    right_thigh->setLocalScale(thigh_width, thigh_length, thigh_width);
    right_thigh->setGeometryOffset(0.0f, -thigh_length * 0.5f, 0.0f);
    right_thigh->setColor(c_pants);

    auto right_lower_leg = std::make_unique<BodyPart>("rightLowerLeg");
    right_lower_leg->setLocalPosition(0.0f, -thigh_length, 0.0f);
    right_lower_leg->setLocalScale(thigh_width, lower_leg_length, thigh_width);
    right_lower_leg->setGeometryOffset(0.0f, -lower_leg_length * 0.5f, 0.0f);
    right_lower_leg->setColor(c_pants);

    auto right_foot = std::make_unique<BodyPart>("rightFoot");
    right_foot->setLocalPosition(0.0f, -lower_leg_length, z_feet);
    right_foot->setLocalScale(thigh_width, feet_height, feet_depth);
    right_foot->setGeometryOffset(0.0f, -feet_height * 0.5f, 0.0f);
    right_foot->setColor(c_skin);

    // HIERARCHY
    this->_head = this->_torso->addChild(std::move(head_part));

    this->_leftUpperArm = this->_torso->addChild(std::move(left_arm));
    this->_leftForearm = this->_leftUpperArm->addChild(std::move(left_forearm));

    this->_rightUpperArm = this->_torso->addChild(std::move(right_arm));
    this->_rightForearm = this->_rightUpperArm->addChild(std::move(right_forearm));

    this->_leftThigh = this->_torso->addChild(std::move(left_thigh));
    this->_leftLowerLeg = this->_leftThigh->addChild(std::move(left_lower_leg));
    this->_leftFoot = this->_leftLowerLeg->addChild(std::move(left_foot));

    this->_rightThigh = this->_torso->addChild(std::move(right_thigh));
    this->_rightLowerLeg = this->_rightThigh->addChild(std::move(right_lower_leg));
    this->_rightFoot = this->_rightLowerLeg->addChild(std::move(right_foot));
}

void	Character::reset() {
	this->_torso.reset();
	this->init();
}

static float lerp(const float a, const float b, const float t) {
	return (a + (b - a) * t);
}

void Character::update(const float time_seconds, const AnimationState state) const {
	if (!this->_torso || !this->_head || !this->_leftUpperArm || !this->_rightUpperArm || !this->_leftForearm || !this->_rightForearm || !this->_leftThigh || !this->_rightThigh || !this->_leftLowerLeg || !this->_rightLowerLeg || !this->_leftFoot || !this->_rightFoot)
		return ;


	this->_torso->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_torso->setLocalPosition(0.0f, 0.0f, 0.0f);
	this->_head->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_leftThigh->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_leftLowerLeg->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_leftFoot->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_rightThigh->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_rightLowerLeg->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_rightFoot->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_leftUpperArm->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_leftForearm->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_rightUpperArm->setLocalRotation(0.0f, 0.0f, 0.0f);
	this->_rightForearm->setLocalRotation(0.0f, 0.0f, 0.0f);

	if (state == AnimationState::Walk) {
		constexpr float fps = 4.0f;
		constexpr int frameCount = 8;

		constexpr float frame_torso[8] =         {-0.2f, -0.3f, -0.1f, 0.0f, -0.2f, -0.3f, -0.1f, 0.0f};

		constexpr float frame_leftThigh[8] =     {-0.5f, -0.2f, 0.2f, 0.8f, 0.9f, 1.3f, 0.0f, -0.3f};
		constexpr float frame_leftLowerLeg[8] =  {0.0f, -1.0f, -1.0f, -1.5f, 0.0f, -1.2f, 0.0f, 0.0f};
		constexpr float frame_leftFoot[8] =      {0.0f, 0.1f, -0.2f, -0.1f, 0.0f, 0.1f, 0.0f, -0.25f};

		constexpr float	frame_rightThigh[8] =    {0.9f, 1.3f, 0.0f, -0.3f, -0.5f, -0.2f, 0.2f, 0.8f};
		constexpr float frame_rightLowerLeg[8] = {0.0f, -1.2f, 0.0f, 0.0f, 0.0f, -1.0f, -1.0f, -1.5f};
		constexpr float frame_rightFoot[8] =     {0.0f, 0.1f, 0.0f, -0.25f, 0.0f, 0.1f, -0.2f, -0.1f};

		float		frame = time_seconds * fps;
		frame = std::fmod(frame, static_cast<float>(frameCount));
		const int	idx0 = static_cast<int>(std::floor(frame));
		const int	idx1 = (idx0 + 1) % frameCount;
		float		t = frame - idx0;
		t = t * t * (3.0f - 2.0f * t);

		this->_torso->setLocalRotation(lerp(frame_torso[idx0], frame_torso[idx1], t), 0.0f, 0.0f);
		this->_leftThigh->setLocalRotation(lerp(frame_leftThigh[idx0], frame_leftThigh[idx1], t), 0.0f, 0.0f);
		this->_rightThigh->setLocalRotation(lerp(frame_rightThigh[idx0], frame_rightThigh[idx1], t), 0.0f, 0.0f);

		this->_leftLowerLeg->setLocalRotation(lerp(frame_leftLowerLeg[idx0], frame_leftLowerLeg[idx1], t), 0.0f, 0.0f);
		this->_rightLowerLeg->setLocalRotation(lerp(frame_rightLowerLeg[idx0], frame_rightLowerLeg[idx1], t), 0.0f, 0.0f);

		this->_leftFoot->setLocalRotation(lerp(frame_leftFoot[idx0], frame_leftFoot[idx1], t), 0.0f, 0.0f);
		this->_rightFoot->setLocalRotation(lerp(frame_rightFoot[idx0], frame_rightFoot[idx1], t), 0.0f, 0.0f);

		const float cosValue = std::cos(time_seconds * fps);
		const float bend = 0.6f * cosValue;

		this->_leftUpperArm->setLocalRotation(bend, 0.0f, 0.0f);
		this->_rightUpperArm->setLocalRotation(-bend, 0.0f, 0.0f);
		this->_leftForearm->setLocalRotation(0.6f, 0.0f, 0.0f);
		this->_rightForearm->setLocalRotation(0.6f, 0.0f, 0.0f);
	}

	if (state == AnimationState::Jump) { // todo make animation
		constexpr float jump_height = 0.7f;
		constexpr float jump_speed = 2.2f;
		const float jump_phase = std::max(0.0f, std::sin(time_seconds * jump_speed));

		this->_torso->setLocalPosition(0.0f, jump_phase * jump_height, 0.0f);

		this->_leftUpperArm->setLocalRotation(-0.6f, 0.0f, 0.0f);
		this->_rightUpperArm->setLocalRotation(-0.6f, 0.0f, 0.0f);
		this->_leftForearm->setLocalRotation(-0.3f, 0.0f, 0.0f);
		this->_rightForearm->setLocalRotation(-0.3f, 0.0f, 0.0f);

		this->_leftThigh->setLocalRotation(0.6f, 0.0f, 0.0f);
		this->_rightThigh->setLocalRotation(0.6f, 0.0f, 0.0f);
		this->_leftLowerLeg->setLocalRotation(-0.6f, 0.0f, 0.0f);
		this->_rightLowerLeg->setLocalRotation(-0.6f, 0.0f, 0.0f);
	}
}

void Character::draw(MatrixStack &stack, const Matrix4 &view_proj) const {
	if (!this->_torso)
		return;
	this->_torso->draw(stack, view_proj);
}
