#include "PerspectiveCamera.h"


namespace OGE
{
    PerspectiveCamera::PerspectiveCamera(const Vec3& eye, const Vec3& target, const Vec3& up, value_type fov, value_type ratio,
        value_type near_dis, value_type far_dis, value_type moving_speed, value_type turning_speed) :
        Frustum(near_dis, far_dis)
    {
        name_ = OGE_PerspectiveCamera;

		SetFov(fov);
		SetRatio(ratio);
		init_eye_ = eye;
		init_front_ = (target - eye).Normalize();
		init_up_ = Vec3::Normalize(up);
		eye_ = init_eye_;
		rotate_angles_.Zero();
		SetMovingSpeed(moving_speed);
		SetTurningSpeed(turning_speed);
		ComputePos();
		ComputePlanes();
    }


	void PerspectiveCamera::SetFov(value_type fov)
	{
		fov_ = fov;
		if (fov_ < 1.0f)
			fov_ = 1.0f;
		if (fov_ > 90.0f)
			fov_ = 90.0f;
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
		//eye_.y() = 0.5f;
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


	void PerspectiveCamera::ComputePlanes()
	{
		value_type ratio = far_dis_ / near_dis_;
		Vec3 near_right_top(OGE::Tan(fov_ / 2) * near_dis_ * ratio_, OGE::Tan(fov_ / 2) * near_dis_, -near_dis_);
		Vec3 near_right_bottom(near_right_top.x(), -near_right_top.y(), near_right_top.z());
		Vec3 near_left_bottom(-near_right_top.x(), -near_right_top.y(), near_right_top.z());
		Vec3 near_left_top(-near_right_top.x(), near_right_top.y(), near_right_top.z());
		Vec3 far_right_top = near_right_top * ratio;
		Vec3 far_right_bottom = near_right_bottom * ratio;
		Vec3 far_left_bottom = near_left_bottom * ratio;
		Vec3 far_left_top = near_left_top * ratio;

		near_plane_.Set(near_right_bottom, near_right_top, near_left_top);
		far_plane_.Set(far_left_bottom, far_left_top, far_right_top);
		bottom_plane_.Set(far_right_bottom, near_right_bottom, near_left_bottom);
		top_plane_.Set(near_right_top, far_right_top, far_left_top);
		left_plane_.Set(near_left_bottom, near_left_top, far_left_top);
		right_plane_.Set(far_right_bottom, far_right_top, near_right_top);

		Matrix view_matrix = ViewMatrix();

		near_plane_.TransformByPreInverse(view_matrix);
		far_plane_.TransformByPreInverse(view_matrix);
		bottom_plane_.TransformByPreInverse(view_matrix);
		top_plane_.TransformByPreInverse(view_matrix);
		left_plane_.TransformByPreInverse(view_matrix);
		right_plane_.TransformByPreInverse(view_matrix);
	}


	bool PerspectiveCamera::Intersect(const BoundingBox& bb)
	{
		if (near_plane_.Intersect(bb) == 1 || far_plane_.Intersect(bb) == 1 || bottom_plane_.Intersect(bb) == 1 ||
			top_plane_.Intersect(bb) == 1 || left_plane_.Intersect(bb) == 1 || right_plane_.Intersect(bb) == 1)
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