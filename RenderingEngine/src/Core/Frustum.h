#pragma once

#include "BaseObject.h"

#include "Math/Planef.h"


namespace OGE
{
	class Frustum :public BaseObject
	{
	public:
		typedef float value_type;

		//���/������Ұ
		value_type GetFov() const { return fov_; }
		void SetFov(value_type fov);

		//���/���ÿ�߱�
		value_type GetRatio() const { return ratio_; }
		void SetRatio(value_type ratio);

		//���/���ý�ƽ�����
		value_type GetNearDistance() const { return near_dis_; }
		void SetNearDistance(value_type near_dis);

		//���/����Զƽ�����
		value_type GetFarDistance() const { return far_dis_; }
		void SetFarDistance(value_type far_dis);

	protected:
		Frustum(value_type fov, value_type ratio, value_type near_dis, value_type far_dis);

		//����������
		void ComputePlanes();

	protected:
		//��Ұ
		value_type		fov_;
		//��߱�
		value_type		ratio_;
		//��ƽ�����
		value_type		near_dis_;
		//Զƽ�����
		value_type		far_dis_;

		//�Ƿ����¼�����ı��
		bool			is_compute_planes_;

		//������
		Plane			near_plane_;
		Plane			far_plane_;
		Plane			bottom_plane_;
		Plane			top_plane_;
		Plane			left_plane_;
		Plane			right_plane_;
	};
}