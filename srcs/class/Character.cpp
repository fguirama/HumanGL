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

float lerp(float a, float b, float t);
AnimationFrame calculateFrame(float time_seconds, float fps, int frameCount);

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
		constexpr float fps = 6.0f;
		constexpr int frameCount = 8;

		constexpr float frame_torso[8]           = {-0.2f, -0.3f, -0.1f,  0.0f, -0.2f, -0.3f, -0.1f,  0.0f};
		constexpr float frame_left_thigh[8]      = {-0.5f, -0.2f,  0.2f,  0.8f,  0.9f,  1.3f,  0.0f, -0.3f};
		constexpr float frame_left_lower_leg[8]  = { 0.0f, -1.0f, -1.0f, -1.5f,  0.0f, -1.2f,  0.0f,  0.0f};
		constexpr float frame_left_foot[8]       = { 0.0f,  0.1f, -0.2f, -0.1f,  0.0f,  0.1f,  0.0f, -0.3f};
		constexpr float	frame_right_thigh[8]     = { 0.9f,  1.3f,  0.0f, -0.3f, -0.5f, -0.2f,  0.2f,  0.8f};
		constexpr float frame_right_lower_leg[8] = { 0.0f, -1.2f,  0.0f,  0.0f,  0.0f, -1.0f, -1.0f, -1.5f};
		constexpr float frame_rightFoot[8]       = { 0.0f,  0.1f,  0.0f, -0.2f,  0.0f,  0.1f, -0.2f, -0.1f};

		auto [idx0, idx1, t] = calculateFrame(time_seconds, fps, frameCount);

		this->_torso->setLocalRotation(lerp(frame_torso[idx0], frame_torso[idx1], t), 0.0f, 0.0f);
		this->_leftThigh->setLocalRotation(lerp(frame_left_thigh[idx0], frame_left_thigh[idx1], t), 0.0f, 0.0f);
		this->_rightThigh->setLocalRotation(lerp(frame_right_thigh[idx0], frame_right_thigh[idx1], t), 0.0f, 0.0f);

		this->_leftLowerLeg->setLocalRotation(lerp(frame_left_lower_leg[idx0], frame_left_lower_leg[idx1], t), 0.0f, 0.0f);
		this->_rightLowerLeg->setLocalRotation(lerp(frame_right_lower_leg[idx0], frame_right_lower_leg[idx1], t), 0.0f, 0.0f);

		this->_leftFoot->setLocalRotation(lerp(frame_left_foot[idx0], frame_left_foot[idx1], t), 0.0f, 0.0f);
		this->_rightFoot->setLocalRotation(lerp(frame_rightFoot[idx0], frame_rightFoot[idx1], t), 0.0f, 0.0f);

		const float cosValue = std::cos(time_seconds * fps);
		const float bend = 0.6f * cosValue;

		this->_leftUpperArm->setLocalRotation(bend, 0.0f, 0.0f);
		this->_rightUpperArm->setLocalRotation(-bend, 0.0f, 0.0f);
		this->_leftForearm->setLocalRotation(0.6f, 0.0f, 0.0f);
		this->_rightForearm->setLocalRotation(0.6f, 0.0f, 0.0f);
	}

	if (state == AnimationState::Jump) {
		constexpr float fps = 2.0f;
		constexpr int frameCount = 8;

		constexpr float position_torso[8]        = { 0.0f, -1.5f,  0.5f,  2.0f,  0.5f, -1.5f,  0.0f, 0.0f};
		constexpr float frame_torso[8]           = { 0.0f, -0.8f, -0.1f, -0.4f,  0.1f, -0.8f,  0.1f, 0.0f};
		constexpr float frame_right_thigh[8]     = { 0.1f,  2.2f, -0.1f,  2.0f,  0.5f,  2.2f,  0.1f, 0.0f};
		constexpr float frame_right_lower_leg[8] = {-0.2f, -2.2f, -0.2f, -2.0f, -0.3f, -2.2f, -0.3f, 0.0f};
		constexpr float frame_right_foot[8]      = { 0.1f,  0.5f, -0.9f, -0.2f, -0.3f,  0.5f,  0.0f, 0.0f};
		constexpr float frame_left_thigh[8]      = { 0.0f,  2.4f, -0.1f,  1.5f,  0.6f,  0.8f, -0.1f, 0.0f};
		constexpr float frame_left_lower_leg[8]  = { 0.0f, -2.2f, -0.2f, -2.0f, -0.3f, -2.2f, -0.3f, 0.0f};
		constexpr float frame_left_foot[8]       = {-0.1f,  0.6f, -0.9f,  0.0f, -0.3f,  1.0f,  0.0f, 0.0f};
		constexpr float	frame_z_arm[8]           = { 0.0f,  0.0f,  0.0f,  1.5f,  0.0f,  0.0f,  0.2f, 0.0f};
		constexpr float	frame_left_arm[8]        = { 0.0f, -0.8f,  2.5f, -0.2f,  3.5f,  1.3f, -0.1f, 0.0f};
		constexpr float	frame_right_arm[8]       = { 0.1f, -0.8f,  2.5f, -0.2f,  3.5f, -0.7f, -0.1f, 0.0f};
		constexpr float	frame_forearm[8]         = { 0.0f,  0.8f,  0.5f,  0.0f, -0.5f,  0.0f,  0.1f, 0.0f};

		auto [idx0, idx1, t] = calculateFrame(time_seconds, fps, frameCount);

		this->_torso->setLocalPosition(0.0f, lerp(position_torso[idx0], position_torso[idx1], t), 0.0f);
		this->_torso->setLocalRotation(lerp(frame_torso[idx0], frame_torso[idx1], t), 0.0f, 0.0f);
		this->_leftThigh->setLocalRotation(lerp(frame_left_thigh[idx0], frame_left_thigh[idx1], t), 0.0f, 0.0f);
		this->_rightThigh->setLocalRotation(lerp(frame_right_thigh[idx0], frame_right_thigh[idx1], t), 0.0f, 0.0f);

		this->_leftLowerLeg->setLocalRotation(lerp(frame_left_lower_leg[idx0], frame_left_lower_leg[idx1], t), 0.0f, 0.0f);
		this->_rightLowerLeg->setLocalRotation(lerp(frame_right_lower_leg[idx0], frame_right_lower_leg[idx1], t), 0.0f, 0.0f);

		this->_leftFoot->setLocalRotation(lerp(frame_left_foot[idx0], frame_left_foot[idx1], t), 0.0f, 0.0f);
		this->_rightFoot->setLocalRotation(lerp(frame_right_foot[idx0], frame_right_foot[idx1], t), 0.0f, 0.0f);

		this->_leftUpperArm->setLocalRotation(lerp(frame_left_arm[idx0], frame_left_arm[idx1], t), 0.0f, -lerp(frame_z_arm[idx0], frame_z_arm[idx1], t));
		this->_rightUpperArm->setLocalRotation(lerp(frame_right_arm[idx0], frame_right_arm[idx1], t), 0.0f, lerp(frame_z_arm[idx0], frame_z_arm[idx1], t));
		this->_leftForearm->setLocalRotation(lerp(frame_forearm[idx0], frame_forearm[idx1], t), 0.0f, 0.0f);
		this->_rightForearm->setLocalRotation(lerp(frame_forearm[idx0], frame_forearm[idx1], t), 0.0f, 0.0f);
	}
	if (state == AnimationState::Dance) {
		constexpr float frame_torso[11]           = { 0.0f, -0.05f,  0.2f,  0.05f, -0.2f,  0.05f,  0.2f,  0.05f, -0.2f, -0.05f,  0.2f};
		constexpr float frame_left_thigh[11]      = { 0.0f,  0.10f, -0.4f,  0.05f,  0.4f, -0.05f, -0.4f, -0.05f,  0.4f,  0.05f, -0.4f};
		constexpr float	frame_right_thigh[11]     = { 0.0f,  0.10f, -0.4f,  0.05f,  0.4f, -0.05f, -0.4f, -0.05f,  0.4f,  0.05f, -0.4f};
		constexpr float frame_left_x_arm[11]      = { 0.0f,  0.30f,  0.3f,  0.30f,  0.3f,  0.00f, -0.3f, -0.30f, -0.3f, -0.30f, -0.3f};
		constexpr float frame_right_x_arm[11]     = { 0.0f, -0.30f, -0.3f, -0.30f, -0.3f,  0.00f,  0.3f,  0.30f,  0.3f,  0.30f,  0.3f};
		constexpr float frame_left_z_arm[11]      = {-0.3f,  0.30f, -0.6f,  0.10f,  0.5f,  0.10f, -0.6f,  0.10f,  0.5f,  0.10f, -0.6f};
		constexpr float frame_right_z_arm[11]     = { 0.3f,  0.30f, -0.5f,  0.10f,  0.6f,  0.10f, -0.5f,  0.10f,  0.6f,  0.10f, -0.5f};

		constexpr float fps = 5.0f;
		constexpr int frameCount = 11;
		auto [idx0, idx1, t] = calculateFrame(time_seconds, fps, frameCount);

		this->_torso->setLocalRotation(0.0f, 0.0f, lerp(frame_torso[idx0], frame_torso[idx1], t));
		this->_head->setLocalRotation(0.0f, 0.0f, -lerp(frame_torso[idx0], frame_torso[idx1], t));
		this->_leftFoot->setLocalRotation(0.0f, 0.0f, lerp(frame_torso[idx0], frame_torso[idx1], t));
		this->_rightFoot->setLocalRotation(0.0f, 0.0f, lerp(frame_torso[idx0], frame_torso[idx1], t));
		this->_leftThigh->setLocalRotation(0.0f, 0.0f, lerp(frame_left_thigh[idx0], frame_left_thigh[idx1], t));
		this->_rightThigh->setLocalRotation(0.0f, 0.0f, lerp(frame_right_thigh[idx0], frame_right_thigh[idx1], t));

		this->_leftUpperArm->setLocalRotation(lerp(frame_left_x_arm[idx0], frame_left_x_arm[idx1], t), 0.0f, lerp(frame_left_z_arm[idx0], frame_left_z_arm[idx1], t));
		this->_rightUpperArm->setLocalRotation(lerp(frame_right_x_arm[idx0], frame_right_x_arm[idx1], t), 0.0f, lerp(frame_right_z_arm[idx0], frame_right_z_arm[idx1], t));
	}
}

void Character::draw(MatrixStack &stack, const Matrix4 &view_proj) const {
	if (!this->_torso)
		return;
	this->_torso->draw(stack, view_proj);
}
