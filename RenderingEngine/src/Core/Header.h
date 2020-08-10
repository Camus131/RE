#pragma once

#include <memory>


namespace OGE
{
#define SPtr(T) std::shared_ptr<T>

	class Object
	{
	public:
		//禁用拷贝构造和赋值
		Object(const Object&) = delete;
		Object& operator = (const Object&) = delete;

	protected:
		//防止外部创建对象
		Object() {}
	};
}