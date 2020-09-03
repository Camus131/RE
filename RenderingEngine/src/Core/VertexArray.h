#pragma once

#include "ContextObject.h"


namespace OGE
{
	class VertexArray :public ContextObject
	{
	public:
		//创建实例
		static SPtr(VertexArray) Create()
		{
			return SPtr(VertexArray)(new VertexArray);
		}

		~VertexArray() { glDeleteVertexArrays(1, &id_); }

		void Bind() const { glBindVertexArray(id_); }
		void UnBind() const { glBindVertexArray(0); }

		//启用/禁用顶点属性
		//使用前需调用Bind()
		void EnableAttrib(unsigned int location) const { glEnableVertexAttribArray(location); }
		void DisableAttrib(unsigned int location) const { glDisableVertexAttribArray(location); }

		//配置顶点属性
		//location为属性位置，size为属性包含的float个数，stride为两属性间步长，offset为第一个属性位置
		//使用前需调用Bind()
		void SetAttrib(unsigned int location, int size, int stride, int offset = 0) const
		{
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		}

		//启用并配置顶点属性
		//location为属性位置，size为属性包含的float个数，stride为两属性间步长，offset为第一个属性位置
		//使用前需调用Bind()
		void EnableSetAttrib(unsigned int location, int size, int stride, int offset = 0) const
		{
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		}

	protected:
		VertexArray():
			ContextObject()
		{
			name_ = "VertexArray";
			glGenVertexArrays(1, &id_);
		}
	};

	typedef VertexArray VAO;
}