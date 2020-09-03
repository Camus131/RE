#pragma once

#include "Object.h"


namespace OGE
{
	class ContextObject :public Object
	{
	public:
		//禁用拷贝构造和赋值
		ContextObject(const ContextObject&) = delete;
		ContextObject& operator = (const ContextObject&) = delete;

		//返回对象id
		unsigned int Id()const { return id_; }

		//绑定对象至上下文
		virtual void Bind() const = 0;

		//将对象从上下文解绑
		virtual void UnBind() const = 0;

	protected:
		ContextObject() :
			Object(),
			id_(0) {}

	protected:
		unsigned int	id_;
	};
}