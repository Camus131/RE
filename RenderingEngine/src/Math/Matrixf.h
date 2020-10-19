#pragma once

#include "Vec4f.h"


namespace OGE
{
#define SET_ROW(row,v1,v2,v3,v4) \
m_[0][(row)] = (v1); \
m_[1][(row)] = (v2); \
m_[2][(row)] = (v3); \
m_[3][(row)] = (v4)

#define MAT_X_MAT(m1,m2,r,c) \
(((m1).m_[0][(r)]*(m2).m_[(c)][0])+ \
((m1).m_[1][(r)]*(m2).m_[(c)][1])+ \
((m1).m_[2][(r)]*(m2).m_[(c)][2])+ \
((m1).m_[3][(r)]*(m2).m_[(c)][3]))

#define MAT_X_VEC3(m,v,r) \
(((m).m_[0][(r)]*(v)[0])+ \
((m).m_[1][(r)]*(v)[1])+ \
((m).m_[2][(r)]*(v)[2])+ \
((m).m_[3][(r)]))

#define VEC3_X_MAT(m,v,r) \
(((m).m_[(r)][0]*(v)[0])+ \
((m).m_[(r)][1]*(v)[1])+ \
((m).m_[(r)][2]*(v)[2])+ \
((m).m_[(r)][3]))

#define MAT_X_VEC4(m,v,r) \
(((m).m_[0][(r)]*(v)[0])+ \
((m).m_[1][(r)]*(v)[1])+ \
((m).m_[2][(r)]*(v)[2])+ \
((m).m_[3][(r)]*(v)[3]))

#define VEC4_X_MAT(m,v,r) \
(((m).m_[(r)][0]*(v)[0])+ \
((m).m_[(r)][1]*(v)[1])+ \
((m).m_[(r)][2]*(v)[2])+ \
((m).m_[(r)][3]*(v)[3]))

	class Matrixf
	{
	public:
		typedef float value_type;

