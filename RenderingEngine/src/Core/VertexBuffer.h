#pragma once

#include <vector>

#include "Buffer.h"


namespace OGE
{
	class VertexBuffer :public Buffer
	{
	public:
		typedef float value_type;

		//创建实例
		//vertices为要发送的顶点数据，size为开辟的缓存大小
		static SPtr(VertexBuffer) Create(const std::vector<value_type>& vertices, int size, Type type = STATIC_DRAW)
		{
			return SPtr(VertexBuffer)(new VertexBuffer(vertices, size, type));
		}

		//创建实例
		//vertices为要发送的顶点数据，length为indices的长度，size为的缓存大小
		static SPtr(VertexBuffer) Create(const value_type* vertices, int length, int size, Type type = STATIC_DRAW)
		{
			return SPtr(VertexBuffer)(new VertexBuffer(vertices, length, size, type));
		}

		~VertexBuffer() { glDeleteBuffers(1, &id_); }

		void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id_); }
		void UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		//更新缓存中的数据，返回false表示数据内容超出了缓存空间大小，更新失败
		//使用前需调用Bind()
		bool UpdateData(const std::vector<value_type>& vertices, int offset = 0);

		//重新分配缓存，开销较大
		//使用前需调用Bind()
		void ResetMemory(int size, Type type = STATIC_DRAW);

	private:
		VertexBuffer(const std::vector<value_type>& vertices, int size, Type type = STATIC_DRAW);
		VertexBuffer(const value_type* vertices, int length, int size, Type type = STATIC_DRAW);
	};

	typedef VertexBuffer VBO;
}