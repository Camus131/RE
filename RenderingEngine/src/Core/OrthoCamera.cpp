#include "OrthoCamera.h"


namespace OGE
{
	OrthoCamera::OrthoCamera(const Vec3& eye, const Vec3& target, const Vec3& up, value_type left, value_type right, value_type bottom, value_type top,
		value_type near_dis, value_type far_dis, value_type dragging_speed, value_type turning_speed) :
		Frustum(near_dis, far_dis)
	{
		name_ = OGE_OrthoCamera;

		SetLeft(left);
		SetRight(right);
		SetBottom(bottom);
		SetTop(top);
		init_eye_ = eye;
		init_front_ = (target - eye).Normalize();
		init_up_ = Vec3::Normalize(up);
		eye_ = init_eye_;
		rotate_angles_.Zero();
		SetDraggingSpeed(dragging_speed);
		SetTurningSpeed(turning_speed);
		ComputePos();
		ComputePlanes();
	}


	void OrthoCamera::SetDraggingSpeed(value_type speed)
	{
		dragging_speed_ = speed;
		if (dragging_speed_ < 1.0f)
			dragging_speed_ = 1.0f;
		if (dragging_speed_ > 5.0f)
			dragging_speed_ = 5.0f;
	}


	void OrthoCamera::SetTurningSpeed(value_type speed)
	{
		turning_speed_ = speed;
		if (turning_speed_ < 0.1f)
			turning_speed_ = 0.1f;
		if (turning_speed_ > 0.5f)
			turning_speed_ = 0.5f;
	}


	void OrthoCamera::Scale(value_type offset)
	{
	}


	void OrthoCamera::Move(value_type xoffset, value_type yoffset, value_type frame_time)
	{
	}


	void OrthoCamera::Turn(value_type xoffset, value_type yoffset)
	{
	}


	void OrthoCamera::Reset()
	{
		eye_ = init_eye_;
		rotate_angles_.Zero();
		ComputePos();
	}


	void OrthoCamera::ComputePlanes()
	{
	}


	bool OrthoCamera::Intersect(const BoundingBox& bb)
	{
		if (near_plane_.Intersect(bb) == 1 || far_plane_.Intersect(bb) == 1 || bottom_plane_.Intersect(bb) == 1 ||
			top_plane_.Intersect(bb) == 1 || left_plane_.Intersect(bb) == 1 || right_plane_.Intersect(bb) == 1)
			return false;
		return true;
	}


	void OrthoCamera::ComputePos()
	{
		front_ = rotate_angles_.ComputeMatrix() * init_front_;
		right_ = front_ ^ init_up_;
		up_ = right_ ^ front_;
	}
}