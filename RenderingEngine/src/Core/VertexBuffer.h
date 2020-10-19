#pragma once

#include "Buffer.h"

#include "Math/Vec2f.h"
#include "Math/Vec3f.h"


namespace OGE
{
	class VertexBuffer :public Buffer
	{
	public:
		typedef float value_type;

		//����ʵ��
		//sizeΪ�����С
		static SPtr(VertexBuffer) Create(int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(VertexBuffer)(new VertexBuffer(size, type));
		}
		//verticesΪҪ���͵Ķ������ݣ�sizeΪ�����С
		static SPtr(VertexBuffer) Create(const std::vector<value_type>& vertices, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(VertexBuffer)(new VertexBuffer(vertices, size, type));
		}

		virtual void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id_); }
		virtual void UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		//���»����е����ݣ�����false��ʾ�������ݳ����˻���ռ��С������ʧ��
		bool UpdateData(const std::vector<value_type>& vertices, int offset = 0);
		bool UpdateData(const Vec2Array& vertices, int offset = 0);
		bool UpdateData(const Vec3Array& vertices, int offset = 0);

		//���·��仺�棬�����ϴ�sizeΪ�����С
		void ResetMemory(int size, Type type = STATIC_DRAW);

	protected:
		VertexBuffer(int size = 0, Type type = STATIC_DRAW);
		VertexBuffer(const std::vector<value_type>& vertices, int size = 0, Type type = STATIC_DRAW);
	};

	typedef VertexBuffer VBO;
}