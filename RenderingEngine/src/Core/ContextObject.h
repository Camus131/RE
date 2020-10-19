#pragma once

#include "BaseObject.h"


namespace OGE
{
	class ContextObject :public BaseObject
	{
	public:
		//���ÿ�������͸�ֵ
		ContextObject(const ContextObject&) = delete;
		ContextObject& operator = (const ContextObject&) = delete;

		//��ö���id
		unsigned int GetId()const { return id_; }

		//�󶨶�����������
		virtual void Bind() const = 0;

		//������������Ľ��
		virtual void UnBind() const = 0;

	protected:
		ContextObject() :
			BaseObject(),
			id_(0) {}

	protected:
		//����id
		unsigned int	id_;
	};
}