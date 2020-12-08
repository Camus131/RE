#pragma once

#include "Frustum.h"

#include "Math/EulerAnglesf.h"


namespace OGE
{
    class OrthoCamera :public Frustum
    {
    public:
        //创建实例
        static SPtr(OrthoCamera) Create(const Vec3& eye, const Vec3& target, const Vec3& up, value_type left, value_type right, value_type bottom, value_type top,
            value_type near_dis, value_type far_dis, value_type dragging_speed = 1.0f, value_type turning_speed = 0.1f)
        {
            return SPtr(OrthoCamera)(new OrthoCamera(eye, target, up, left, right, bottom, top,
                near_dis, far_dis, dragging_speed, turning_speed));
        }

        //获得/设置左
        value_type GetLeft() const { return xleft_; }
        void SetLeft(value_type left) { xleft_ = left; }

        //获得/设置右
        value_type GetRight() const { return xright_; }
        void SetRight(value_type right) { xright_ = right; }

        //获得/设置下
        value_type GetBottom() const { return ybottom_; }
        void SetBottom(value_type bottom) { ybottom_ = bottom; }

        //获得/设置上
        value_type GetTop() const { return ytop_; }
        void SetTop(value_type top) { ytop_ = top; }

        //获得视点
        Vec3 GetEye() const { return eye_; }

        //获得/设置移动速度
        value_type GetDraggingSpeed() const { return dragging_speed_; }
        void SetDraggingSpeed(value_type speed);

        //获得/设置转视角速度
        value_type GetTurningSpeed() const { return turning_speed_; }
        void SetTurningSpeed(value_type speed);

        //视图矩阵
        Matrix ViewMatrix() const { return Matrix::LookAt(eye_, eye_ + front_, up_); }

        //投影矩阵
        Matrix ProjectionMatrix() const { return Matrix::Ortho(xleft_, xright_, ybottom_, ytop_, near_dis_, far_dis_); }

        //缩放视景体
        void Scale(value_type offset);

        //移动相机,frame_time为帧生成时间
        void Move(value_type xoffset, value_type yoffset, value_type frame_time);

        //转动相机
        void Turn(value_type xoffset, value_type yoffset);

        //还原相机
        void Reset();

        //计算世界坐标六个面
        void ComputePlanes();

        //返回true表示包围盒可见
        bool Intersect(const BoundingBox& bb);

    protected:
        OrthoCamera(const Vec3& eye, const Vec3& target, const Vec3& up, value_type left, value_type right, value_type bottom, value_type top,
            value_type near_dis, value_type far_dis, value_type dragging_speed = 1.0f, value_type turning_speed = 0.1f);

        //计算位置
        void ComputePos();

    protected:
        //左右下上
        value_type		xleft_;
        value_type		xright_;
        value_type		ybottom_;
        value_type		ytop_;

        //实时位置
        Vec3           eye_;
        Vec3           front_;
        Vec3           up_;
        Vec3           right_;

        //初始位置
        Vec3           init_eye_;
        Vec3           init_front_;
        Vec3           init_up_;

        //旋转欧拉角
        EulerAngles     rotate_angles_;

        //拖拽速度
        value_type      dragging_speed_;

        //转视角速度
        value_type      turning_speed_;
    };
}