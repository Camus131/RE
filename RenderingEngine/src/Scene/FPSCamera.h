#pragma once

#include "../Math/Matrixf.h"
#include "../Math/EulerAngles.h"


namespace OGE
{
    class FPSCamera
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

        FPSCamera(const Vec3& position, const Vec3& target, const Vec3& up, float fov = 45.0f, float movement_speed = 1.0f, float sensitivity = 0.1f);

        //获得视图矩阵
        Matrix ViewMatrix()const { return Matrix::LookAt(position_, position_ + front_, up_); }

        //移动相机,frame_time为帧生成时间
        void Move(Dir direction, float frame_time);

        //转动相机
        void Turn(float xoffset, float yoffset);

        //还原相机
        void Reset();

        //获得/设置视野
        float GetFov() const { return fov_; }
        void SetFov(float fov);

        //获得/设置移动速度
        float GetSpeed() const { return movement_speed_; }
        void SetSpeed(float speed);

        //获得/设置视角灵敏度
        float GetSensitivity() const { return sensitivity_; }
        void SetSensitivity(float sensitivity);

        //获得位置
        Vec3 GetPosition()const { return position_; }

    private:
        void update();

    private:
        //实时位置
        Vec3           position_;
        Vec3           front_;
        Vec3           up_;
        Vec3           right_;

        //初始位置
        Vec3           default_position_;
        Vec3           default_front_;
        Vec3           default_up_;

        //欧拉角
        EulerAngles     euler_angles_;

        //视野大小
        float           fov_;

        //移动速度
        float           movement_speed_;

        //视角灵敏度
        float           sensitivity_;
    };
}