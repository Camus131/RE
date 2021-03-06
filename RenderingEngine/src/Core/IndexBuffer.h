#pragma once

#include "Buffer.h"


namespace OGE
{
	class IndexBuffer :public Buffer
	{
	public:
		//重新分配缓存，开销较大，size为缓存大小
		void ResetMemory(int size = 0, Type type = STATIC_DRAW);

		virtual void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }
		virtual void UnBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	protected:
		IndexBuffer(int size = 0, Type type = STATIC_DRAW) :
			Buffer(size, type) {}
	};


	class IndexBufferUByte :public IndexBuffer
	{
	public:
		typedef unsigned char value_type;

		//创建实例
		//size为缓存大小
		static SPtr(IndexBufferUByte) Create(int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUByte)(new IndexBufferUByte(size, type));
		}
		//indices为要发送的顶点数据，size为缓存大小
		static SPtr(IndexBufferUByte) Create(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUByte)(new IndexBufferUByte(indices, size, type));
		}

		//更新缓存中的数据，返回false表示数据内容超出了缓存空间大小，更新失败
		bool UpdateData(const std::vector<value_type>& indices, int offset = 0);

	protected:
		IndexBufferUByte(int size = 0, Type type = STATIC_DRAW);
		IndexBufferUByte(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW);
	};


	class IndexBufferUShort :public IndexBuffer
	{
	public:
		typedef unsigned short value_type;

		//创建实例
		//size为缓存大小
		static SPtr(IndexBufferUShort) Create(int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUShort)(new IndexBufferUShort(size, type));
		}
		//indices为要发送的顶点数据，size为缓存大小
		static SPtr(IndexBufferUShort) Create(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUShort)(new IndexBufferUShort(indices, size, type));
		}

		//更新缓存中的数据，返回false表示数据内容超出了缓存空间大小，更新失败
		bool UpdateData(const std::vector<value_type>& indices, int offset = 0);

	protected:
		IndexBufferUShort(int size = 0, Type type = STATIC_DRAW);
		IndexBufferUShort(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW);
	};


	class IndexBufferUInt :public IndexBuffer
	{
	public:
		typedef unsigned int value_type;

		//创建实例
		//size为缓存大小
		static SPtr(IndexBufferUInt) Create(int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUInt)(new IndexBufferUInt(size, type));
		}
		//indices为要发送的顶点数据，size为缓存大小
		static SPtr(IndexBufferUInt) Create(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUInt)(new IndexBufferUInt(indices, size, type));
		}

		//更新缓存中的数据，返回false表示数据内容超出了缓存空间大小，更新失败
		bool UpdateData(const std::vector<value_type>& indices, int offset = 0);

	protected:
		IndexBufferUInt(int size = 0, Type type = STATIC_DRAW);
		IndexBufferUInt(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW);
	};

	typedef IndexBuffer			EBO;
	typedef IndexBufferUByte	EBO_UByte;
	typedef IndexBufferUShort	EBO_UShort;
	typedef IndexBufferUInt		EBO_UInt;
}