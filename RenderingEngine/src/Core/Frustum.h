#pragma once

#include "BaseObject.h"

#include "Math/Planef.h"


namespace OGE
{
	class Frustum :public BaseObject
	{
	public:
		typedef float value_type;

		//获得/设置视野
		value_type GetFov() const { return fov_; }
		void SetFov(value_type fov);

		//获得/设置宽高比
		value_type GetRatio() const { return ratio_; }
		void SetRatio(value_type ratio);

		//获得/设置近平面距离
		value_type GetNearDistance() const { return near_dis_; }
		void SetNearDistance(value_type near_dis);

		//获得/设置远平面距离
		value_type GetFarDistance() const { return far_dis_; }
		void SetFarDistance(value_type far_dis);

	protected:
		Frustum(value_type fov, value_type ratio, value_type near_dis, value_type far_dis);

		//计算六个面
		void ComputePlanes();

	protected:
		//视野
		value_type		fov_;
		//宽高比
		value_type		ratio_;
		//近平面距离
		value_type		near_dis_;
		//远平面距离
		value_type		far_dis_;

		//是否重新计算面的标记
		bool			is_compute_planes_;

		//六个面
		Plane			near_plane_;
		Plane			far_plane_;
		Plane			bottom_plane_;
		Plane			top_plane_;
		Plane			left_plane_;
		Plane			right_plane_;
	};
}