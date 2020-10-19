#pragma once

#include "Matrixf.h"


namespace OGE
{
	class EulerAnglesf
	{
	public:
		typedef float value_type;

		EulerAnglesf() :
			yaw_(0.0f), pitch_(0.0f), roll_(0.0f) {}

		EulerAnglesf(const EulerAnglesf& ea) :
			yaw_(ea.yaw_), pitch_(ea.pitch_), roll_(ea.roll_) {}

		EulerAnglesf(const Vec3f& v) :
			yaw_(v.x()), pitch_(v.y()), roll_(v.z()) {}

		EulerAnglesf(value_type yaw, value_type pitch, value_type roll) :
			yaw_(yaw), pitch_(pitch), roll_(roll) {}

		//��������
		void Set(const EulerAnglesf& ea) { yaw_ = ea.yaw_; pitch_ = ea.pitch_; roll_ = ea.roll_; }
		void Set(value_type yaw, value_type pitch, value_type roll) { yaw_ = yaw; pitch_ = pitch; roll_ = roll; }
		void Set(const Vec3f& v) { yaw_ = v.x(); pitch_ = v.y(); roll_ = v.z(); }

		//����
		void Zero() { yaw_ = pitch_ = roll_ = 0.0f; }

		//����true��ʾ�������ݾ��Ϸ�
		bool IsValid() const { return !IsNaN(); }

		//����true��ʾ������������һ��ֵ�ǷǷ���
		bool IsNaN() const { return OGE::IsNaN(yaw_) || OGE::IsNaN(pitch_) || OGE::IsNaN(roll_); }

		//ȡֵ
		value_type& yaw() { return yaw_; }
		value_type& pitch() { return pitch_; }
		value_type& roll() { return roll_; }
		value_type  yaw() const { return yaw_; }
		value_type  pitch() const { return pitch_; }
		value_type  roll() const { return roll_; }

		//������ŷ���Ǽ���ľ���
		Matrixf ComputeMatrix() const 
		{ 
			return Matrixf::Rotate(yaw_, Y_AXIS) * Matrixf::Rotate(pitch_, X_AXIS) * Matrixf::Rotate(roll_, Z_AXIS); 
		}

		//����������ʽ
		Vec3f ToVec3() const { return Vec3f(yaw_, pitch_, roll_); }

		EulerAnglesf& operator = (const EulerAnglesf& ea)
		{
			if (&ea == this)
				return *this;
			yaw_ = ea.yaw_;
			pitch_ = ea.pitch_;
			roll_ = ea.roll_;
			return *this;
		}

		EulerAnglesf& operator = (const Vec3f& v)
		{
			yaw_ = v.x();
			pitch_ = v.y();
			roll_ = v.z();
			return *this;
		}

		EulerAnglesf operator - () const { return EulerAnglesf(-yaw_, -pitch_, -roll_); }

		bool operator == (const EulerAnglesf& ea) const 
		{ 
			return OGE::IsEqual(yaw_, ea.yaw_) && OGE::IsEqual(pitch_, ea.pitch_) && OGE::IsEqual(roll_, ea.roll_); 
		}

		bool operator != (const EulerAnglesf& ea) const 
		{ 
			return !OGE::IsEqual(yaw_, ea.yaw_) || !OGE::IsEqual(pitch_, ea.pitch_) || !OGE::IsEqual(roll_, ea.roll_); 
		}

	protected:
		//�����Ƕ��ԽǶ�ֵ���棬Ӧ��˳��Ϊyaw-pitch-roll
		//ƫ����
		value_type		yaw_;
		//������
		value_type		pitch_;
		//���ֽ�
		value_type		roll_;
	};

	typedef EulerAnglesf EulerAngles;
}