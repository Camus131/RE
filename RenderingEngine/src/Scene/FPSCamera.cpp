#include "FPSCamera.h"


namespace OGE
{
	FPSCamera::FPSCamera(const Vec3& position, const Vec3& target, const Vec3& up, float fov, float movement_speed, float sensitivity)
	{
		default_position_ = position;
		default_front_ = (target - position).Normalize();
		default_up_ = Vec3::Normalize(up);
		position_ = default_position_;
		euler_angles_.Identity();
		SetFov(fov);
		SetSpeed(movement_speed);
		SetSensitivity(sensitivity);
		Update();
	}


	void FPSCamera::Move(Dir direction, float frame_time)
	{
		float time = frame_time * movement_speed_;
		switch (direction)
		{
		case FORWARD:
			position_ += front_ * time;
			break;
		case BACKWARD:
			position_ -= front_ * time;
			break;
		case LEFT:
			position_ -= right_ * time;
			break;
		case RIGHT:
			position_ += right_ * time;
			break;
		}
		position_.y() = 0.5f;
	}


	void FPSCamera::Turn(float xoffset, float yoffset)
	{
		xoffset *= sensitivity_;
		yoffset *= sensitivity_;

		euler_angles_.yaw_ += xoffset;
		euler_angles_.pitch_ += yoffset;

		if (euler_angles_.pitch_ > 89.0f)
			euler_angles_.pitch_ = 89.0f;
		if (euler_angles_.pitch_ < -89.0f)
			euler_angles_.pitch_ = -89.0f;

		Update();
	}


	void FPSCamera::Reset()
	{
		position_ = default_position_;
		euler_angles_.Identity();
		Update();
	}


	void FPSCamera::SetFov(float fov)
	{
		fov_ = fov;
		if (fov_ < 1.0f)
			fov_ = 1.0f;
		if (fov_ > 90.0f)
			fov_ = 90.0f;
	}


	void FPSCamera::SetSpeed(float speed)
	{
		movement_speed_ = speed;
		if (movement_speed_ < 1.0f)
			movement_speed_ = 1.0f;
		if (movement_speed_ > 5.0f)
			movement_speed_ = 5.0f;
	}


	void FPSCamera::SetSensitivity(float sensitivity)
	{
		sensitivity_ = sensitivity;
		if (sensitivity_ < 0.1f)
			sensitivity_ = 0.1f;
		if (sensitivity_ > 0.5f)
			sensitivity_ = 0.5f;
	}


	void FPSCamera::Update()
	{
		front_ = euler_angles_.ToMatrix() * default_front_;
		right_ = front_ ^ default_up_;
		up_ = right_ ^ front_;
	}
}