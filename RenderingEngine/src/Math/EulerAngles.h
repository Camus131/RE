#pragma once

#include "Matrixd.h"


namespace OGE
{
	class EulerAngles
	{
	public:
		typedef double value_type;

		EulerAngles() :
			yaw_(0.0), pitch_(0.0), roll_(0.0) {}

		EulerAngles(value_type yaw_angle, value_type pitch_angle, value_type roll_angle) :
			yaw_(yaw_angle), pitch_(pitch_angle), roll_(roll_angle) {}

		EulerAngles(const Vec3f& v) :
			yaw_(v.x()), pitch_(v.y()), roll_(v.z()) {}

		EulerAngles(const Vec3d& v) :
			yaw_(v.x()), pitch_(v.y()), roll_(v.z()) {}

		EulerAngles(const EulerAngles& ea) :
			yaw_(ea.yaw_), pitch_(ea.pitch_), roll_(ea.roll_) {}

		//��������
		void Set(value_type yaw_angle, value_type pitch_angle, value_type roll_angle)
		{
			yaw_ = yaw_angle;
			pitch_ = pitch_angle;
			roll_ = roll_angle;
		}
		void Set(const Vec3f& v)
		{
			yaw_ = v.x();
			pitch_ = v.y();
			roll_ = v.z();
		}
		void Set(const Vec3d& v)
		{
			yaw_ = v.x();
			pitch_ = v.y();
			roll_ = v.z();
		}
		void Set(const EulerAngles& ea)
		{
			yaw_ = ea.yaw_;
			pitch_ = ea.pitch_;
			roll_ = ea.roll_;
		}

		//��λ������
		void Identity()
		{
			yaw_ = 0.0f;
			pitch_ = 0.0f;
			roll_ = 0.0f;
		}

		//����true��ʾ�������ݾ��Ϸ�
		bool IsValid() const { return !IsNaN(); }

		//����true��ʾ������������һ��ֵ�ǷǷ���
		bool IsNaN() const { return OGE::IsNaN(yaw_) || OGE::IsNaN(pitch_) || OGE::IsNaN(roll_); }

		//������ŷ�������ɵľ���
		Matrixd ToMatrix() const { return Matrixd::Rotate(yaw_, Y_AXIS) * Matrixd::Rotate(pitch_, X_AXIS) * Matrixd::Rotate(roll_, Z_AXIS); }

		EulerAngles& operator = (const EulerAngles& ea)
		{
			if (&ea == this)
				return *this;
			yaw_ = ea.yaw_;
			pitch_ = ea.pitch_;
			roll_ = ea.roll_;
			return *this;
		}

		EulerAngles operator - () const { return EulerAngles(-yaw_, -pitch_, -roll_); }

		bool operator == (const EulerAngles& ea) const { return yaw_ == ea.yaw_ && pitch_ == ea.pitch_ && roll_ == ea.roll_; }

		bool operator != (const EulerAngles& ea) const { return yaw_ != ea.yaw_ || pitch_ != ea.pitch_ || roll_ != ea.roll_; }

	public:
		//�����Ƕ��ԽǶ�ֵ���棬Ӧ��˳��Ϊyaw-pitch-roll
		//ƫ����
		value_type		yaw_;
		//������
		value_type		pitch_;
		//���ֽ�
		value_type		roll_;
	};
}