#pragma once

#include "Matrixd.h"
#include "BoundingBoxf.h"


namespace OGE
{
    class BoundingBoxd
    {
    public:
        typedef Vec3d vec_type;
        typedef Vec3d::value_type value_type;
        typedef Vec3f other_type;

        BoundingBoxd() :
            min_(DBL_MAX, DBL_MAX, DBL_MAX),
            max_(-DBL_MAX, -DBL_MAX, -DBL_MAX) {}

        BoundingBoxd(const BoundingBoxd& bb) :
            min_(bb.min_),
            max_(bb.max_) {}

        BoundingBoxd(const BoundingBoxf& bb) :
            min_(bb.min()),
            max_(bb.max()) {}

        BoundingBoxd(const vec_type& min, const vec_type& max) :
            min_(min),
            max_(max) {}

        BoundingBoxd(const other_type& min, const other_type& max) :
            min_(min),
            max_(max) {}

        BoundingBoxd(value_type xmin, value_type ymin, value_type zmin,
            value_type xmax, value_type ymax, value_type zmax) :
            min_(xmin, ymin, zmin),
            max_(xmax, ymax, zmax) {}

        //重置内容
        void Set(const BoundingBoxd& bb)
        {
            min_ = bb.min_;
            max_ = bb.max_;
        }
        void Set(const BoundingBoxf& bb)
        {
            min_ = bb.min();
            max_ = bb.max();
        }
        void Set(const vec_type& min, const vec_type& max)
        {
            min_ = min;
            max_ = max;
        }
        void Set(const other_type& min, const other_type& max)
        {
            min_ = min;
            max_ = max;
        }
        void Set(value_type xmin, value_type ymin, value_type zmin,
            value_type xmax, value_type ymax, value_type zmax)
        {
            min_.Set(xmin, ymin, zmin);
            max_.Set(xmax, ymax, zmax);
        }

        //初始化
        void Init()
        {
            min_.Set(DBL_MAX, DBL_MAX, DBL_MAX);
            max_.Set(-DBL_MAX, -DBL_MAX, -DBL_MAX);
        }

        //返回true表示包围盒合法
        bool IsValid() const { return max_.x() >= min_.x() && max_.y() >= min_.y() && max_.z() >= min_.z(); }

        //取值
        vec_type& min() { return min_; }
        vec_type& max() { return max_; }
        vec_type  min() const { return min_; }
        vec_type  max() const { return max_; }
        value_type& xmin() { return min_.x(); }
        value_type& ymin() { return min_.y(); }
        value_type& zmin() { return min_.z(); }
        value_type& xmax() { return max_.x(); }
        value_type& ymax() { return max_.y(); }
        value_type& zmax() { return max_.z(); }
        value_type  xmin() const { return min_.x(); }
        value_type  ymin() const { return min_.y(); }
        value_type  zmin() const { return min_.z(); }
        value_type  xmax() const { return max_.x(); }
        value_type  ymax() const { return max_.y(); }
        value_type  zmax() const { return max_.z(); }

        //中心点
        vec_type Center() const { return (min_ + max_) * 0.5; }

        //半径
        value_type Radius() const { return OGE::Sqrt(Radius2()); }

        //半径平方
        value_type Radius2() const { return  ((max_ - min_).Mod2()) * 0.25; }

        //返回特定向量
        //i为8进制数，范围为0-7，位从小到大对应x-y-z,1取最大值，0取最小值
        vec_type Corner(unsigned int i) const { return vec_type(i & 1 ? max_.x() : min_.x(), i & 2 ? max_.y() : min_.y(), i & 4 ? max_.z() : min_.z()); }

        //扩大包围盒至给出范围
        void ExpandBy(const vec_type& v)
        {
            if (v.x() < min_.x())
                min_.x() = v.x();
            if (v.x() > max_.x())
                max_.x() = v.x();

            if (v.y() < min_.y())
                min_.y() = v.y();
            if (v.y() > max_.y())
                max_.y() = v.y();

            if (v.z() < min_.z())
                min_.z() = v.z();
            if (v.z() > max_.z())
                max_.z() = v.z();
        }
        void ExpandBy(value_type x, value_type y, value_type z)
        {
            if (x < min_.x())
                min_.x() = x;
            if (x > max_.x())
                max_.x() = x;

            if (y < min_.y())
                min_.y() = y;
            if (y > max_.y())
                max_.y() = y;

            if (z < min_.z())
                min_.z() = z;
            if (z > max_.z())
                max_.z() = z;
        }
        void ExpandBy(const BoundingBoxd& bb)
        {
            if (!bb.IsValid())
                return;

            if (bb.min_.x() < min_.x())
                min_.x() = bb.min_.x();
            if (bb.max_.x() > max_.x())
                max_.x() = bb.max_.x();

            if (bb.min_.y() < min_.y())
                min_.y() = bb.min_.y();
            if (bb.max_.y() > max_.y())
                max_.y() = bb.max_.y();

            if (bb.min_.z() < min_.z())
                min_.z() = bb.min_.z();
            if (bb.max_.z() > max_.z())
                max_.z() = bb.max_.z();
        }

