#pragma once

#include "Header.h"

#include "glad/glad.h"


namespace OGE
{
	class GLObject :public Object
	{
	public:
		//����true��ʾ�������
		bool IsActive() const { return id_ != 0; }

		//���ض���id
		unsigned int Id()const { return id_; }

		//�󶨶�����������
		virtual void Bind() const = 0;

		//������������Ľ��
		virtual void UnBind() const = 0;

	protected:
		//��ֹ�ⲿ��������
		GLObject() :
			Object(),
			id_(0) {}

	protected:
		unsigned int	id_;
	};
}