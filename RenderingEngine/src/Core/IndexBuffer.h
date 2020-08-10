#pragma once

#include <vector>

#include "Buffer.h"
#include "../Math/Math.h"


namespace OGE
{
	template<typename VT>
	class IndexBufferTL :public Buffer
	{
	public:
		typedef VT value_type;

		//创建实例
		//indices为要发送的顶点数据，size为开辟的缓存大小
		static SPtr(IndexBufferTL<VT>) Create(const std::vector<value_type>& indices, int size, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferTL<VT>)(new IndexBufferTL(indices, size, type));
		}

		//创建实例
		//indices为要发送的顶点数据，length为indices的长度，size为开辟的缓存大小
		static SPtr(IndexBufferTL<VT>) Create(const value_type* indices, int length, int size, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferTL<VT>)(new IndexBufferTL(indices, length, size, type));
		}

		~IndexBufferTL() { glDeleteBuffers(1, &id_); }

		void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }
		void UnBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		//更新缓存中的数据，返回false表示数据内容超出了缓存空间大小，更新失败
		//使用前需调用Bind()
		bool UpdateData(const std::vector<value_type>& indices, int offset = 0)
		{
			int data_size = indices.size() * sizeof(value_type);
			if (data_size + offset > size_)
				return false;

			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, data_size, &indices[0]);
			return true;
		}

		//重新分配缓存，开销较大
		//使用前需调用Bind()
		void ResetMemory(int size, Type type = STATIC_DRAW)
		{
			size_ = size;
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		}

	private:
		IndexBufferTL(const std::vector<value_type>& indices, int size, Type type = STATIC_DRAW) :
			Buffer()
		{
			int data_size = indices.size() * sizeof(value_type);
			size_ = OGE::Maximum(data_size, size);

			glGenBuffers(1, &id_);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, &indices[0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBufferTL(const value_type* indices, int length, int size, Type type = STATIC_DRAW) :
			Buffer()
		{
			int data_size = length * sizeof(value_type);
			size_ = OGE::Maximum(data_size, size);

			glGenBuffers(1, &id_);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, indices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	};

	typedef IndexBufferTL<unsigned char>	IndexBufferUByte;
	typedef IndexBufferTL<unsigned short>	IndexBufferUShort;
	typedef IndexBufferTL<unsigned int>		IndexBufferUInt;

	typedef IndexBufferUByte	EBO_UByte;
	typedef IndexBufferUShort	EBO_UShort;
	typedef IndexBufferUInt		EBO_UInt;
}