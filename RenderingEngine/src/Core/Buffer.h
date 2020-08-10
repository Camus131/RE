#pragma once

#include "GLObject.h"


namespace OGE
{
	//1MB���ֽڳ���
	const int BUFFER_SIZE_1MB = 1048576;

	class Buffer :public GLObject
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

		//���ػ����ֽڳ���
		int Size() const { return size_; }

		//����true��ʾ�����СΪ0
		bool IsEmpty() const { return size_ == 0; }

	protected:
		//��ֹ�ⲿ��������
		Buffer() :
			GLObject(),
			size_(0) {}

	protected:
		//�����ֽڳ���
		int		size_;
	};
}