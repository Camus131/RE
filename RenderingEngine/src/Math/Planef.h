#pragma once

#include "BoundingBoxf.h"


namespace OGE
{
#define SET(v1,v2,v3,v4) v_[0] = (v1); v_[1] = (v2); v_[2] = (v3); v_[3] = (v4)

	class Planef
	{
	public:
		typedef float value_type;

        Planef() { Zero(); }
        Planef(const Planef& v) { Set(v); }
        Planef(const Vec4f& v) { Set(v); }
        Planef(const Vec3f& normal, value_type d) { Set(normal, d); }
        Planef(value_type a, value_type b, value_type c, value_type d) { Set(a, b, c, d); }
        Planef(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3) { Set(v1, v2, v3); }

        //重置内容
        void Set(const Planef& v) { SET(v[0], v[1], v[2], v[3]); Normalize(); }
        void Set(const Vec4f& v) { SET(v[0], v[1], v[2], v[3]); Normalize(); }
        void Set(const Vec3f& normal, value_type d) { SET(normal[0], normal[1], normal[2], d); Normalize(); }
        void Set(value_type a, value_type b, value_type c, value_type d) { SET(a, b, c, d); Normalize(); }
        void Set(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3)
        {
            Vec3f normal = ((v2 - v1) ^ (v3 - v2)).Normalize();
            Set(normal, -(v1 * normal));
        }

        //置零
        void Zero() { SET(0.0f, 0.0f, 0.0f, 0.0f); upper_corner_ = lower_corner_ = 0; }

        //单位化
        void Normalize()
        {
            value_type mod2 = v_[0] * v_[0] + v_[1] * v_[1] + v_[2] * v_[2];
            if (mod2 > 0.0f && !OGE::IsEqual(mod2, 1.0f))
            {
                value_type inv = 1.0f / OGE::Sqrt(mod2);
                v_[0] *= inv;
                v_[1] *= inv;
                v_[2] *= inv;
                v_[3] *= inv;
            }
            ComputeCorners();
        }

        //返回true表示所有数据均合法
        bool IsValid() const { return !IsNaN(); }

        //返回true表示数据中至少有一个值是非法的
        bool IsNaN() const { return OGE::IsNaN(v_[0]) || OGE::IsNaN(v_[1]) || OGE::IsNaN(v_[2]) || OGE::IsNaN(v_[3]); }

        //取地址
        value_type* Ptr() { return v_; }
        const value_type* Ptr() const { return v_; }

        //取值
        value_type& operator [] (unsigned int i) { return v_[i]; }
        value_type  operator [] (unsigned int i) const { return v_[i]; }
        value_type& a() { return v_[0]; }
        value_type& b() { return v_[1]; }
        value_type& c() { return v_[2]; }
        value_type& d() { return v_[3]; }
        value_type  a() const { return v_[0]; }
        value_type  b() const { return v_[1]; }
        value_type  c() const { return v_[2]; }
        value_type  d() const { return v_[3]; }

        //返回向量形式
        Vec4f ToVec4() const { return Vec4f(v_[0], v_[1], v_[2], v_[3]); }

        //返回平面法向量
        Vec3f Normal() const { return Vec3f(v_[0], v_[1], v_[2]); }

        //点到平面距离
        value_type Distance(const Vec3f& v) const { return v_[0] * v.x() + v_[1] * v.y() + v_[2] * v.z() + v_[3]; }

        //和点的相交检测
        //返回1表示点在平面上方
        //返回0表示相交
        //返回-1表示点在平面下方
        int Intersect(const Vec3f& v) const
        {
            value_type d = Distance(v);
            if (d > 0.0f)
                return 1;
            else if (d < 0.0f)
                return -1;
            else
                return 0;
        }

        //和点集区域的相交检测
        //返回1表示点集区域在平面上方
        //返回0表示相交
        //返回-1表示点集区域在平面下方
        int Intersect(const Vec3Array& vertices) const
        {
            if (vertices.empty())
                return -1;

            int num_above = 0, num_below = 0;
            for (int i = 0; i < vertices.size(); ++i)
            {
                value_type d = Distance(vertices[i]);
                if (d > 0.0f)
                    ++num_above;
                else if (d < 0.0f)
                    ++num_below;
            }

            if (num_above > 0)
            {
                if (num_below > 0)
                    return 0;
                else
                    return 1;
            }
            return -1;
        }

        //和包围盒的相交检测
        //返回1表示包围盒在平面上方
        //返回0表示相交
        //返回-1表示包围盒在平面下方
        int Intersect(const BoundingBoxf& bb) const
        {
            if (Distance(bb.Corner(lower_corner_)) > 0.0f)
                return 1;
            if (Distance(bb.Corner(upper_corner_)) < 0.0f)
                return -1;
            return 0;
        }

        //应用变换
        //如有缓存的逆矩阵直接调用TransformByPreInverse加速计算
        void Transform(const Matrixf& matrix) { TransformByPreInverse(Matrixf::Inverse(matrix)); }
        void TransformByPreInverse(const Matrixf& matrix) { Set(matrix * ToVec4()); }

        Planef& operator = (const Planef& v)
        {
            if (&v == this)
                return *this;
            SET(v[0], v[1], v[2], v[3]);
            return *this;
        }

        Planef& operator = (const Vec4f& v)
        {
            SET(v[0], v[1], v[2], v[3]);
            return *this;
        }

        Planef operator - () const { return Planef(-v_[0], -v_[1], -v_[2], -v_[3]); }

        bool operator == (const Planef& v) const
        {
            return OGE::IsEqual(v_[0], v[0]) && OGE::IsEqual(v_[1], v[1]) && OGE::IsEqual(v_[2], v[2]) && OGE::IsEqual(v_[3], v[3]);
        }

        bool operator != (const Planef& v) const
        {
            return !OGE::IsEqual(v_[0], v[0]) || !OGE::IsEqual(v_[1], v[1]) || !OGE::IsEqual(v_[2], v[2]) || !OGE::IsEqual(v_[3], v[3]);
        }

    protected:
        void ComputeCorners()
        {
            upper_corner_ = (v_[0] >= 0.0f ? 1 : 0) |
                (v_[1] >= 0.0f ? 2 : 0) |
                (v_[2] >= 0.0f ? 4 : 0);
            lower_corner_ = (~upper_corner_) & 7;
        }

	protected:
		value_type		v_[4];
        //加速包围盒相交检测的缓存变量
        unsigned int    upper_corner_;
        unsigned int    lower_corner_;
	};

    typedef Planef Plane;

#undef SET
}