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

        //��������
        void Set(const Planef& v) { SET(v[0], v[1], v[2], v[3]); Normalize(); }
        void Set(const Vec4f& v) { SET(v[0], v[1], v[2], v[3]); Normalize(); }
        void Set(const Vec3f& normal, value_type d) { SET(normal[0], normal[1], normal[2], d); Normalize(); }
        void Set(value_type a, value_type b, value_type c, value_type d) { SET(a, b, c, d); Normalize(); }
        void Set(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3)
        {
            Vec3f normal = ((v2 - v1) ^ (v3 - v2)).Normalize();
            Set(normal, -(v1 * normal));
        }

        //����
        void Zero() { SET(0.0f, 0.0f, 0.0f, 0.0f); upper_corner_ = lower_corner_ = 0; }

        //��λ��
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

        //����true��ʾ�������ݾ��Ϸ�
        bool IsValid() const { return !IsNaN(); }

        //����true��ʾ������������һ��ֵ�ǷǷ���
        bool IsNaN() const { return OGE::IsNaN(v_[0]) || OGE::IsNaN(v_[1]) || OGE::IsNaN(v_[2]) || OGE::IsNaN(v_[3]); }

        //ȡ��ַ
        value_type* Ptr() { return v_; }
        const value_type* Ptr() const { return v_; }

        //ȡֵ
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

        //����������ʽ
        Vec4f ToVec4() const { return Vec4f(v_[0], v_[1], v_[2], v_[3]); }

        //����ƽ�淨����
        Vec3f Normal() const { return Vec3f(v_[0], v_[1], v_[2]); }

        //�㵽ƽ�����
        value_type Distance(const Vec3f& v) const { return v_[0] * v.x() + v_[1] * v.y() + v_[2] * v.z() + v_[3]; }

        //�͵���ཻ���
        //����1��ʾ����ƽ���Ϸ�
        //����0��ʾ�ཻ
        //����-1��ʾ����ƽ���·�
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

        //�͵㼯������ཻ���
        //����1��ʾ�㼯������ƽ���Ϸ�
        //����0��ʾ�ཻ
        //����-1��ʾ�㼯������ƽ���·�
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

        //�Ͱ�Χ�е��ཻ���
        //����1��ʾ��Χ����ƽ���Ϸ�
        //����0��ʾ�ཻ
        //����-1��ʾ��Χ����ƽ���·�
        int Intersect(const BoundingBoxf& bb) const
        {
            if (Distance(bb.Corner(lower_corner_)) > 0.0f)
                return 1;
            if (Distance(bb.Corner(upper_corner_)) < 0.0f)
                return -1;
            return 0;
        }

        //Ӧ�ñ任
        //���л���������ֱ�ӵ���TransformByPreInverse���ټ���
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
        //���ٰ�Χ���ཻ���Ļ������
        unsigned int    upper_corner_;
        unsigned int    lower_corner_;
	};

    typedef Planef Plane;

#undef SET
}