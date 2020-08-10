#pragma once

#include "Math.h"


namespace OGE
{
    class Vec2f
    {
    public:
        typedef float value_type;

        Vec2f() { v_[0] = 0.0f; v_[1] = 0.0f; }
        Vec2f(value_type x, value_type y) { v_[0] = x; v_[1] = y; }
        Vec2f(const Vec2f& v) { v_[0] = v.v_[0]; v_[1] = v.v_[1]; }

        //重置内容
        Vec2f& Set(value_type x, value_type y)
        {
            v_[0] = x;
            v_[1] = y;
            return *this;
        }
        Vec2f& Set(const Vec2f& v)
        {
            v_[0] = v.v_[0];
            v_[1] = v.v_[1];
            return *this;
        }

        //置零
        Vec2f& Zero()
        {
            v_[0] = 0.0f;
            v_[1] = 0.0f;
            return *this;
        }

        //模
        value_type Mod() const { return Sqrt(v_[0] * v_[0] + v_[1] * v_[1]); }

        //模的平方
        value_type Mod2() const { return v_[0] * v_[0] + v_[1] * v_[1]; }

        //单位化
        Vec2f& Normalize()
        {
            value_type mod = Mod();
            if (mod > 0.0f)
            {
                value_type inv = 1.0f / mod;
                v_[0] *= inv;
                v_[1] *= inv;
            }
            return *this;
        }

        //返回true表示所有数据均合法
        bool IsValid() const { return !IsNaN(); }

        //返回true表示数据中至少有一个值是非法的
        bool IsNaN() const { return OGE::IsNaN(v_[0]) || OGE::IsNaN(v_[1]); }

        //取地址
        value_type* Ptr() { return v_; }
        const value_type* Ptr() const { return v_; }

        //取值
        value_type& operator [] (int i) { return v_[i]; }
        value_type operator [] (int i) const { return v_[i]; }
        value_type& x() { return v_[0]; }
        value_type& y() { return v_[1]; }
        value_type x() const { return v_[0]; }
        value_type y() const { return v_[1]; }

        //点乘
        value_type operator * (const Vec2f& v) const { return v_[0] * v.v_[0] + v_[1] * v.v_[1]; }

        Vec2f& operator = (const Vec2f& v)
        {
            if (&v == this)
                return *this;
            v_[0] = v.v_[0];
            v_[1] = v.v_[1];
            return *this;
        }

        Vec2f operator - () const { return Vec2f(-v_[0], -v_[1]); }

        bool operator == (const Vec2f& v) const { return v_[0] == v.v_[0] && v_[1] == v.v_[1]; }

        bool operator != (const Vec2f& v) const { return v_[0] != v.v_[0] || v_[1] != v.v_[1]; }

        Vec2f operator + (const Vec2f& v) const { return Vec2f(v_[0] + v.v_[0], v_[1] + v.v_[1]); }

        Vec2f operator - (const Vec2f& v) const { return Vec2f(v_[0] - v.v_[0], v_[1] - v.v_[1]); }

        Vec2f operator * (value_type v) const { return Vec2f(v_[0] * v, v_[1] * v); }

        Vec2f operator / (value_type v) const
        {
            value_type inv = 1.0f / v;
            return Vec2f(v_[0] * inv, v_[1] * inv);
        }

        Vec2f& operator += (const Vec2f& v)
        {
            return *this = *this + v;
            v_[0] += v.v_[0];
            v_[1] += v.v_[1];
            return *this;
        }

        Vec2f& operator -= (const Vec2f& v)
        {
            v_[0] -= v.v_[0];
            v_[1] -= v.v_[1];
            return *this;
        }

        Vec2f& operator *= (value_type v)
        {
            v_[0] *= v;
            v_[1] *= v;
            return *this;
        }

        Vec2f& operator /= (value_type v)
        {
            value_type inv = 1.0f / v;
            v_[0] *= inv;
            v_[1] *= inv;
            return *this;
        }

        //两向量距离
        static value_type Distance(const Vec2f& v1, const Vec2f& v2) { return Sqrt(Distance2(v1, v2)); }

        //两向量距离平方
        static value_type Distance2(const Vec2f& v1, const Vec2f& v2)
        {
            value_type dx = v1.x() - v2.x();
            value_type dy = v1.y() - v2.y();
            return dx * dx + dy * dy;
        }

    private:
        value_type		v_[2];
    };

    typedef Vec2f Vec2;
}