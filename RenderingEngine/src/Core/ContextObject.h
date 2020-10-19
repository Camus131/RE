#pragma once

#include "BaseObject.h"


namespace OGE
{
	class ContextObject :public BaseObject
	{
	public:
		//禁用拷贝构造和赋值
		ContextObject(const ContextObject&) = delete;
		ContextObject& operator = (const ContextObject&) = delete;

		//获得对象id
		unsigned int GetId()const { return id_; }

		//绑定对象至上下文
		virtual void Bind() const = 0;

		//将对象从上下文解绑
		virtual void UnBind() const = 0;

	protected:
		ContextObject() :
			BaseObject(),
			id_(0) {}

	protected:
		//对象id
		unsigned int	id_;
	};
}