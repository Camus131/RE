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

		//创建实例
		//size为缓存大小
		static SPtr(VertexBuffer) Create(int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(VertexBuffer)(new VertexBuffer(size, type));
		}
		//vertices为要发送的顶点数据，size为缓存大小
		static SPtr(VertexBuffer) Create(const std::vector<value_type>& vertices, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(VertexBuffer)(new VertexBuffer(vertices, size, type));
		}

		virtual void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id_); }
		virtual void UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		//更新缓存中的数据，返回false表示数据内容超出了缓存空间大小，更新失败
		bool UpdateData(const std::vector<value_type>& vertices, int offset = 0);
		bool UpdateData(const Vec2Array& vertices, int offset = 0);
		bool UpdateData(const Vec3Array& vertices, int offset = 0);

		//重新分配缓存，开销较大，size为缓存大小
		void ResetMemory(int size, Type type = STATIC_DRAW);

	protected:
		VertexBuffer(int size = 0, Type type = STATIC_DRAW);
		VertexBuffer(const std::vector<value_type>& vertices, int size = 0, Type type = STATIC_DRAW);
	};

	typedef VertexBuffer VBO;
}