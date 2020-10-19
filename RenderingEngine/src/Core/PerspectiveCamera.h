#pragma once

#include "Frustum.h"

#include "Math/EulerAnglesf.h"


namespace OGE
{
	class PerspectiveCamera :public Frustum
	{
	public:
        //方向
        enum Dir
        {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

        //创建实例
        static SPtr(PerspectiveCamera) Create(const Vec3& eye, const Vec3& target, const Vec3& up, value_type fov, value_type ratio,
            value_type near_dis, value_type far_dis, value_type moving_speed = 1.0f, value_type turning_speed = 0.1f)
        {
            return SPtr(PerspectiveCamera)(new PerspectiveCamera(eye, target, up, fov, ratio,
                near_dis, far_dis, moving_speed, turning_speed));
        }

        //获得视点
        Vec3 GetEye() const { return eye_; }

        //获得/设置移动速度
        value_type GetMovingSpeed() const { return moving_speed_; }
        void SetMovingSpeed(value_type speed);

        //获得/设置转视角速度
        value_type GetTurningSpeed() const { return turning_speed_; }
        void SetTurningSpeed(value_type speed);

        //视图矩阵
        Matrix ViewMatrix() const { return Matrix::LookAt(eye_, eye_ + front_, up_); }

        //投影矩阵
        Matrix ProjectionMatrix() const { return Matrix::Perspective(fov_, ratio_, near_dis_, far_dis_); }

        //移动相机,frame_time为帧生成时间
        void Move(Dir direction, value_type frame_time);

        //转动相机
        void Turn(value_type xoffset, value_type yoffset);

        //还原相机
        void Reset();

        //计算世界坐标六个面
        void ComputeWorldPlanes();

        //返回true表示包围盒可见
        bool Intersect(const BoundingBox& bb);

	protected:
        PerspectiveCamera(const Vec3& eye, const Vec3& target, const Vec3& up, value_type fov, value_type ratio,
            value_type near_dis, value_type far_dis, value_type moving_speed = 1.0f, value_type turning_speed = 0.1f);

        //计算位置
        void ComputePos();

	protected:
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

        //移动速度
        value_type      moving_speed_;

        //转视角速度
        value_type      turning_speed_;

        //世界坐标六个面
        Plane			near_plane_world_;
        Plane			far_plane_world_;
        Plane			bottom_plane_world_;
        Plane			top_plane_world_;
        Plane			left_plane_world_;
        Plane			right_plane_world_;
	};
}