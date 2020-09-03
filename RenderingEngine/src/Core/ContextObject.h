#pragma once

#include "Object.h"


namespace OGE
{
	class ContextObject :public Object
	{
	public:
		//���ÿ�������͸�ֵ
		ContextObject(const ContextObject&) = delete;
		ContextObject& operator = (const ContextObject&) = delete;

		//���ض���id
		unsigned int Id()const { return id_; }

		//�󶨶�����������
		virtual void Bind() const = 0;

		//������������Ľ��
		virtual void UnBind() const = 0;

	protected:
		ContextObject() :
			Object(),
			id_(0) {}

	protected:
		unsigned int	id_;
	};
}