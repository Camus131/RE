#pragma once

#include "Vec3f.h"


namespace OGE
{
#define SET(v1,v2,v3,v4) v_[0] = (v1); v_[1] = (v2); v_[2] = (v3); v_[3] = (v4)

    class Vec4f
    {
    public:
        typedef float value_type;

        Vec4f() { SET(0.0f, 0.0f, 0.0f, 0.0f); }
        Vec4f(const Vec4f& v) { SET(v[0], v[1], v[2], v[3]); }
        Vec4f(const Vec3f& v, value_type w) { SET(v[0], v[1], v[2], w); }
        Vec4f(value_type x, value_type y, value_type z, value_type w) { SET(x, y, z, w); }

        //重置内容
        Vec4f& Set(const Vec4f& v) { SET(v[0], v[1], v[2], v[3]); return *this; }
        Vec4f& Set(const Vec3f& v, value_type w) { SET(v[0], v[1], v[2], w); return *this; }
        Vec4f& Set(value_type x, value_type y, value_type z, value_type w) { SET(x, y, z, w); return *this; }

        //置零
        Vec4f& Zero() { SET(0.0f, 0.0f, 0.0f, 0.0f); return *this; }

        //模
        value_type Mod() const { return OGE::Sqrt(Mod2()); }

        //模的平方
        value_type Mod2() const { return v_[0] * v_[0] + v_[1] * v_[1] + v_[2] * v_[2] + v_[3] * v_[3]; }

        //单位化
        Vec4f& Normalize()
        {
            value_type mod2 = Mod2();
            if (mod2 > 0.0f && !OGE::IsEqual(mod2, 1.0f))
            {
                value_type inv = 1.0f / OGE::Sqrt(mod2);
                v_[0] *= inv;
                v_[1] *= inv;
                v_[2] *= inv;
                v_[3] *= inv;
            }
            return *this;
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
        value_type& x() { return v_[0]; }
        value_type& y() { return v_[1]; }
        value_type& z() { return v_[2]; }
        value_type& w() { return v_[3]; }
        value_type  x() const { return v_[0]; }
        value_type  y() const { return v_[1]; }
        value_type  z() const { return v_[2]; }
        value_type  w() const { return v_[3]; }
        value_type& r() { return v_[0]; }
        value_type& g() { return v_[1]; }
        value_type& b() { return v_[2]; }
        value_type& a() { return v_[3]; }
        value_type  r() const { return v_[0]; }
        value_type  g() const { return v_[1]; }
        value_type  b() const { return v_[2]; }
        value_type  a() const { return v_[3]; }

        //点乘
        value_type operator * (const Vec4f& v) const { return v_[0] * v[0] + v_[1] * v[1] + v_[2] * v[2] + v_[3] * v[3]; }

        Vec4f& operator = (const Vec4f& v)
        {
            if (&v == this)
                return *this;
            SET(v[0], v[1], v[2], v[3]);
            return *this;
        }

        Vec4f operator - () const { return Vec4f(-v_[0], -v_[1], -v_[2], -v_[3]); }

        bool operator == (const Vec4f& v) const 
        {
            return OGE::IsEqual(v_[0], v[0]) && OGE::IsEqual(v_[1], v[1]) && OGE::IsEqual(v_[2], v[2]) && OGE::IsEqual(v_[3], v[3]);
        }

        bool operator != (const Vec4f& v) const 
        { 
            return !OGE::IsEqual(v_[0], v[0]) || !OGE::IsEqual(v_[1], v[1]) || !OGE::IsEqual(v_[2], v[2]) || !OGE::IsEqual(v_[3], v[3]);
        }

        Vec4f operator + (const Vec4f& v) const { return Vec4f(v_[0] + v[0], v_[1] + v[1], v_[2] + v[2], v_[3] + v[3]); }

        Vec4f operator - (const Vec4f& v) const { return Vec4f(v_[0] - v[0], v_[1] - v[1], v_[2] - v[2], v_[3] - v[3]); }

        Vec4f operator * (value_type v) const { return Vec4f(v_[0] * v, v_[1] * v, v_[2] * v, v_[3] * v); }

        Vec4f operator / (value_type v) const
        {
            value_type inv = 1.0f / v;
            return Vec4f(v_[0] * inv, v_[1] * inv, v_[2] * inv, v_[3] * inv);
        }

        Vec4f& operator += (const Vec4f& v)
        {
            v_[0] += v[0];
            v_[1] += v[1];
            v_[2] += v[2];
            v_[3] += v[3];
            return *this;
        }

        Vec4f& operator -= (const Vec4f& v)
        {
            v_[0] -= v[0];
            v_[1] -= v[1];
            v_[2] -= v[2];
            v_[3] -= v[3];
            return *this;
        }

        Vec4f& operator *= (value_type v)
        {
            v_[0] *= v;
            v_[1] *= v;
            v_[2] *= v;
            v_[3] *= v;
            return *this;
        }

        Vec4f& operator /= (value_type v)
        {
            value_type inv = 1.0f / v;
            v_[0] *= inv;
            v_[1] *= inv;
            v_[2] *= inv;
            v_[3] *= inv;
            return *this;
        }

    protected:
        value_type      v_[4];
    };

    typedef Vec4f Vec4;
    typedef std::vector<Vec4> Vec4Array;

#undef SET
}