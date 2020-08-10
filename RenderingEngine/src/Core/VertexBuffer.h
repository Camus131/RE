#pragma once

#include <vector>

#include "Buffer.h"


namespace OGE
{
	class VertexBuffer :public Buffer
	{
	public:
		typedef float value_type;

		//����ʵ��
		//verticesΪҪ���͵Ķ������ݣ�sizeΪ���ٵĻ����С
		static SPtr(VertexBuffer) Create(const std::vector<value_type>& vertices, int size, Type type = STATIC_DRAW)
		{
			return SPtr(VertexBuffer)(new VertexBuffer(vertices, size, type));
		}

		//����ʵ��
		//verticesΪҪ���͵Ķ������ݣ�lengthΪindices�ĳ��ȣ�sizeΪ�Ļ����С
		static SPtr(VertexBuffer) Create(const value_type* vertices, int length, int size, Type type = STATIC_DRAW)
		{
			return SPtr(VertexBuffer)(new VertexBuffer(vertices, length, size, type));
		}

		~VertexBuffer() { glDeleteBuffers(1, &id_); }

		void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id_); }
		void UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		//���»����е����ݣ�����false��ʾ�������ݳ����˻���ռ��С������ʧ��
		//ʹ��ǰ�����Bind()
		bool UpdateData(const std::vector<value_type>& vertices, int offset = 0);

		//���·��仺�棬�����ϴ�
		//ʹ��ǰ�����Bind()
		void ResetMemory(int size, Type type = STATIC_DRAW);

	private:
		VertexBuffer(const std::vector<value_type>& vertices, int size, Type type = STATIC_DRAW);
		VertexBuffer(const value_type* vertices, int length, int size, Type type = STATIC_DRAW);
	};

	typedef VertexBuffer VBO;
}