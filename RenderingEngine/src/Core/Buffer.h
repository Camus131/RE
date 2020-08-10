#pragma once

#include "GLObject.h"


namespace OGE
{
	//1MB的字节长度
	const int BUFFER_SIZE_1MB = 1048576;

	class Buffer :public GLObject
	{
	public:
		//缓存数据类型
		enum Type
		{
			STREAM_DRAW = GL_STREAM_DRAW,
			STREAM_READ = GL_STREAM_READ,
			STREAM_COPY = GL_STREAM_COPY,
			STATIC_DRAW = GL_STATIC_DRAW,
			STATIC_READ = GL_STATIC_READ,
			STATIC_COPY = GL_STATIC_COPY,
			DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
			DYNAMIC_READ = GL_DYNAMIC_READ,
			DYNAMIC_COPY = GL_DYNAMIC_COPY,
		};

		//返回缓存字节长度
		int Size() const { return size_; }

		//返回true表示缓存大小为0
		bool IsEmpty() const { return size_ == 0; }

	protected:
		//防止外部创建对象
		Buffer() :
			GLObject(),
			size_(0) {}

	protected:
		//缓存字节长度
		int		size_;
	};
}