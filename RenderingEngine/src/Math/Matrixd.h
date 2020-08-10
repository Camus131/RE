#pragma once

#include "Vec3d.h"
#include "Matrixf.h"


namespace OGE
{
	class Matrixd
	{
	public:
		typedef double value_type;

		Matrixd() { Identity(); }
		Matrixd(value_type m00, value_type m01, value_type m02, value_type m03,
			value_type m10, value_type m11, value_type m12, value_type m13,
			value_type m20, value_type m21, value_type m22, value_type m23,
			value_type m30, value_type m31, value_type m32, value_type m33)
		{
			Set(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
		}
		Matrixd(const value_type* const ptr) { Set(ptr); }
		Matrixd(const Matrixd& m) { Set(m.Ptr()); }
		Matrixd(const Matrixf& m) { Set(m.Ptr()); }

		//重置内容
		Matrixd& Set(value_type m00, value_type m01, value_type m02, value_type m03,
			value_type m10, value_type m11, value_type m12, value_type m13,
			value_type m20, value_type m21, value_type m22, value_type m23,
			value_type m30, value_type m31, value_type m32, value_type m33)
		{
			SET_ROW(0, m00, m01, m02, m03);
			SET_ROW(1, m10, m11, m12, m13);
			SET_ROW(2, m20, m21, m22, m23);
			SET_ROW(3, m30, m31, m32, m33);
			return *this;
		}
		Matrixd& Set(const value_type* const ptr)
		{
			value_type* m_ptr = (value_type*)m_;
			for (int i = 0; i < 16; ++i)
				m_ptr[i] = ptr[i];
			return *this;
		}
		Matrixd& Set(const Matrixd& m) { return Set(m.Ptr()); }
		Matrixd& Set(const Matrixf& m) { return Set(m.Ptr()); }

		//单位化
		Matrixd& Identity()
		{
			SET_ROW(0, 1.0, 0.0, 0.0, 0.0);
			SET_ROW(1, 0.0, 1.0, 0.0, 0.0);
			SET_ROW(2, 0.0, 0.0, 1.0, 0.0);
			SET_ROW(3, 0.0, 0.0, 0.0, 1.0);
			return *this;
		}

		//返回true表示单位矩阵
		bool IsIdentity() const
		{
			return m_[0][0] == 1.0 && m_[1][0] == 0.0 && m_[2][0] == 0.0 && m_[3][0] == 0.0 &&
				m_[0][1] == 0.0 && m_[1][1] == 1.0 && m_[2][1] == 0.0 && m_[3][1] == 0.0 &&
				m_[0][2] == 0.0 && m_[1][2] == 0.0 && m_[2][2] == 1.0 && m_[3][2] == 0.0 &&
				m_[0][3] == 0.0 && m_[1][3] == 0.0 && m_[2][3] == 0.0 && m_[3][3] == 1.0;
		}

		//返回true表示所有数据均合法
		bool IsValid() const { return !IsNaN(); }

		//返回true表示数据中至少有一个值是非法的
		bool IsNaN() const
		{
			return OGE::IsNaN(m_[0][0]) || OGE::IsNaN(m_[1][0]) || OGE::IsNaN(m_[2][0]) || OGE::IsNaN(m_[3][0]) ||
				OGE::IsNaN(m_[0][1]) || OGE::IsNaN(m_[1][1]) || OGE::IsNaN(m_[2][1]) || OGE::IsNaN(m_[3][1]) ||
				OGE::IsNaN(m_[0][2]) || OGE::IsNaN(m_[1][2]) || OGE::IsNaN(m_[2][2]) || OGE::IsNaN(m_[3][2]) ||
				OGE::IsNaN(m_[0][3]) || OGE::IsNaN(m_[1][3]) || OGE::IsNaN(m_[2][3]) || OGE::IsNaN(m_[3][3]);
		}

		//取地址
		value_type* Ptr() { return (value_type*)m_; }
		const value_type* Ptr() const { return (const value_type*)m_; }

		//取值
		value_type& operator()(int row, int col) { return m_[col][row]; }
		value_type operator()(int row, int col) const { return m_[col][row]; }

		Matrixd& operator = (const Matrixd& m)
		{
			if (&m == this)
				return *this;
			Set(m.Ptr());
			return *this;
		}

		Matrixd& operator = (const Matrixf& m)
		{
			Set(m.Ptr());
			return *this;
		}

		Matrixd operator - () const
		{
			return Matrixd(
				-m_[0][0], -m_[1][0], -m_[2][0], -m_[3][0],
				-m_[0][1], -m_[1][1], -m_[2][1], -m_[3][1],
				-m_[0][2], -m_[1][2], -m_[2][2], -m_[3][2],
				-m_[0][3], -m_[1][3], -m_[2][3], -m_[3][3]);
		}

		//左乘
		Vec3f LeftMulti(const Vec3f& v) const
		{
			float inv = 1.0f / (float)MAT_X_VEC3(*this, v, 3);
			return Vec3f((float)MAT_X_VEC3(*this, v, 0) * inv, (float)MAT_X_VEC3(*this, v, 1) * inv, (float)MAT_X_VEC3(*this, v, 2) * inv);
		}
		Vec3d LeftMulti(const Vec3d& v) const
		{
			value_type inv = 1.0 / MAT_X_VEC3(*this, v, 3);
			return Vec3d(MAT_X_VEC3(*this, v, 0) * inv, MAT_X_VEC3(*this, v, 1) * inv, MAT_X_VEC3(*this, v, 2) * inv);
		}

		//右乘
		Vec3f RightMulti(const Vec3f& v) const
		{
			float inv = 1.0f / (float)VEC3_X_MAT(*this, v, 3);
			return Vec3f((float)VEC3_X_MAT(*this, v, 0) * inv, (float)VEC3_X_MAT(*this, v, 1) * inv, (float)VEC3_X_MAT(*this, v, 2) * inv);
		}
		Vec3d RightMulti(const Vec3d& v) const
		{
			value_type inv = 1.0 / VEC3_X_MAT(*this, v, 3);
			return Vec3d(VEC3_X_MAT(*this, v, 0) * inv, VEC3_X_MAT(*this, v, 1) * inv, VEC3_X_MAT(*this, v, 2) * inv);
		}

		//返回0表示两矩阵相同
		int Compare(const Matrixd& m) const
		{
			const value_type* lhs = (value_type*)m_;
			const value_type* end_lhs = lhs + 16;
			const value_type* rhs = m.Ptr();
			for (; lhs != end_lhs; ++lhs, ++rhs)
			{
				if (!OGE::IsEqual(*lhs, *rhs))
					return -1;
			}
			return 0;
		}

		bool operator == (const Matrixd& m) const { return Compare(m) == 0; }

		bool operator != (const Matrixd& m) const { return Compare(m) != 0; }

		Matrixd operator + (const Matrixd& m) const
		{
			return Matrixd(
				m_[0][0] + m.m_[0][0], m_[1][0] + m.m_[1][0], m_[2][0] + m.m_[2][0], m_[3][0] + m.m_[3][0],
				m_[0][1] + m.m_[0][1], m_[1][1] + m.m_[1][1], m_[2][1] + m.m_[2][1], m_[3][1] + m.m_[3][1],
				m_[0][2] + m.m_[0][2], m_[1][2] + m.m_[1][2], m_[2][2] + m.m_[2][2], m_[3][2] + m.m_[3][2],
				m_[0][3] + m.m_[0][3], m_[1][3] + m.m_[1][3], m_[2][3] + m.m_[2][3], m_[3][3] + m.m_[3][3]);
		}

		Matrixd operator - (const Matrixd& m) const
		{
			return Matrixd(
				m_[0][0] - m.m_[0][0], m_[1][0] - m.m_[1][0], m_[2][0] - m.m_[2][0], m_[3][0] - m.m_[3][0],
				m_[0][1] - m.m_[0][1], m_[1][1] - m.m_[1][1], m_[2][1] - m.m_[2][1], m_[3][1] - m.m_[3][1],
				m_[0][2] - m.m_[0][2], m_[1][2] - m.m_[1][2], m_[2][2] - m.m_[2][2], m_[3][2] - m.m_[3][2],
				m_[0][3] - m.m_[0][3], m_[1][3] - m.m_[1][3], m_[2][3] - m.m_[2][3], m_[3][3] - m.m_[3][3]);
		}

		Matrixd operator * (value_type v) const
		{
			return Matrixd(
				m_[0][0] * v, m_[1][0] * v, m_[2][0] * v, m_[3][0] * v,
				m_[0][1] * v, m_[1][1] * v, m_[2][1] * v, m_[3][1] * v,
				m_[0][2] * v, m_[1][2] * v, m_[2][2] * v, m_[3][2] * v,
				m_[0][3] * v, m_[1][3] * v, m_[2][3] * v, m_[3][3] * v);
		}

		Matrixd operator * (const Matrixd& m) const
		{
			return Matrixd(
				MAT_X_MAT(*this, m, 0, 0), MAT_X_MAT(*this, m, 0, 1), MAT_X_MAT(*this, m, 0, 2), MAT_X_MAT(*this, m, 0, 3),
				MAT_X_MAT(*this, m, 1, 0), MAT_X_MAT(*this, m, 1, 1), MAT_X_MAT(*this, m, 1, 2), MAT_X_MAT(*this, m, 1, 3),
				MAT_X_MAT(*this, m, 2, 0), MAT_X_MAT(*this, m, 2, 1), MAT_X_MAT(*this, m, 2, 2), MAT_X_MAT(*this, m, 2, 3),
				MAT_X_MAT(*this, m, 3, 0), MAT_X_MAT(*this, m, 3, 1), MAT_X_MAT(*this, m, 3, 2), MAT_X_MAT(*this, m, 3, 3));
		}

		Vec3f operator * (const Vec3f& v) const { return LeftMulti(v); }

		Vec3d operator * (const Vec3d& v) const { return LeftMulti(v); }

		Matrixd operator / (value_type v) const
		{
			value_type inv = 1.0 / v;
			return Matrixd(
				m_[0][0] * inv, m_[1][0] * inv, m_[2][0] * inv, m_[3][0] * inv,
				m_[0][1] * inv, m_[1][1] * inv, m_[2][1] * inv, m_[3][1] * inv,
				m_[0][2] * inv, m_[1][2] * inv, m_[2][2] * inv, m_[3][2] * inv,
				m_[0][3] * inv, m_[1][3] * inv, m_[2][3] * inv, m_[3][3] * inv);
		}

		Matrixd& operator += (const Matrixd& m) { return *this = *this + m; }

		Matrixd& operator -= (const Matrixd& m) { return *this = *this - m; }

		Matrixd& operator *= (value_type v) { return *this = *this * v; }

		Matrixd& operator *= (const Matrixd& m) { return *this = *this * m; }

		Matrixd& operator /= (value_type v) { return *this = *this / v; }

		//重置为平移矩阵
		Matrixd& MakeTranslate(value_type x, value_type y, value_type z)
		{
			SET_ROW(0, 1.0, 0.0, 0.0, x);
			SET_ROW(1, 0.0, 1.0, 0.0, y);
			SET_ROW(2, 0.0, 0.0, 1.0, z);
			SET_ROW(3, 0.0, 0.0, 0.0, 1.0);
			return *this;
		}
		Matrixd& MakeTranslate(const Vec3f& v) { return MakeTranslate(v.x(), v.y(), v.z()); }
		Matrixd& MakeTranslate(const Vec3d& v) { return MakeTranslate(v.x(), v.y(), v.z()); }

		//重置为缩放矩阵
		Matrixd& MakeScale(value_type x, value_type y, value_type z)
		{
			SET_ROW(0, x, 0.0, 0.0, 0.0);
			SET_ROW(1, 0.0, y, 0.0, 0.0);
			SET_ROW(2, 0.0, 0.0, z, 0.0);
			SET_ROW(3, 0.0, 0.0, 0.0, 1.0);
			return *this;
		}
		Matrixd& MakeScale(const Vec3f& v) { return MakeScale(v.x(), v.y(), v.z()); }
		Matrixd& MakeScale(const Vec3d& v) { return MakeScale(v.x(), v.y(), v.z()); }

		//重置为旋转矩阵
		Matrixd& MakeRotate(value_type angle, value_type axis_x, value_type axis_y, value_type axis_z)
		{
			Vec3d a(axis_x, axis_y, axis_z);
			a.Normalize();
			value_type x = a.x();
			value_type y = a.y();
			value_type z = a.z();
			value_type c = OGE::Cos(angle);
			value_type s = OGE::Sin(angle);
			value_type k = 1.0 - c;
			SET_ROW(0, x * x * k + c, x * y * k - z * s, x * z * k + y * s, 0.0);
			SET_ROW(1, x * y * k + z * s, y * y * k + c, y * z * k - x * s, 0.0);
			SET_ROW(2, x * z * k - y * s, y * z * k + x * s, z * z * k + c, 0.0);
			SET_ROW(3, 0.0, 0.0, 0.0, 1.0);
			return *this;
		}
		Matrixd& MakeRotate(value_type angle, const Vec3f& axis) { return MakeRotate(angle, axis.x(), axis.y(), axis.z()); }
		Matrixd& MakeRotate(value_type angle, const Vec3d& axis) { return MakeRotate(angle, axis.x(), axis.y(), axis.z()); }

		//重置为视图矩阵
		Matrixd& MakeLookAt(const Vec3f& eye, const Vec3f& target, const Vec3f& up)
		{
			Vec3f b = (eye - target).Normalize();
			Vec3f u = up;
			u.Normalize();
			Vec3f r = u ^ b;
			SET_ROW(0, r.x(), r.y(), r.z(), 0.0);
			SET_ROW(1, u.x(), u.y(), u.z(), 0.0);
			SET_ROW(2, b.x(), b.y(), b.z(), 0.0);
			SET_ROW(3, 0.0, 0.0, 0.0, 1.0);
			return (*this) *= Translate(-eye.x(), -eye.y(), -eye.z());
		}
		Matrixd& MakeLookAt(const Vec3d& eye, const Vec3d& target, const Vec3d& up)
		{
			Vec3d b = (eye - target).Normalize();
			Vec3d u = up;
			u.Normalize();
			Vec3d r = u ^ b;
			SET_ROW(0, r.x(), r.y(), r.z(), 0.0);
			SET_ROW(1, u.x(), u.y(), u.z(), 0.0);
			SET_ROW(2, b.x(), b.y(), b.z(), 0.0);
			SET_ROW(3, 0.0, 0.0, 0.0, 1.0);
			return (*this) *= Translate(-eye.x(), -eye.y(), -eye.z());
		}

		//重置为正交投影矩阵
		Matrixd& MakeOrtho(value_type left, value_type right, value_type bottom, value_type top, value_type near, value_type far)
		{
			value_type w = right - left;
			value_type h = top - bottom;
			value_type d = far - near;
			SET_ROW(0, 2.0 / w, 0.0, 0.0, -(right + left) / w);
			SET_ROW(1, 0.0, 2.0 / h, 0.0, -(top + bottom) / h);
			SET_ROW(2, 0.0, 0.0, -2.0 / d, -(far + near) / d);
			SET_ROW(3, 0.0, 0.0, 0.0, 1.0);
			return *this;
		}

		//重置为透视投影矩阵
		Matrixd& MakePerspective(value_type fov, value_type aspect, value_type near, value_type far)
		{
			value_type c = OGE::Cot(fov / 2);
			value_type d = far - near;
			SET_ROW(0, c / aspect, 0.0, 0.0, 0.0);
			SET_ROW(1, 0.0, c, 0.0, 0.0);
			SET_ROW(2, 0.0, 0.0, -(far + near) / d, -2 * far * near / d);
			SET_ROW(3, 0.0, 0.0, -1.0, 0.0);
			return *this;
		}

		//重置为自身转置矩阵
		Matrixd& MakeTranspose()
		{
			OGE::Swap(m_[1][0], m_[0][1]);
			OGE::Swap(m_[2][0], m_[0][2]);
			OGE::Swap(m_[3][0], m_[0][3]);
			OGE::Swap(m_[2][1], m_[1][2]);
			OGE::Swap(m_[3][1], m_[1][3]);
			OGE::Swap(m_[3][2], m_[2][3]);
			return *this;
		}

		//重置为自身逆矩阵
		bool MakeInverse()
		{
			unsigned int indxc[4], indxr[4], ipiv[4];
			unsigned int i, j, k, l, ll;
			unsigned int icol = 0;
			unsigned int irow = 0;
			value_type pivinv, dum, big;

			for (j = 0; j < 4; j++) ipiv[j] = 0;

			for (i = 0; i < 4; i++)
			{
				big = 0.0;
				for (j = 0; j < 4; ++j)
				{
					if (ipiv[j] != 1)
					{
						for (k = 0; k < 4; k++)
						{
							if (ipiv[k] == 0)
							{
								if (OGE::Absolute(m_[j][k]) >= big)
								{
									big = OGE::Absolute(m_[j][k]);
									irow = j;
									icol = k;
								}
							}
							else if (ipiv[k] > 1)
								return false;
						}
					}
				}
				++(ipiv[icol]);
				if (irow != icol)
					for (l = 0; l < 4; ++l)
						OGE::Swap(m_[irow][l], m_[icol][l]);

				indxr[i] = irow;
				indxc[i] = icol;
				if (m_[icol][icol] == 0)
					return false;

				pivinv = 1.0 / m_[icol][icol];
				m_[icol][icol] = 1;
				for (l = 0; l < 4; ++l)
					m_[icol][l] *= pivinv;
				for (ll = 0; ll < 4; ++ll)
				{
					if (ll != icol)
					{
						dum = m_[ll][icol];
						m_[ll][icol] = 0;
						for (l = 0; l < 4; ++l)
							m_[ll][l] -= m_[icol][l] * dum;
					}
				}
			}
			for (int lx = 4; lx > 0; --lx)
			{
				if (indxr[lx - 1] != indxc[lx - 1])
				{
					for (k = 0; k < 4; k++)
						OGE::Swap(m_[k][indxr[lx - 1]], m_[k][indxc[lx - 1]]);
				}
			}
			return true;
		}

		//平移矩阵
		static Matrixd Translate(value_type x, value_type y, value_type z)
		{
			Matrixd m;
			m.MakeTranslate(x, y, z);
			return m;
		}
		static Matrixd Translate(const Vec3f& v)
		{
			Matrixd m;
			m.MakeTranslate(v);
			return m;
		}
		static Matrixd Translate(const Vec3d& v)
		{
			Matrixd m;
			m.MakeTranslate(v);
			return m;
		}

		//缩放矩阵
		static Matrixd Scale(value_type x, value_type y, value_type z)
		{
			Matrixd m;
			m.MakeScale(x, y, z);
			return m;
		}
		static Matrixd Scale(const Vec3f& v)
		{
			Matrixd m;
			m.MakeScale(v);
			return m;
		}
		static Matrixd Scale(const Vec3d& v)
		{
			Matrixd m;
			m.MakeScale(v);
			return m;
		}

		//旋转矩阵
		static Matrixd Rotate(value_type angle, value_type x, value_type y, value_type z)
		{
			Matrixd m;
			m.MakeRotate(angle, x, y, z);
			return m;
		}
		static Matrixd Rotate(value_type angle, const Vec3f& axis)
		{
			Matrixd m;
			m.MakeRotate(angle, axis);
			return m;
		}
		static Matrixd Rotate(value_type angle, const Vec3d& axis)
		{
			Matrixd m;
			m.MakeRotate(angle, axis);
			return m;
		}

		//视图矩阵
		static Matrixd LookAt(const Vec3f& eye, const Vec3f& target, const Vec3f& up)
		{
			Matrixd m;
			m.MakeLookAt(eye, target, up);
			return m;
		}
		static Matrixd LookAt(const Vec3d& eye, const Vec3d& target, const Vec3d& up)
		{
			Matrixd m;
			m.MakeLookAt(eye, target, up);
			return m;
		}

		//正交投影矩阵
		static Matrixd Ortho(value_type left, value_type right, value_type bottom, value_type top, value_type near, value_type far)
		{
			Matrixd m;
			m.MakeOrtho(left, right, bottom, top, near, far);
			return m;
		}

		//透视投影矩阵
		static Matrixd Perspective(value_type fov, value_type aspect, value_type near, value_type far)
		{
			Matrixd m;
			m.MakePerspective(fov, aspect, near, far);
			return m;
		}

		//转置矩阵
		static Matrixd Transpose(const Matrixd& m)
		{
			Matrixd res = m;
			return res.MakeTranspose();
		}

		//逆矩阵
		static bool Inverse(const Matrixd& m, Matrixd& inv_m)
		{
			inv_m = m;
			return inv_m.MakeInverse();
		}

	private:
		value_type		m_[4][4];
	};
}