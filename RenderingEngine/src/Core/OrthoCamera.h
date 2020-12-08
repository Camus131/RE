#pragma once

#include "Frustum.h"

#include "Math/EulerAnglesf.h"


namespace OGE
{
    class OrthoCamera :public Frustum
    {
    public:
        //����ʵ��
        static SPtr(OrthoCamera) Create(const Vec3& eye, const Vec3& target, const Vec3& up, value_type left, value_type right, value_type bottom, value_type top,
            value_type near_dis, value_type far_dis, value_type dragging_speed = 1.0f, value_type turning_speed = 0.1f)
        {
            return SPtr(OrthoCamera)(new OrthoCamera(eye, target, up, left, right, bottom, top,
                near_dis, far_dis, dragging_speed, turning_speed));
        }

        //���/������
        value_type GetLeft() const { return xleft_; }
        void SetLeft(value_type left) { xleft_ = left; }

        //���/������
        value_type GetRight() const { return xright_; }
        void SetRight(value_type right) { xright_ = right; }

        //���/������
        value_type GetBottom() const { return ybottom_; }
        void SetBottom(value_type bottom) { ybottom_ = bottom; }

        //���/������
        value_type GetTop() const { return ytop_; }
        void SetTop(value_type top) { ytop_ = top; }

        //����ӵ�
        Vec3 GetEye() const { return eye_; }

        //���/�����ƶ��ٶ�
        value_type GetDraggingSpeed() const { return dragging_speed_; }
        void SetDraggingSpeed(value_type speed);

        //���/����ת�ӽ��ٶ�
        value_type GetTurningSpeed() const { return turning_speed_; }
        void SetTurningSpeed(value_type speed);

        //��ͼ����
        Matrix ViewMatrix() const { return Matrix::LookAt(eye_, eye_ + front_, up_); }

        //ͶӰ����
        Matrix ProjectionMatrix() const { return Matrix::Ortho(xleft_, xright_, ybottom_, ytop_, near_dis_, far_dis_); }

        //�����Ӿ���
        void Scale(value_type offset);

        //�ƶ����,frame_timeΪ֡����ʱ��
        void Move(value_type xoffset, value_type yoffset, value_type frame_time);

        //ת�����
        void Turn(value_type xoffset, value_type yoffset);

        //��ԭ���
        void Reset();

        //������������������
        void ComputePlanes();

        //����true��ʾ��Χ�пɼ�
        bool Intersect(const BoundingBox& bb);

    protected:
        OrthoCamera(const Vec3& eye, const Vec3& target, const Vec3& up, value_type left, value_type right, value_type bottom, value_type top,
            value_type near_dis, value_type far_dis, value_type dragging_speed = 1.0f, value_type turning_speed = 0.1f);

        //����λ��
        void ComputePos();

    protected:
        //��������
        value_type		xleft_;
        value_type		xright_;
        value_type		ybottom_;
        value_type		ytop_;

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

        //��ק�ٶ�
        value_type      dragging_speed_;

        //ת�ӽ��ٶ�
        value_type      turning_speed_;
    };
}