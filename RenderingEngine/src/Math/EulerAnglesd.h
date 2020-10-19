#pragma once

#include "Matrixd.h"
#include "EulerAnglesf.h"


namespace OGE
{
	class EulerAnglesd
	{
	public:
		typedef double value_type;

		EulerAnglesd() :
			yaw_(0.0), pitch_(0.0), roll_(0.0) {}

		EulerAnglesd(const EulerAnglesd& ea) :
			yaw_(ea.yaw_), pitch_(ea.pitch_), roll_(ea.roll_) {}

		EulerAnglesd(const EulerAnglesf& ea) :
			yaw_(ea.yaw()), pitch_(ea.pitch()), roll_(ea.roll()) {}

		EulerAnglesd(const Vec3d& v) :
			yaw_(v.x()), pitch_(v.y()), roll_(v.z()) {}

		EulerAnglesd(const Vec3f& v) :
			yaw_(v.x()), pitch_(v.y()), roll_(v.z()) {}

		EulerAnglesd(value_type yaw, value_type pitch, value_type roll) :
			yaw_(yaw), pitch_(pitch), roll_(roll) {}

		//��������
		void Set(const EulerAnglesd& ea) { yaw_ = ea.yaw_; pitch_ = ea.pitch_; roll_ = ea.roll_; }
		void Set(const EulerAnglesf& ea) { yaw_ = ea.yaw(); pitch_ = ea.pitch(); roll_ = ea.roll(); }
		void Set(const Vec3d& v) { yaw_ = v.x(); pitch_ = v.y(); roll_ = v.z(); }
		void Set(const Vec3f& v) { yaw_ = v.x(); pitch_ = v.y(); roll_ = v.z(); }
		void Set(value_type yaw, value_type pitch, value_type roll) { yaw_ = yaw; pitch_ = pitch; roll_ = roll; }

		//����
		void Zero() { yaw_ = pitch_ = roll_ = 0.0; }

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

		//������ŷ�������ɵľ���
		Matrixd ComputeMatrix() const 
		{ 
			return Matrixd::Rotate(yaw_, Y_AXIS) * Matrixd::Rotate(pitch_, X_AXIS) * Matrixd::Rotate(roll_, Z_AXIS); 
		}

		//����������ʽ
		Vec3d ToVec3() const { return Vec3d(yaw_, pitch_, roll_); }

		EulerAnglesd& operator = (const EulerAnglesd& ea)
		{
			if (&ea == this)
				return *this;
			yaw_ = ea.yaw_;
			pitch_ = ea.pitch_;
			roll_ = ea.roll_;
			return *this;
		}

		EulerAnglesd& operator = (const EulerAnglesf& ea)
		{
			yaw_ = ea.yaw();
			pitch_ = ea.pitch();
			roll_ = ea.roll();
			return *this;
		}

		EulerAnglesd& operator = (const Vec3d& v)
		{
			yaw_ = v.x();
			pitch_ = v.y();
			roll_ = v.z();
			return *this;
		}

		EulerAnglesd& operator = (const Vec3f& v)
		{
			yaw_ = v.x();
			pitch_ = v.y();
			roll_ = v.z();
			return *this;
		}

		EulerAnglesd operator - () const { return EulerAnglesd(-yaw_, -pitch_, -roll_); }

		bool operator == (const EulerAnglesd& ea) const { return OGE::IsEqual(yaw_, ea.yaw_) && OGE::IsEqual(pitch_, ea.pitch_) && OGE::IsEqual(roll_, ea.roll_); }

		bool operator != (const EulerAnglesd& ea) const { return !OGE::IsEqual(yaw_, ea.yaw_) || !OGE::IsEqual(pitch_, ea.pitch_) || !OGE::IsEqual(roll_, ea.roll_); }

	protected:
		//�����Ƕ��ԽǶ�ֵ���棬Ӧ��˳��Ϊyaw-pitch-roll
		//ƫ����
		value_type		yaw_;
		//������
		value_type		pitch_;
		//���ֽ�
		value_type		roll_;
	};
}