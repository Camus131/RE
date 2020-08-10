#pragma once

#include "../Math/Matrixf.h"
#include "../Math/EulerAngles.h"


namespace OGE
{
    class FPSCamera
    {
    public:
        //����
        enum Dir
        {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

        FPSCamera(const Vec3& position, const Vec3& target, const Vec3& up, float fov = 45.0f, float movement_speed = 1.0f, float sensitivity = 0.1f);

        //�����ͼ����
        Matrix ViewMatrix()const { return Matrix::LookAt(position_, position_ + front_, up_); }

        //�ƶ����,frame_timeΪ֡����ʱ��
        void Move(Dir direction, float frame_time);

        //ת�����
        void Turn(float xoffset, float yoffset);

        //��ԭ���
        void Reset();

        //���/������Ұ
        float GetFov() const { return fov_; }
        void SetFov(float fov);

        //���/�����ƶ��ٶ�
        float GetSpeed() const { return movement_speed_; }
        void SetSpeed(float speed);

        //���/�����ӽ�������
        float GetSensitivity() const { return sensitivity_; }
        void SetSensitivity(float sensitivity);

        //���λ��
        Vec3 GetPosition()const { return position_; }

    private:
        void update();

    private:
        //ʵʱλ��
        Vec3           position_;
        Vec3           front_;
        Vec3           up_;
        Vec3           right_;

        //��ʼλ��
        Vec3           default_position_;
        Vec3           default_front_;
        Vec3           default_up_;

        //ŷ����
        EulerAngles     euler_angles_;

        //��Ұ��С
        float           fov_;

        //�ƶ��ٶ�
        float           movement_speed_;

        //�ӽ�������
        float           sensitivity_;
    };
}