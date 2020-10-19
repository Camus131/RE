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

		//重置内容
		void Set(const EulerAnglesd& ea) { yaw_ = ea.yaw_; pitch_ = ea.pitch_; roll_ = ea.roll_; }
		void Set(const EulerAnglesf& ea) { yaw_ = ea.yaw(); pitch_ = ea.pitch(); roll_ = ea.roll(); }
		void Set(const Vec3d& v) { yaw_ = v.x(); pitch_ = v.y(); roll_ = v.z(); }
		void Set(const Vec3f& v) { yaw_ = v.x(); pitch_ = v.y(); roll_ = v.z(); }
		void Set(value_type yaw, value_type pitch, value_type roll) { yaw_ = yaw; pitch_ = pitch; roll_ = roll; }

		//置零
		void Zero() { yaw_ = pitch_ = roll_ = 0.0; }

		//返回true表示所有数据均合法
		bool IsValid() const { return !IsNaN(); }

		//返回true表示数据中至少有一个值是非法的
		bool IsNaN() const { return OGE::IsNaN(yaw_) || OGE::IsNaN(pitch_) || OGE::IsNaN(roll_); }

		//取值
		value_type& yaw() { return yaw_; }
		value_type& pitch() { return pitch_; }
		value_type& roll() { return roll_; }
		value_type  yaw() const { return yaw_; }
		value_type  pitch() const { return pitch_; }
		value_type  roll() const { return roll_; }

		//返回由欧拉角生成的矩阵
		Matrixd ComputeMatrix() const 
		{ 
			return Matrixd::Rotate(yaw_, Y_AXIS) * Matrixd::Rotate(pitch_, X_AXIS) * Matrixd::Rotate(roll_, Z_AXIS); 
		}

		//返回向量形式
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
		//三个角都以角度值储存，应用顺序为yaw-pitch-roll
		//偏航角
		value_type		yaw_;
		//俯仰角
		value_type		pitch_;
		//滚轮角
		value_type		roll_;
	};
}