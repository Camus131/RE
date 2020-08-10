#pragma once

#include "Header.h"

#include "glad/glad.h"


namespace OGE
{
	class GLObject :public Object
	{
	public:
		//返回true表示对象可用
		bool IsActive() const { return id_ != 0; }

		//返回对象id
		unsigned int Id()const { return id_; }

		//绑定对象至上下文
		virtual void Bind() const = 0;

		//将对象从上下文解绑
		virtual void UnBind() const = 0;

	protected:
		//防止外部创建对象
		GLObject() :
			Object(),
			id_(0) {}

	protected:
		unsigned int	id_;
	};
}