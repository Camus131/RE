#pragma once

#include <vector>

#include "Math.h"


namespace OGE
{
#define SET(v1,v2,v3) v_[0] = (v1); v_[1] = (v2); v_[2] = (v3)

    class Vec3f
    {
    public:
        typedef float value_type;

        Vec3f() { SET(0.0f, 0.0f, 0.0f); }
        Vec3f(const Vec3f& v) { SET(v[0], v[1], v[2]); }
        Vec3f(value_type x, value_type y, value_type z) { SET(x, y, z); }

        //重置内容
        Vec3f& Set(const Vec3f& v) { SET(v[0], v[1], v[2]); return *this; }
        Vec3f& Set(value_type x, value_type y, value_type z) { SET(x, y, z); return *this; }

        //置零
        Vec3f& Zero() { SET(0.0f, 0.0f, 0.0f); return *this; }

        //模
        value_type Mod() const { return OGE::Sqrt(Mod2()); }

        //模的平方
        value_type Mod2() const { return v_[0] * v_[0] + v_[1] * v_[1] + v_[2] * v_[2]; }

        //单位化
        Vec3f& Normalize()
        {
            value_type mod2 = Mod2();
            if (mod2 > 0.0f && !OGE::IsEqual(mod2, 1.0f))
            {
                value_type inv = 1.0f / OGE::Sqrt(mod2);
                v_[0] *= inv;
                v_[1] *= inv;
                v_[2] *= inv;
            }
            return *this;
        }

        //返回true表示所有数据均合法
        bool IsValid() const { return !IsNaN(); }

        //返回true表示数据中至少有一个值是非法的
        bool IsNaN() const { return OGE::IsNaN(v_[0]) || OGE::IsNaN(v_[1]) || OGE::IsNaN(v_[2]); }

        //取地址
        value_type* Ptr() { return v_; }
        const value_type* Ptr() const { return v_; }

        //取值
        value_type& operator [] (unsigned int i) { return v_[i]; }
        value_type  operator [] (unsigned int i) const { return v_[i]; }
        value_type& x() { return v_[0]; }
        value_type& y() { return v_[1]; }
        value_type& z() { return v_[2]; }
        value_type  x() const { return v_[0]; }
        value_type  y() const { return v_[1]; }
        value_type  z() const { return v_[2]; }

        //点乘
        value_type operator * (const Vec3f& v) const { return v_[0] * v[0] + v_[1] * v[1] + v_[2] * v[2]; }

        //叉乘
        Vec3f operator ^ (const Vec3f& v) const { return Vec3f(v_[1] * v[2] - v_[2] * v[1], v_[2] * v[0] - v_[0] * v[2], v_[0] * v[1] - v_[1] * v[0]); }

        Vec3f& operator = (const Vec3f& v)
        {
            if (&v == this)
                return *this;
            SET(v[0], v[1], v[2]);
            return *this;
        }

        Vec3f operator - () const { return Vec3f(-v_[0], -v_[1], -v_[2]); }

        bool operator == (const Vec3f& v) const { return OGE::IsEqual(v_[0], v[0]) && OGE::IsEqual(v_[1], v[1]) && OGE::IsEqual(v_[2], v[2]); }

        bool operator != (const Vec3f& v) const { return !OGE::IsEqual(v_[0], v[0]) || !OGE::IsEqual(v_[1], v[1]) || !OGE::IsEqual(v_[2], v[2]); }

        Vec3f operator + (const Vec3f& v) const { return Vec3f(v_[0] + v[0], v_[1] + v[1], v_[2] + v[2]); }

        Vec3f operator - (const Vec3f& v) const { return Vec3f(v_[0] - v[0], v_[1] - v[1], v_[2] - v[2]); }

        Vec3f operator * (value_type v) const { return Vec3f(v_[0] * v, v_[1] * v, v_[2] * v); }

        Vec3f operator / (value_type v) const
        {
            value_type inv = 1.0f / v;
            return Vec3f(v_[0] * inv, v_[1] * inv, v_[2] * inv);
        }

        Vec3f& operator += (const Vec3f& v)
        {
            v_[0] += v[0];
            v_[1] += v[1];
            v_[2] += v[2];
            return *this;
        }

        Vec3f& operator -= (const Vec3f& v)
        {
            v_[0] -= v[0];
            v_[1] -= v[1];
            v_[2] -= v[2];
            return *this;
        }

        Vec3f& operator *= (value_type v)
        {
            v_[0] *= v;
            v_[1] *= v;
            v_[2] *= v;
            return *this;
        }

        Vec3f& operator /= (value_type v)
        {
            value_type inv = 1.0f / v;
            v_[0] *= inv;
            v_[1] *= inv;
            v_[2] *= inv;
            return *this;
        }

        //两向量距离
        static value_type Distance(const Vec3f& v1, const Vec3f& v2) { return OGE::Sqrt(Distance2(v1, v2)); }

        //两向量距离平方
        static value_type Distance2(const Vec3f& v1, const Vec3f& v2) { return OGE::Square(v1.x() - v2.x()) + OGE::Square(v1.y() - v2.y()) + OGE::Square(v1.z() - v2.z()); }

        //单位化
        static Vec3f Normalize(const Vec3f& v)
        {
            Vec3f res = v;
            return res.Normalize();
        }

    protected:
        value_type      v_[3];
    };

    typedef Vec3f Vec3;
    typedef std::vector<Vec3> Vec3Array;

    //轴向单位向量
    const Vec3 X_AXIS(1.0f, 0.0f, 0.0f);
    const Vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
    const Vec3 Z_AXIS(0.0f, 0.0f, 1.0f);

#undef SET
}