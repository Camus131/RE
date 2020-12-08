#pragma once

#include "Core/BaseObject.h"

#include "Math/Matrixf.h"


namespace OGE
{
	class Viewport :public BaseObject
	{
	public:
		typedef float value_type;

		//����ʵ��
		static SPtr(Viewport) Create(value_type x = 0.0f, value_type y = 0.0f, value_type width = 1920.0f, value_type height = 1080.0f)
		{
			return SPtr(Viewport)(new Viewport(x, y, width, height));
		}

		//���/�������½�x����
		value_type GetX() const { return x_; }
		void SetX(value_type x) { x_ = x; }

		//���/�������½�y����
		value_type GetY() const { return y_; }
		void SetY(value_type y) { y_ = y; }

		//���/���ÿ�
		value_type GetWidth() const { return width_; }
		void SetWidth(value_type width) { width_ = width; }

		//���/���ø�
		value_type GetHeight() const { return height_; }
		void SetHeight(value_type height) { height_ = height; }

		//��߱�
		value_type AspectRatio() const { return width_ / height_; }

		//�ӿھ���
		Matrix ViewportMatrix() const
		{
			return  Matrix::Translate(x_, y_, 0.0f) * Matrix::Scale(width_ * 0.5f, height_ * 0.5f, 0.5f) * Matrix::Translate(1.0f, 1.0f, 1.0f);
		}

	protected:
		Viewport(value_type x = 0.0f, value_type y = 0.0f, value_type width = 1920.0f, value_type height = 1080.0f) :
			BaseObject(),
			x_(x),
			y_(y),
			width_(width),
			height_(height)
		{
			name_ = OGE_Viewport;
		}

	protected:
		value_type		x_;

		value_type		y_;

		value_type		width_;

		value_type		height_;
	};
}