		Matrixf()
		{
			SET_ROW(0, 1.0f, 0.0f, 0.0f, 0.0f);
			SET_ROW(1, 0.0f, 1.0f, 0.0f, 0.0f);
			SET_ROW(2, 0.0f, 0.0f, 1.0f, 0.0f);
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrixf(const Matrixf& m) 
		{ 
			value_type* m_ptr = Ptr();
			const value_type* ptr = m.Ptr();
			for (int i = 0; i < 16; ++i)
				m_ptr[i] = ptr[i];
		}

		Matrixf(const value_type* const ptr)
		{
			value_type* m_ptr = Ptr();
			for (int i = 0; i < 16; ++i)
				m_ptr[i] = ptr[i];
		}

		Matrixf(value_type m00, value_type m01, value_type m02, value_type m03,
			value_type m10, value_type m11, value_type m12, value_type m13,
			value_type m20, value_type m21, value_type m22, value_type m23,
			value_type m30, value_type m31, value_type m32, value_type m33)
		{
			SET_ROW(0, m00, m01, m02, m03);
			SET_ROW(1, m10, m11, m12, m13);
			SET_ROW(2, m20, m21, m22, m23);
			SET_ROW(3, m30, m31, m32, m33);
		}

		//重置内容
		Matrixf& Set(const Matrixf& m) { return Set(m.Ptr()); }
		Matrixf& Set(const value_type* const ptr)
		{
			value_type* m_ptr = Ptr();
			for (int i = 0; i < 16; ++i)
				m_ptr[i] = ptr[i];
			return *this;
		}
		Matrixf& Set(value_type m00, value_type m01, value_type m02, value_type m03,
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

		//单位化
		Matrixf& Identity()
		{
			SET_ROW(0, 1.0f, 0.0f, 0.0f, 0.0f);
			SET_ROW(1, 0.0f, 1.0f, 0.0f, 0.0f);
			SET_ROW(2, 0.0f, 0.0f, 1.0f, 0.0f);
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
			return *this;
		}

		//返回true表示单位矩阵
		bool IsIdentity() const
		{
			return OGE::IsEqual(m_[0][0], 1.0f) && OGE::IsEqual(m_[1][0], 0.0f) && OGE::IsEqual(m_[2][0], 0.0f) && OGE::IsEqual(m_[3][0], 0.0f) &&
				OGE::IsEqual(m_[0][1], 0.0f) && OGE::IsEqual(m_[1][1], 1.0f) && OGE::IsEqual(m_[2][1], 0.0f) && OGE::IsEqual(m_[3][1], 0.0f) &&
				OGE::IsEqual(m_[0][2], 0.0f) && OGE::IsEqual(m_[1][2], 0.0f) && OGE::IsEqual(m_[2][2], 1.0f) && OGE::IsEqual(m_[3][2], 0.0f) &&
				OGE::IsEqual(m_[0][3], 0.0f) && OGE::IsEqual(m_[1][3], 0.0f) && OGE::IsEqual(m_[2][3], 0.0f) && OGE::IsEqual(m_[3][3], 1.0f);
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
		value_type& operator()(unsigned int row, unsigned int col) { return m_[col][row]; }
		value_type operator()(unsigned int row, unsigned int col) const { return m_[col][row]; }

		Matrixf& operator = (const Matrixf& m)
		{
			if (&m == this)
				return *this;
			return Set(m.Ptr());
		}

		Matrixf operator - () const
		{
			return Matrixf(
				-m_[0][0], -m_[1][0], -m_[2][0], -m_[3][0],
				-m_[0][1], -m_[1][1], -m_[2][1], -m_[3][1],
				-m_[0][2], -m_[1][2], -m_[2][2], -m_[3][2],
				-m_[0][3], -m_[1][3], -m_[2][3], -m_[3][3]);
		}

		//返回0表示两矩阵相同
		int Compare(const Matrixf& m) const
		{
			const value_type* lhs = Ptr();
			const value_type* end_lhs = lhs + 16;
			const value_type* rhs = m.Ptr();
			for (; lhs != end_lhs; ++lhs, ++rhs)
			{
				if (!OGE::IsEqual(*lhs, *rhs))
					return -1;
			}
			return 0;
		}

		bool operator == (const Matrixf& m) const { return Compare(m) == 0; }

		bool operator != (const Matrixf& m) const { return Compare(m) != 0; }

		Matrixf operator + (const Matrixf& m) const
		{
			return Matrixf(
				m_[0][0] + m.m_[0][0], m_[1][0] + m.m_[1][0], m_[2][0] + m.m_[2][0], m_[3][0] + m.m_[3][0],
				m_[0][1] + m.m_[0][1], m_[1][1] + m.m_[1][1], m_[2][1] + m.m_[2][1], m_[3][1] + m.m_[3][1],
				m_[0][2] + m.m_[0][2], m_[1][2] + m.m_[1][2], m_[2][2] + m.m_[2][2], m_[3][2] + m.m_[3][2],
				m_[0][3] + m.m_[0][3], m_[1][3] + m.m_[1][3], m_[2][3] + m.m_[2][3], m_[3][3] + m.m_[3][3]);
		}

		Matrixf operator - (const Matrixf& m) const
		{
			return Matrixf(
				m_[0][0] - m.m_[0][0], m_[1][0] - m.m_[1][0], m_[2][0] - m.m_[2][0], m_[3][0] - m.m_[3][0],
				m_[0][1] - m.m_[0][1], m_[1][1] - m.m_[1][1], m_[2][1] - m.m_[2][1], m_[3][1] - m.m_[3][1],
				m_[0][2] - m.m_[0][2], m_[1][2] - m.m_[1][2], m_[2][2] - m.m_[2][2], m_[3][2] - m.m_[3][2],
				m_[0][3] - m.m_[0][3], m_[1][3] - m.m_[1][3], m_[2][3] - m.m_[2][3], m_[3][3] - m.m_[3][3]);
		}

		Matrixf operator * (value_type v) const
		{
			return Matrixf(
				m_[0][0] * v, m_[1][0] * v, m_[2][0] * v, m_[3][0] * v,
				m_[0][1] * v, m_[1][1] * v, m_[2][1] * v, m_[3][1] * v,
				m_[0][2] * v, m_[1][2] * v, m_[2][2] * v, m_[3][2] * v,
				m_[0][3] * v, m_[1][3] * v, m_[2][3] * v, m_[3][3] * v);
		}

		Matrixf operator * (const Matrixf& m) const
		{
			return Matrixf(
				MAT_X_MAT(*this, m, 0, 0), MAT_X_MAT(*this, m, 0, 1), MAT_X_MAT(*this, m, 0, 2), MAT_X_MAT(*this, m, 0, 3),
				MAT_X_MAT(*this, m, 1, 0), MAT_X_MAT(*this, m, 1, 1), MAT_X_MAT(*this, m, 1, 2), MAT_X_MAT(*this, m, 1, 3),
				MAT_X_MAT(*this, m, 2, 0), MAT_X_MAT(*this, m, 2, 1), MAT_X_MAT(*this, m, 2, 2), MAT_X_MAT(*this, m, 2, 3),
				MAT_X_MAT(*this, m, 3, 0), MAT_X_MAT(*this, m, 3, 1), MAT_X_MAT(*this, m, 3, 2), MAT_X_MAT(*this, m, 3, 3));
		}

		//左乘
		Vec3f LeftMulti(const Vec3f& v) const
		{
			value_type inv = 1.0f / MAT_X_VEC3(*this, v, 3);
			return Vec3f(MAT_X_VEC3(*this, v, 0) * inv, MAT_X_VEC3(*this, v, 1) * inv, MAT_X_VEC3(*this, v, 2) * inv);
		}
		Vec4f LeftMulti(const Vec4f& v) const
		{
			return Vec4f(MAT_X_VEC4(*this, v, 0), MAT_X_VEC4(*this, v, 1), MAT_X_VEC4(*this, v, 2), MAT_X_VEC4(*this, v, 3));
		}

		//右乘
		Vec3f RightMulti(const Vec3f& v) const
		{
			value_type inv = 1.0f / VEC3_X_MAT(*this, v, 3);
			return Vec3f(VEC3_X_MAT(*this, v, 0) * inv, VEC3_X_MAT(*this, v, 1) * inv, VEC3_X_MAT(*this, v, 2) * inv);
		}
		Vec4f RightMulti(const Vec4f& v) const
		{
			return Vec4f(VEC4_X_MAT(*this, v, 0), VEC4_X_MAT(*this, v, 1), VEC4_X_MAT(*this, v, 2), VEC4_X_MAT(*this, v, 3));
		}

		Vec3f operator * (const Vec3f& v) const { return LeftMulti(v); }

		Vec4f operator * (const Vec4f& v) const { return LeftMulti(v); }

		Matrixf operator / (value_type v) const
		{
			value_type inv = 1.0f / v;
			return Matrixf(
				m_[0][0] * inv, m_[1][0] * inv, m_[2][0] * inv, m_[3][0] * inv,
				m_[0][1] * inv, m_[1][1] * inv, m_[2][1] * inv, m_[3][1] * inv,
				m_[0][2] * inv, m_[1][2] * inv, m_[2][2] * inv, m_[3][2] * inv,
				m_[0][3] * inv, m_[1][3] * inv, m_[2][3] * inv, m_[3][3] * inv);
		}

		Matrixf& operator += (const Matrixf& m) { return *this = *this + m; }

		Matrixf& operator -= (const Matrixf& m) { return *this = *this - m; }

		Matrixf& operator *= (value_type v) { return *this = *this * v; }

		Matrixf& operator *= (const Matrixf& m) { return *this = *this * m; }

		Matrixf& operator /= (value_type v) { return *this = *this / v; }

		//重置为平移矩阵
		Matrixf& MakeTranslate(value_type xmov, value_type ymov, value_type zmov)
		{
			SET_ROW(0, 1.0f, 0.0f, 0.0f, xmov);
			SET_ROW(1, 0.0f, 1.0f, 0.0f, ymov);
			SET_ROW(2, 0.0f, 0.0f, 1.0f, zmov);
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
			return *this;
		}
		Matrixf& MakeTranslate(const Vec3f& mov) { return MakeTranslate(mov.x(), mov.y(), mov.z()); }

		//重置为以原点缩放矩阵
		Matrixf& MakeScale(value_type xscale, value_type yscale, value_type zscale)
		{
			SET_ROW(0, xscale, 0.0f, 0.0f, 0.0f);
			SET_ROW(1, 0.0f, yscale, 0.0f, 0.0f);
			SET_ROW(2, 0.0f, 0.0f, zscale, 0.0f);
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
			return *this;
		}
		Matrixf& MakeScale(const Vec3f& scale) { return MakeScale(scale.x(), scale.y(), scale.z()); }

		//重置为以任意点缩放矩阵
		Matrixf& MakeScale(value_type xscale, value_type yscale, value_type zscale, const Vec3f& point)
		{
			SET_ROW(0, xscale, 0.0f, 0.0f, point.x() * (1.0f - xscale));
			SET_ROW(1, 0.0f, yscale, 0.0f, point.y() * (1.0f - yscale));
			SET_ROW(2, 0.0f, 0.0f, zscale, point.z() * (1.0f - zscale));
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
			return *this;
		}
		Matrixf& MakeScale(const Vec3f& scale, const Vec3f& point) { return MakeScale(scale.x(), scale.y(), scale.z(), point); }

		//重置为绕任意轴旋转矩阵
		Matrixf& MakeRotate(value_type angle, value_type xaxis, value_type yaxis, value_type zaxis)
		{
			return MakeRotate(angle, Vec3f(xaxis, yaxis, zaxis));
		}
		Matrixf& MakeRotate(value_type angle, const Vec3f& axis) 
		{ 
			Vec3f a = Vec3f::Normalize(axis);
			value_type x = a.x();
			value_type y = a.y();
			value_type z = a.z();
			value_type c = OGE::Cos(angle);
			value_type s = OGE::Sin(angle);
			value_type k = 1.0f - c;
			SET_ROW(0, x * x * k + c, x * y * k - z * s, x * z * k + y * s, 0.0f);
			SET_ROW(1, x * y * k + z * s, y * y * k + c, y * z * k - x * s, 0.0f);
			SET_ROW(2, x * z * k - y * s, y * z * k + x * s, z * z * k + c, 0.0f);
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
			return *this;
		}

		//重置为镜像矩阵
		Matrixf& MakeMirror(value_type xaxis, value_type yaxis, value_type zaxis)
		{
			return MakeMirror(Vec3f(xaxis, yaxis, zaxis));
		}
		Matrixf& MakeMirror(const Vec3f& axis)
		{
			Vec3f a = Vec3f::Normalize(axis);
			value_type x = a.x();
			value_type y = a.y();
			value_type z = a.z();
			SET_ROW(0, 1.0f - 2 * x * x, -2 * x * y, -2 * x * z, 0.0f);
			SET_ROW(1, -2 * x * y, 1.0f - 2 * y * y, -2 * y * z, 0.0f);
			SET_ROW(2, -2 * x * z, -2 * y * z, 1.0f - 2 * z * z, 0.0f);
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
			return *this;
		}

		//重置为视图矩阵
		Matrixf& MakeLookAt(const Vec3f& eye, const Vec3f& target, const Vec3f& up)
		{
			Vec3f b = Vec3f::Normalize(eye - target);
			Vec3f u = Vec3f::Normalize(up);
			Vec3f r = u ^ b;
			SET_ROW(0, r.x(), r.y(), r.z(), 0.0f);
			SET_ROW(1, u.x(), u.y(), u.z(), 0.0f);
			SET_ROW(2, b.x(), b.y(), b.z(), 0.0f);
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
			return *this *= Translate(-eye.x(), -eye.y(), -eye.z());
		}

		//重置为正交投影矩阵
		Matrixf& MakeOrtho(value_type left, value_type right, value_type bottom, value_type top, value_type near, value_type far)
		{
			value_type w = 1.0f / (right - left);
			value_type h = 1.0f / (top - bottom);
			value_type d = 1.0f / (far - near);
			SET_ROW(0, 2.0f * w, 0.0f, 0.0f, -(right + left) * w);
			SET_ROW(1, 0.0f, 2.0f * h, 0.0f, -(top + bottom) * h);
			SET_ROW(2, 0.0f, 0.0f, -2.0f * d, -(far + near) * d);
			SET_ROW(3, 0.0f, 0.0f, 0.0f, 1.0f);
			return *this;
		}

		//重置为透视投影矩阵
		Matrixf& MakePerspective(value_type fov, value_type ratio, value_type near, value_type far)
		{
			value_type c = OGE::Cot(fov / 2);
			value_type d = 1.0f / (far - near);
			SET_ROW(0, c / ratio, 0.0f, 0.0f, 0.0f);
			SET_ROW(1, 0.0f, c, 0.0f, 0.0f);
			SET_ROW(2, 0.0f, 0.0f, -(far + near) * d, -2 * far * near * d);
			SET_ROW(3, 0.0f, 0.0f, -1.0f, 0.0f);
			return *this;
		}

		//重置为自身转置矩阵
		Matrixf& MakeTranspose()
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
			Matrixf m = *this;
			unsigned int indxc[4], indxr[4], ipiv[4];
			unsigned int i, j, k, l, ll;
			unsigned int icol = 0;
			unsigned int irow = 0;
			value_type pivinv, dum, big;

			for (j = 0; j < 4; j++) ipiv[j] = 0;

			for (i = 0; i < 4; i++)
			{
				big = 0.0f;
				for (j = 0; j < 4; ++j)
				{
					if (ipiv[j] != 1)
					{
						for (k = 0; k < 4; k++)
						{
							if (ipiv[k] == 0)
							{
								if (OGE::Absolute(m.m_[j][k]) >= big)
								{
									big = OGE::Absolute(m.m_[j][k]);
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
						OGE::Swap(m.m_[irow][l], m.m_[icol][l]);

				indxr[i] = irow;
				indxc[i] = icol;
				if (OGE::IsEqual(m.m_[icol][icol], 0.0f))
					return false;

				pivinv = 1.0f / m.m_[icol][icol];
				m.m_[icol][icol] = 1;
				for (l = 0; l < 4; ++l) 
					m.m_[icol][l] *= pivinv;
				for (ll = 0; ll < 4; ++ll)
				{
					if (ll != icol)
					{
						dum = m.m_[ll][icol];
						m.m_[ll][icol] = 0;
						for (l = 0; l < 4; ++l)
							m.m_[ll][l] -= m.m_[icol][l] * dum;
					}
				}
			}
			for (int lx = 4; lx > 0; --lx)
			{
				if (indxr[lx - 1] != indxc[lx - 1])
				{
					for (k = 0; k < 4; k++)
						OGE::Swap(m.m_[k][indxr[lx - 1]], m.m_[k][indxc[lx - 1]]);
				}
			}
			Set(m);
			return true;
		}

		//平移矩阵
		static Matrixf Translate(value_type xmov, value_type ymov, value_type zmov)
		{
			Matrixf m;
			return m.MakeTranslate(xmov, ymov, zmov);
		}
		static Matrixf Translate(const Vec3f& mov)
		{
			Matrixf m;
			return m.MakeTranslate(mov);
		}

		//以原点缩放矩阵
		static Matrixf Scale(value_type xscale, value_type yscale, value_type zscale)
		{
			Matrixf m;
			return m.MakeScale(xscale, yscale, zscale);
		}
		static Matrixf Scale(const Vec3f& scale)
		{
			Matrixf m;
			return m.MakeScale(scale);
		}

		//以任意点缩放矩阵
		static Matrixf Scale(value_type xscale, value_type yscale, value_type zscale, const Vec3f& point)
		{
			Matrixf m;
			return m.MakeScale(xscale, yscale, zscale, point);
		}
		static Matrixf Scale(const Vec3f& scale, const Vec3f& point)
		{
			Matrixf m;
			return m.MakeScale(scale, point);
		}

		//绕任意轴旋转矩阵
		static Matrixf Rotate(value_type angle, value_type xaxis, value_type yaxis, value_type zaxis)
		{
			Matrixf m;
			return m.MakeRotate(angle, xaxis, yaxis, zaxis);
		}
		static Matrixf Rotate(value_type angle, const Vec3f& axis)
		{
			Matrixf m;
			return m.MakeRotate(angle, axis);
		}

		//镜像矩阵
		static Matrixf Mirror(value_type xaxis, value_type yaxis, value_type zaxis)
		{
			Matrixf m;
			return m.MakeMirror(xaxis, yaxis, zaxis);
		}
		static Matrixf Mirror(const Vec3f& axis)
		{
			Matrixf m;
			return m.MakeMirror(axis);
		}

		//视图矩阵
		static Matrixf LookAt(const Vec3f& eye, const Vec3f& target, const Vec3f& up)
		{
			Matrixf m;
			return m.MakeLookAt(eye, target, up);
		}

		//正交投影矩阵
		static Matrixf Ortho(value_type left, value_type right, value_type bottom, value_type top, value_type near, value_type far)
		{
			Matrixf m;
			return m.MakeOrtho(left, right, bottom, top, near, far);
		}

		//透视投影矩阵
		static Matrixf Perspective(value_type fov, value_type ratio, value_type near, value_type far)
		{
			Matrixf m;
			return m.MakePerspective(fov, ratio, near, far);
		}

		//转置矩阵
		static Matrixf Transpose(const Matrixf& m)
		{
			Matrixf res = m;
			return res.MakeTranspose();
		}

		//逆矩阵
		static Matrixf Inverse(const Matrixf& m)
		{
			Matrixf res = m;
			res.MakeInverse();
			return res;
		}

	protected:
		value_type		m_[4][4];
	};

	typedef Matrixf Matrix;
	typedef std::vector<Matrix> MatrixArray;

#undef SET_ROW
#undef MAT_X_VEC3
#undef VEC3_X_MAT
#undef MAT_X_VEC4
#undef VEC4_X_MAT
}