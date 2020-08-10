#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"


namespace OGE
{
	class VertexArray :public GLObject
	{
	public:
		//����ʵ��
		static SPtr(VertexArray) Create()
		{
			return SPtr(VertexArray)(new VertexArray);
		}

		~VertexArray() { glDeleteVertexArrays(1, &id_); }

		void Bind() const { glBindVertexArray(id_); }
		void UnBind() const { glBindVertexArray(0); }

		//��VBO��EBO
		//ʹ��ǰ�����Bind()
		void BindVBO(SPtr(VBO) vbo) const { vbo->Bind(); }
		void BindEBO(SPtr(EBO_UByte) ebo) const { ebo->Bind(); }
		void BindEBO(SPtr(EBO_UShort) ebo) const { ebo->Bind(); }
		void BindEBO(SPtr(EBO_UInt) ebo) const { ebo->Bind(); }

		//����/���ö�������
		//ʹ��ǰ�����Bind()
		void EnableAttrib(unsigned int location) const { glEnableVertexAttribArray(location); }
		void DisableAttrib(unsigned int location) const { glDisableVertexAttribArray(location); }

		//���ö�������
		//locationΪ����λ�ã�sizeΪ���԰�����float������strideΪ�����Լ䲽����offsetΪ��һ������λ��
		//ʹ��ǰ�����Bind()
		void SetAttrib(unsigned int location, int size, int stride, int offset) const
		{
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)offset);
		}

		//���ò����ö�������
		//locationΪ����λ�ã�sizeΪ���԰�����float������strideΪ�����Լ䲽����offsetΪ��һ������λ��
		//ʹ��ǰ�����Bind()
		void EnableSetAttrib(unsigned int location, int size, int stride, int offset) const
		{
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		}

	private:
		VertexArray():
			GLObject()
		{
			glGenVertexArrays(1, &id_);
		}
	};

	typedef VertexArray VAO;
}