        //返回两包围盒相交区域
        BoundingBoxd IntersectBox(const BoundingBoxd& bb) const
        {
            return BoundingBoxd(OGE::Maximum(min_.x(), bb.min_.x()), OGE::Maximum(min_.y(), bb.min_.y()), OGE::Maximum(min_.z(), bb.min_.z()),
                OGE::Minimum(max_.x(), bb.max_.x()), OGE::Minimum(max_.y(), bb.max_.y()), OGE::Minimum(max_.z(), bb.max_.z()));
        }

        //返回true表示两包围盒相交
        bool Isintersect(const BoundingBoxd& bb) const
        {
            return OGE::Maximum(min_.x(), bb.min_.x()) <= OGE::Minimum(max_.x(), bb.max_.x()) &&
                OGE::Maximum(min_.y(), bb.min_.y()) <= OGE::Minimum(max_.y(), bb.max_.y()) &&
                OGE::Maximum(min_.z(), bb.min_.z()) <= OGE::Minimum(max_.z(), bb.max_.z());

        }

        //返回true表示包围盒包含此向量
        bool Contains(const vec_type& v, value_type epsilon = 1e-6) const
        {
            return IsValid() &&
                ((v.x() + epsilon) >= min_.x() && (v.x() - epsilon) <= max_.x()) &&
                ((v.y() + epsilon) >= min_.y() && (v.y() - epsilon) <= max_.y()) &&
                ((v.z() + epsilon) >= min_.z() && (v.z() - epsilon) <= max_.z());
        }

        //应用变换
        void Transform(const Matrixd& matrix)
        {
            vec_type corner_0 = matrix * Corner(0);
            vec_type corner_1 = matrix * Corner(1);
            vec_type corner_2 = matrix * Corner(2);
            vec_type corner_3 = matrix * Corner(3);
            vec_type corner_4 = matrix * Corner(4);
            vec_type corner_5 = matrix * Corner(5);
            vec_type corner_6 = matrix * Corner(6);
            vec_type corner_7 = matrix * Corner(7);
            min_.x() = OGE::Minimum(OGE::Minimum(OGE::Minimum(corner_0.x(), corner_1.x()), OGE::Minimum(corner_2.x(), corner_3.x())),
                OGE::Minimum(OGE::Minimum(corner_4.x(), corner_5.x()), OGE::Minimum(corner_6.x(), corner_7.x())));
            min_.y() = OGE::Minimum(OGE::Minimum(OGE::Minimum(corner_0.y(), corner_1.y()), OGE::Minimum(corner_2.y(), corner_3.y())),
                OGE::Minimum(OGE::Minimum(corner_4.y(), corner_5.y()), OGE::Minimum(corner_6.y(), corner_7.y())));
            min_.z() = OGE::Minimum(OGE::Minimum(OGE::Minimum(corner_0.z(), corner_1.z()), OGE::Minimum(corner_2.z(), corner_3.z())),
                OGE::Minimum(OGE::Minimum(corner_4.z(), corner_5.z()), OGE::Minimum(corner_6.z(), corner_7.z())));
            max_.x() = OGE::Maximum(OGE::Maximum(OGE::Maximum(corner_0.x(), corner_1.x()), OGE::Maximum(corner_2.x(), corner_3.x())),
                OGE::Maximum(OGE::Maximum(corner_4.x(), corner_5.x()), OGE::Maximum(corner_6.x(), corner_7.x())));
            max_.y() = OGE::Maximum(OGE::Maximum(OGE::Maximum(corner_0.y(), corner_1.y()), OGE::Maximum(corner_2.y(), corner_3.y())),
                OGE::Maximum(OGE::Maximum(corner_4.y(), corner_5.y()), OGE::Maximum(corner_6.y(), corner_7.y())));
            max_.z() = OGE::Maximum(OGE::Maximum(OGE::Maximum(corner_0.z(), corner_1.z()), OGE::Maximum(corner_2.z(), corner_3.z())),
                OGE::Maximum(OGE::Maximum(corner_4.z(), corner_5.z()), OGE::Maximum(corner_6.z(), corner_7.z())));
        }

        BoundingBoxd& operator = (const BoundingBoxd& bb)
        {
            if (&bb == this)
                return *this;
            min_ = bb.min_;
            max_ = bb.max_;
            return *this;
        }

        BoundingBoxd& operator = (const BoundingBoxf& bb)
        {
            min_ = bb.min();
            max_ = bb.max();
            return *this;
        }

        bool operator == (const BoundingBoxd& bb) const { return min_ == bb.min_ && max_ == bb.max_; }

        bool operator != (const BoundingBoxd& bb) const { return min_ != bb.min_ || max_ != bb.max_; }

    protected:
        vec_type    min_;
        vec_type    max_;
    };
}