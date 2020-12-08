#pragma once

#include "BaseObject.h"

#include "Math/Planef.h"


namespace OGE
{
	class Frustum :public BaseObject
	{
	public:
		typedef float value_type;

		//���/���ý�ƽ�����
		value_type GetNearDistance() const { return near_dis_; }
		void SetNearDistance(value_type near_dis) { near_dis_ = near_dis; }

		//���/����Զƽ�����
		value_type GetFarDistance() const { return far_dis_; }
		void SetFarDistance(value_type far_dis) { far_dis_ = far_dis; }

	protected:
		Frustum(value_type near_dis, value_type far_dis) :
			BaseObject(),
			near_dis_(near_dis),
			far_dis_(far_dis) {}

	protected:
		//��ƽ�����
		value_type		near_dis_;

		//Զƽ�����
		value_type		far_dis_;

		//������
		Plane			near_plane_;
		Plane			far_plane_;
		Plane			bottom_plane_;
		Plane			top_plane_;
		Plane			left_plane_;
		Plane			right_plane_;
	};
}