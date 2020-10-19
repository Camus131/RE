#pragma once

#include "Frustum.h"

#include "Math/EulerAnglesf.h"


namespace OGE
{
	class PerspectiveCamera :public Frustum
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

        //����ʵ��
        static SPtr(PerspectiveCamera) Create(const Vec3& eye, const Vec3& target, const Vec3& up, value_type fov, value_type ratio,
            value_type near_dis, value_type far_dis, value_type moving_speed = 1.0f, value_type turning_speed = 0.1f)
        {
            return SPtr(PerspectiveCamera)(new PerspectiveCamera(eye, target, up, fov, ratio,
                near_dis, far_dis, moving_speed, turning_speed));
        }

        //����ӵ�
        Vec3 GetEye() const { return eye_; }

        //���/�����ƶ��ٶ�
        value_type GetMovingSpeed() const { return moving_speed_; }
        void SetMovingSpeed(value_type speed);

        //���/����ת�ӽ��ٶ�
        value_type GetTurningSpeed() const { return turning_speed_; }
        void SetTurningSpeed(value_type speed);

        //��ͼ����
        Matrix ViewMatrix() const { return Matrix::LookAt(eye_, eye_ + front_, up_); }

        //ͶӰ����
        Matrix ProjectionMatrix() const { return Matrix::Perspective(fov_, ratio_, near_dis_, far_dis_); }

        //�ƶ����,frame_timeΪ֡����ʱ��
        void Move(Dir direction, value_type frame_time);

        //ת�����
        void Turn(value_type xoffset, value_type yoffset);

        //��ԭ���
        void Reset();

        //������������������
        void ComputeWorldPlanes();

        //����true��ʾ��Χ�пɼ�
        bool Intersect(const BoundingBox& bb);

	protected:
        PerspectiveCamera(const Vec3& eye, const Vec3& target, const Vec3& up, value_type fov, value_type ratio,
            value_type near_dis, value_type far_dis, value_type moving_speed = 1.0f, value_type turning_speed = 0.1f);

        //����λ��
        void ComputePos();

	protected:
        //ʵʱλ��
        Vec3           eye_;
        Vec3           front_;
        Vec3           up_;
        Vec3           right_;

        //��ʼλ��
        Vec3           init_eye_;
        Vec3           init_front_;
        Vec3           init_up_;

        //��תŷ����
        EulerAngles     rotate_angles_;

        //�ƶ��ٶ�
        value_type      moving_speed_;

        //ת�ӽ��ٶ�
        value_type      turning_speed_;

        //��������������
        Plane			near_plane_world_;
        Plane			far_plane_world_;
        Plane			bottom_plane_world_;
        Plane			top_plane_world_;
        Plane			left_plane_world_;
        Plane			right_plane_world_;
	};
}