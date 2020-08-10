#pragma once

#include "Math.h"


namespace OGE
{
    class Vec3f
    {
    public:
        typedef float value_type;

        Vec3f() { v_[0] = 0.0f; v_[1] = 0.0f; v_[2] = 0.0f; }
        Vec3f(value_type x, value_type y, value_type z) { v_[0] = x; v_[1] = y; v_[2] = z; }
        Vec3f(const Vec3f& v) { v_[0] = v.v_[0]; v_[1] = v.v_[1]; v_[2] = v.v_[2]; }

        //��������
        Vec3f& Set(value_type x, value_type y, value_type z)
        {
            v_[0] = x;
            v_[1] = y;
            v_[2] = z;
            return *this;
        }
        Vec3f& Set(const Vec3f& v)
        {
            v_[0] = v.v_[0];
            v_[1] = v.v_[1];
            v_[2] = v.v_[2];
            return *this;
        }

        //����
        Vec3f& Zero()
        {
            v_[0] = 0.0f;
            v_[1] = 0.0f;
            v_[2] = 0.0f;
            return *this;
        }

        //ģ
        value_type Mod() const { return Sqrt(v_[0] * v_[0] + v_[1] * v_[1] + v_[2] * v_[2]); }

        //ģ��ƽ��
        value_type Mod2() const { return v_[0] * v_[0] + v_[1] * v_[1] + v_[2] * v_[2]; }

        //��λ��
        Vec3f& Normalize()
        {
            value_type mod = Mod();
            if (mod > 0.0f)
            {
                value_type inv = 1.0f / mod;
                v_[0] *= inv;
                v_[1] *= inv;
                v_[2] *= inv;
            }
            return *this;
        }

        //����true��ʾ�������ݾ��Ϸ�
        bool IsValid() const { return !IsNaN(); }

        //����true��ʾ������������һ��ֵ�ǷǷ���
        bool IsNaN() const { return OGE::IsNaN(v_[0]) || OGE::IsNaN(v_[1]) || OGE::IsNaN(v_[2]); }

        //ȡ��ַ
        value_type* Ptr() { return v_; }
        const value_type* Ptr() const { return v_; }

        //ȡֵ
        value_type& operator [] (int i) { return v_[i]; }
        value_type operator [] (int i) const { return v_[i]; }
        value_type& x() { return v_[0]; }
        value_type& y() { return v_[1]; }
        value_type& z() { return v_[2]; }
        value_type x() const { return v_[0]; }
        value_type y() const { return v_[1]; }
        value_type z() const { return v_[2]; }

        //���
        value_type operator * (const Vec3f& v) const { return v_[0] * v.v_[0] + v_[1] * v.v_[1] + v_[2] * v.v_[2]; }

        //���
        Vec3f operator ^ (const Vec3f& v) const
        {
            return Vec3f(v_[1] * v.v_[2] - v_[2] * v.v_[1],
                v_[2] * v.v_[0] - v_[0] * v.v_[2],
                v_[0] * v.v_[1] - v_[1] * v.v_[0]);
        }

        Vec3f& operator = (const Vec3f& v)
        {
            if (&v == this)
                return *this;
            v_[0] = v.v_[0];
            v_[1] = v.v_[1];
            v_[2] = v.v_[2];
            return *this;
        }

        Vec3f operator - () const { return Vec3f(-v_[0], -v_[1], -v_[2]); }

        bool operator == (const Vec3f& v) const { return v_[0] == v.v_[0] && v_[1] == v.v_[1] && v_[2] == v.v_[2]; }

        bool operator != (const Vec3f& v) const { return v_[0] != v.v_[0] || v_[1] != v.v_[1] || v_[2] != v.v_[2]; }

        Vec3f operator + (const Vec3f& v) const { return Vec3f(v_[0] + v.v_[0], v_[1] + v.v_[1], v_[2] + v.v_[2]); }

        Vec3f operator - (const Vec3f& v) const { return Vec3f(v_[0] - v.v_[0], v_[1] - v.v_[1], v_[2] - v.v_[2]); }

        Vec3f operator * (value_type v) const { return Vec3f(v_[0] * v, v_[1] * v, v_[2] * v); }

        Vec3f operator / (value_type v) const
        {
            value_type inv = 1.0f / v;
            return Vec3f(v_[0] * inv, v_[1] * inv, v_[2] * inv);
        }

        Vec3f& operator += (const Vec3f& v)
        {
            v_[0] += v.v_[0];
            v_[1] += v.v_[1];
            v_[2] += v.v_[2];
            return *this;
        }

        Vec3f& operator -= (const Vec3f& v)
        {
            v_[0] -= v.v_[0];
            v_[1] -= v.v_[1];
            v_[2] -= v.v_[2];
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

        //����������
        static value_type Distance(const Vec3f& v1, const Vec3f& v2) { return Sqrt(Distance2(v1, v2)); }

        //����������ƽ��
        static value_type Distance2(const Vec3f& v1, const Vec3f& v2)
        {
            value_type dx = v1.x() - v2.x();
            value_type dy = v1.y() - v2.y();
            value_type dz = v1.z() - v2.z();
            return dx * dx + dy * dy + dz * dz;
        }

        //��λ��
        static Vec3f Normalize(const Vec3f& v)
        {
            Vec3f res = v;
            return res.Normalize();
        }

    private:
        value_type      v_[3];
    };

    typedef Vec3f Vec3;

    //����λ����
    const Vec3 X_AXIS(1.0f, 0.0f, 0.0f);
    const Vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
    const Vec3 Z_AXIS(0.0f, 0.0f, 1.0f);
}