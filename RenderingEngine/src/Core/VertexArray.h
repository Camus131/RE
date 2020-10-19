#pragma once

#include "ContextObject.h"


namespace OGE
{
	class VertexArray :public ContextObject
	{
	public:
		//����ʵ��
		static SPtr(VertexArray) Create()
		{
			return SPtr(VertexArray)(new VertexArray);
		}

		~VertexArray() { glDeleteVertexArrays(1, &id_); }

		virtual void Bind() const { glBindVertexArray(id_); }
		virtual void UnBind() const { glBindVertexArray(0); }

		//����/���ö�������
		//ʹ��ǰ�����Bind()
		void EnableAttrib(unsigned int location) const { glEnableVertexAttribArray(location); }
		void DisableAttrib(unsigned int location) const { glDisableVertexAttribArray(location); }

		//���ö�������
		//locationΪ����λ�ã�sizeΪ���԰�����float������strideΪ�����Լ䲽����offsetΪ��һ������λ��
		void SetAttrib(unsigned int location, int size, int stride, int offset = 0) const
		{
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		}

		//���ò����ö�������
		//locationΪ����λ�ã�sizeΪ���԰�����float������strideΪ�����Լ䲽����offsetΪ��һ������λ��
		void EnableSetAttrib(unsigned int location, int size, int stride, int offset = 0) const
		{
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		}

	protected:
		VertexArray():
			ContextObject()
		{
			name_ = OGE_VertexArray;
			glGenVertexArrays(1, &id_);
		}
	};

	typedef VertexArray VAO;
}