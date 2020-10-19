#pragma once

#include "Vec3d.h"
#include "Vec4f.h"


namespace OGE
{
#define SET(v1,v2,v3,v4) v_[0] = (v1); v_[1] = (v2); v_[2] = (v3); v_[3] = (v4)

    class Vec4d
    {
    public:
        typedef double value_type;

        Vec4d() { SET(0.0, 0.0, 0.0, 0.0); }
        Vec4d(const Vec4d& v) { SET(v[0], v[1], v[2], v[3]); }
        Vec4d(const Vec4f& v) { SET(v[0], v[1], v[2], v[3]); }
        Vec4d(const Vec3d& v, value_type w) { SET(v[0], v[1], v[2], w); }
        Vec4d(const Vec3f& v, value_type w) { SET(v[0], v[1], v[2], w); }
        Vec4d(value_type x, value_type y, value_type z, value_type w) { SET(x, y, z, w); }

        //重置内容
        Vec4d& Set(const Vec4d& v) { SET(v[0], v[1], v[2], v[3]); return *this; }
        Vec4d& Set(const Vec4f& v) { SET(v[0], v[1], v[2], v[3]); return *this; }
        Vec4d& Set(const Vec3d& v, value_type w) { SET(v[0], v[1], v[2], w); return *this; }
        Vec4d& Set(const Vec3f& v, value_type w) { SET(v[0], v[1], v[2], w); return *this; }
        Vec4d& Set(value_type x, value_type y, value_type z, value_type w) { SET(x, y, z, w); return *this; }

        //置零
        Vec4d& Zero() { SET(0.0, 0.0, 0.0, 0.0); return *this; }

        //模
        value_type Mod() const { return OGE::Sqrt(Mod2()); }

        //模的平方
        value_type Mod2() const { return v_[0] * v_[0] + v_[1] * v_[1] + v_[2] * v_[2] + v_[3] * v_[3]; }

        //单位化
        Vec4d& Normalize()
        {
            value_type mod2 = Mod2();
            if (mod2 > 0.0 && !OGE::IsEqual(mod2, 1.0))
            {
                value_type inv = 1.0 / OGE::Sqrt(mod2);
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
        value_type operator * (const Vec4d& v) const { return v_[0] * v[0] + v_[1] * v[1] + v_[2] * v[2] + v_[3] * v[3]; }

        Vec4d& operator = (const Vec4d& v)
        {
            if (&v == this)
                return *this;
            SET(v[0], v[1], v[2], v[3]);
            return *this;
        }

        Vec4d& operator = (const Vec4f& v)
        {
            SET(v[0], v[1], v[2], v[3]);
            return *this;
        }

        Vec4d operator - () const { return Vec4d(-v_[0], -v_[1], -v_[2], -v_[3]); }

        bool operator == (const Vec4d& v) const 
        {
            return OGE::IsEqual(v_[0], v[0]) && OGE::IsEqual(v_[1], v[1]) && OGE::IsEqual(v_[2], v[2]) && OGE::IsEqual(v_[3], v[3]);
        };

        bool operator != (const Vec4d& v) const 
        { 
            return !OGE::IsEqual(v_[0], v[0]) || !OGE::IsEqual(v_[1], v[1]) || !OGE::IsEqual(v_[2], v[2]) || !OGE::IsEqual(v_[3], v[3]);
        }

        Vec4d operator + (const Vec4d& v) const { return Vec4d(v_[0] + v[0], v_[1] + v[1], v_[2] + v[2], v_[3] + v[3]); }

        Vec4d operator - (const Vec4d& v) const { return Vec4d(v_[0] - v[0], v_[1] - v[1], v_[2] - v[2], v_[3] - v[3]); }

        Vec4d operator * (value_type v) const { return Vec4d(v_[0] * v, v_[1] * v, v_[2] * v, v_[3] * v); }

        Vec4d operator / (value_type v) const
        {
            value_type inv = 1.0 / v;
            return Vec4d(v_[0] * inv, v_[1] * inv, v_[2] * inv, v_[3] * inv);
        }

        Vec4d& operator += (const Vec4d& v)
        {
            v_[0] += v[0];
            v_[1] += v[1];
            v_[2] += v[2];
            v_[3] += v[3];
            return *this;
        }

        Vec4d& operator -= (const Vec4d& v)
        {
            v_[0] -= v[0];
            v_[1] -= v[1];
            v_[2] -= v[2];
            v_[3] -= v[3];
            return *this;
        }

        Vec4d& operator *= (value_type v)
        {
            v_[0] *= v;
            v_[1] *= v;
            v_[2] *= v;
            v_[3] *= v;
            return *this;
        }

        Vec4d& operator /= (value_type v)
        {
            value_type inv = 1.0 / v;
            v_[0] *= inv;
            v_[1] *= inv;
            v_[2] *= inv;
            v_[3] *= inv;
            return *this;
        }

    protected:
        value_type      v_[4];
    };

#undef SET
}