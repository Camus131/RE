#include "PerspectiveCamera.h"


namespace OGE
{
    PerspectiveCamera::PerspectiveCamera(const Vec3& eye, const Vec3& target, const Vec3& up, value_type fov, value_type ratio,
        value_type near_dis, value_type far_dis, value_type moving_speed, value_type turning_speed) :
        Frustum(fov, ratio, near_dis, far_dis)
    {
        name_ = OGE_PerspectiveCamera;

		init_eye_ = eye;
		init_front_ = (target - eye).Normalize();
		init_up_ = Vec3::Normalize(up);
		eye_ = init_eye_;
		rotate_angles_.Zero();
		SetFov(fov);
		SetMovingSpeed(moving_speed);
		SetTurningSpeed(turning_speed);
		ComputePos();
		ComputeWorldPlanes();
    }


	void PerspectiveCamera::SetMovingSpeed(value_type speed)
	{
		moving_speed_ = speed;
		if (moving_speed_ < 1.0f)
			moving_speed_ = 1.0f;
		if (moving_speed_ > 5.0f)
			moving_speed_ = 5.0f;
	}


	void PerspectiveCamera::SetTurningSpeed(value_type speed)
	{
		turning_speed_ = speed;
		if (turning_speed_ < 0.1f)
			turning_speed_ = 0.1f;
		if (turning_speed_ > 0.5f)
			turning_speed_ = 0.5f;
	}


	void PerspectiveCamera::Move(Dir direction, value_type frame_time)
	{
		value_type time = frame_time * moving_speed_;
		switch (direction)
		{
		case FORWARD:
			eye_ += front_ * time;
			break;
		case BACKWARD:
			eye_ -= front_ * time;
			break;
		case LEFT:
			eye_ -= right_ * time;
			break;
		case RIGHT:
			eye_ += right_ * time;
			break;
		}

		//限定移动平面
		eye_.y() = 0.5f;
	}


	void PerspectiveCamera::Turn(value_type xoffset, value_type yoffset)
	{
		xoffset *= turning_speed_;
		yoffset *= turning_speed_;

		rotate_angles_.yaw() += xoffset;
		rotate_angles_.pitch() += yoffset;
		if (rotate_angles_.pitch() > 89.0f)
			rotate_angles_.pitch() = 89.0f;
		if (rotate_angles_.pitch() < -89.0f)
			rotate_angles_.pitch() = -89.0f;

		ComputePos();
	}


	void PerspectiveCamera::Reset()
	{
		eye_ = init_eye_;
		rotate_angles_.Zero();
		ComputePos();
	}


	void PerspectiveCamera::ComputeWorldPlanes()
	{
		ComputePlanes();

		Matrix view_matrix = ViewMatrix();

		near_plane_world_ = near_plane_;
		far_plane_world_ = far_plane_;
		bottom_plane_world_ = bottom_plane_;
		top_plane_world_ = top_plane_;
		left_plane_world_ = left_plane_;
		right_plane_world_ = right_plane_;

		near_plane_world_.TransformByPreInverse(view_matrix);
		far_plane_world_.TransformByPreInverse(view_matrix);
		bottom_plane_world_.TransformByPreInverse(view_matrix);
		top_plane_world_.TransformByPreInverse(view_matrix);
		left_plane_world_.TransformByPreInverse(view_matrix);
		right_plane_world_.TransformByPreInverse(view_matrix);
	}


	bool PerspectiveCamera::Intersect(const BoundingBox& bb)
	{
		if (near_plane_world_.Intersect(bb) == 1 || far_plane_world_.Intersect(bb) == 1 || bottom_plane_world_.Intersect(bb) == 1 ||
			top_plane_world_.Intersect(bb) == 1 || left_plane_world_.Intersect(bb) == 1 || right_plane_world_.Intersect(bb) == 1)
			return false;
		return true;
	}


	void PerspectiveCamera::ComputePos()
	{
		front_ = rotate_angles_.ComputeMatrix() * init_front_;
		right_ = front_ ^ init_up_;
		up_ = right_ ^ front_;
	}
}