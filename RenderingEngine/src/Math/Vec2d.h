#pragma once

#include "Vec2f.h"


namespace OGE
{
    class Vec2d
    {
    public:
        typedef double value_type;

        Vec2d() { v_[0] = 0.0; v_[1] = 0.0; }
        Vec2d(value_type x, value_type y) { v_[0] = x; v_[1] = y; }
        Vec2d(const Vec2d& v) { v_[0] = v.v_[0]; v_[1] = v.v_[1]; }
        Vec2d(const Vec2f& v) { v_[0] = v[0]; v_[1] = v[1]; }

        //��������
        Vec2d& Set(value_type x, value_type y)
        {
            v_[0] = x;
            v_[1] = y;
            return *this;
        }
        Vec2d& Set(const Vec2d& v)
        {
            v_[0] = v.v_[0];
            v_[1] = v.v_[1];
            return *this;
        }
        Vec2d& Set(const Vec2f& v)
        {
            v_[0] = v[0];
            v_[1] = v[1];
            return *this;
        }

        //����
        Vec2d& Zero()
        {
            v_[0] = 0.0;
            v_[1] = 0.0;
            return *this;
        }

        //ģ
        value_type Mod() const { return Sqrt(v_[0] * v_[0] + v_[1] * v_[1]); }

        //ģ��ƽ��
        value_type Mod2() const { return v_[0] * v_[0] + v_[1] * v_[1]; }

        //��λ��
        Vec2d& Normalize()
        {
            value_type mod = Mod();
            if (mod > 0.0)
            {
                value_type inv = 1.0 / mod;
                v_[0] *= inv;
                v_[1] *= inv;
            }
            return *this;
        }

        //����true��ʾ�������ݾ��Ϸ�
        bool IsValid() const { return !IsNaN(); }

        //����true��ʾ������������һ��ֵ�ǷǷ���
        bool IsNaN() const { return OGE::IsNaN(v_[0]) || OGE::IsNaN(v_[1]); }

        //ȡ��ַ
        value_type* Ptr() { return v_; }
        const value_type* Ptr() const { return v_; }

        //ȡֵ
        value_type& operator [] (int i) { return v_[i]; }
        value_type operator [] (int i) const { return v_[i]; }
        value_type& x() { return v_[0]; }
        value_type& y() { return v_[1]; }
        value_type x() const { return v_[0]; }
        value_type y() const { return v_[1]; }

        //���
        value_type operator * (const Vec2d& v) const { return v_[0] * v.v_[0] + v_[1] * v.v_[1]; }

        Vec2d& operator = (const Vec2d& v)
        {
            if (&v == this)
                return *this;
            v_[0] = v.v_[0];
            v_[1] = v.v_[1];
            return *this;
        }

        Vec2d& operator = (const Vec2f& v)
        {
            v_[0] = v[0];
            v_[1] = v[1];
            return *this;
        }

        Vec2d operator - () const { return Vec2d(-v_[0], -v_[1]); }

        bool operator == (const Vec2d& v) const { return OGE::IsEqual(v_[0], v.v_[0]) && OGE::IsEqual(v_[1], v.v_[1]); }

        bool operator != (const Vec2d& v) const { return v_[0] != v.v_[0] || v_[1] != v.v_[1]; }

        Vec2d operator + (const Vec2d& v) const { return Vec2d(v_[0] + v.v_[0], v_[1] + v.v_[1]); }

        Vec2d operator - (const Vec2d& v) const { return Vec2d(v_[0] - v.v_[0], v_[1] - v.v_[1]); }

        Vec2d operator * (value_type v) const { return Vec2d(v_[0] * v, v_[1] * v); }

        Vec2d operator / (value_type v) const
        {
            value_type inv = 1.0 / v;
            return Vec2d(v_[0] * inv, v_[1] * inv);
        }

        Vec2d& operator += (const Vec2d& v)
        {
            v_[0] += v.v_[0];
            v_[1] += v.v_[1];
            return *this;
        }

        Vec2d& operator -= (const Vec2d& v)
        {
            v_[0] -= v.v_[0];
            v_[1] -= v.v_[1];
            return *this;
        }

        Vec2d& operator *= (value_type v)
        {
            v_[0] *= v;
            v_[1] *= v;
            return *this;
        }

        Vec2d& operator /= (value_type v)
        {
            value_type inv = 1.0 / v;
            v_[0] *= inv;
            v_[1] *= inv;
            return *this;
        }

        //����������
        static value_type Distance(const Vec2d& v1, const Vec2d& v2) { return Sqrt(Distance2(v1, v2)); }

        //����������ƽ��
        static value_type Distance2(const Vec2d& v1, const Vec2d& v2)
        {
            value_type dx = v1.x() - v2.x();
            value_type dy = v1.y() - v2.y();
            return dx * dx + dy * dy;
        }

    private:
        value_type		v_[2];
    };
}