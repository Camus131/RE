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

		//重置内容
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

		//单位化置零
		void Identity()
		{
			yaw_ = 0.0f;
			pitch_ = 0.0f;
			roll_ = 0.0f;
		}

		//返回true表示所有数据均合法
		bool IsValid() const { return !IsNaN(); }

		//返回true表示数据中至少有一个值是非法的
		bool IsNaN() const { return OGE::IsNaN(yaw_) || OGE::IsNaN(pitch_) || OGE::IsNaN(roll_); }

		//返回由欧拉角生成的矩阵
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
		//三个角都以角度值储存，应用顺序为yaw-pitch-roll
		//偏航角
		value_type		yaw_;
		//俯仰角
		value_type		pitch_;
		//滚轮角
		value_type		roll_;
	};
}