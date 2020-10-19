#pragma once

#include "Leaf.h"


namespace OGE
{
	class Cube :public Leaf
	{
	public:
		friend class NodeVisitor;

		typedef float value_type;

		//����ʵ��
		static SPtr(Cube) Create(const Vec3& center = Vec3(0.0f, 0.5f, 0.0f), value_type x = 1.0f, value_type y = 1.0f, value_type z = 1.0f, bool uv_enable = false)
		{
			return SPtr(Cube)(new Cube(center, x, y, z, uv_enable));
		}

		//���/��������
		Vec3 GetCenter() const { return center_; }
		void SetCenter(const Vec3& center);

		//���/����x���򳤶�
		value_type GetX() const { return x_; }
		void SetX(value_type length);

		//���/����y���򳤶�
		value_type GetY() const { return y_; }
		void SetY(value_type width);

		//���/����z���򳤶�
		value_type GetZ() const { return z_; }
		void SetZ(value_type height);

		//�������uv��������״̬
		bool GetUvEnable() const { return uv_enable_; }
		void SetUvEnable(value_type uv_enable) { uv_enable_ = uv_enable; }

	protected:
		Cube(const Vec3& center = Vec3(0.0f, 0.5f, 0.0f), value_type x = 1.0f, value_type y = 1.0f, value_type z = 1.0f, bool uv_enable = false);

		virtual void UpdateBox();

	protected:
		Vec3			center_;

		value_type		x_;

		value_type		y_;

		value_type		z_;

		bool			uv_enable_;
	};
}