#pragma once

#include "ContextObject.h"


namespace OGE
{
	class Buffer :public ContextObject
	{
	public:
		//������������
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

		~Buffer() { glDeleteBuffers(1, &id_); }

		//��û����ֽڳ���
		int GetSize() const { return size_; }

		//��û�����������
		Type GetType() const { return type_; }

	protected:
		Buffer(int size = 0, Type type = STATIC_DRAW) :
			ContextObject(),
			size_(size),
			type_(type)
		{
			glGenBuffers(1, &id_);
		}

	protected:
		//�����ֽڳ���
		int			size_;
		//������������
		Type		type_;
	};
}