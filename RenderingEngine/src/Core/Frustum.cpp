#include "Frustum.h"


namespace OGE
{
	Frustum::Frustum(value_type fov, value_type ratio, value_type near_dis, value_type far_dis) :
		fov_(fov),
		ratio_(ratio),
		near_dis_(near_dis),
		far_dis_(far_dis),
		is_compute_planes_(true)
	{
		ComputePlanes();
	}


	void Frustum::SetFov(value_type fov) 
	{
		if (OGE::IsEqual(fov_, fov))
			return;

		fov_ = fov;
		if (fov_ < 1.0f)
			fov_ = 1.0f;
		if (fov_ > 90.0f)
			fov_ = 90.0f;

		is_compute_planes_ = true;
	}


	void Frustum::SetRatio(value_type ratio) 
	{
		if (OGE::IsEqual(ratio_, ratio))
			return;

		ratio_ = ratio;
		is_compute_planes_ = true;
	}


	void Frustum::SetNearDistance(value_type near_dis) 
	{
		if (OGE::IsEqual(near_dis_, near_dis))
			return;

		near_dis_ = near_dis;
		is_compute_planes_ = true;
	}


	void Frustum::SetFarDistance(value_type far_dis) 
	{
		if (OGE::IsEqual(far_dis_, far_dis))
			return;

		far_dis_ = far_dis;
		is_compute_planes_ = true;
	}


	void Frustum::ComputePlanes()
	{
		if (!is_compute_planes_)
			return;

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

		is_compute_planes_ = false;
	}
}