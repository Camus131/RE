#pragma once

#include <memory>


namespace OGE
{
#define SPtr(T) std::shared_ptr<T>

	class Object
	{
	public:
		//���ÿ�������͸�ֵ
		Object(const Object&) = delete;
		Object& operator = (const Object&) = delete;

	protected:
		//��ֹ�ⲿ��������
		Object() {}
	};
}