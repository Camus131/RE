#pragma once

#include "Buffer.h"


namespace OGE
{
	class IndexBuffer :public Buffer
	{
	public:
		//���·��仺�棬�����ϴ�sizeΪ�����С
		void ResetMemory(int size, Type type = STATIC_DRAW);

	protected:
		IndexBuffer() :
			Buffer() {}
	};


	class IndexBufferUByte :public IndexBuffer
	{
	public:
		typedef unsigned char value_type;

		//����ʵ��
		//sizeΪ�����С
		static SPtr(IndexBufferUByte) Create(int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUByte)(new IndexBufferUByte(size, type));
		}
		//indicesΪҪ���͵Ķ������ݣ�sizeΪ�����С
		static SPtr(IndexBufferUByte) Create(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUByte)(new IndexBufferUByte(indices, size, type));
		}
		//indicesΪҪ���͵Ķ������ݣ�lengthΪindices�ĳ��ȣ�sizeΪ�����С
		static SPtr(IndexBufferUByte) Create(const value_type* indices, int length, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUByte)(new IndexBufferUByte(indices, length, size, type));
		}

		void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }
		void UnBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		//���»����е����ݣ�����false��ʾ�������ݳ����˻���ռ��С������ʧ��
		//ʹ��ǰ�����Bind()
		bool UpdateData(const std::vector<value_type>& indices, int offset = 0);

	protected:
		IndexBufferUByte(int size = 0, Type type = STATIC_DRAW);
		IndexBufferUByte(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW);
		IndexBufferUByte(const value_type* indices, int length, int size = 0, Type type = STATIC_DRAW);
	};


	class IndexBufferUShort :public IndexBuffer
	{
	public:
		typedef unsigned short value_type;

		//����ʵ��
		//sizeΪ�����С
		static SPtr(IndexBufferUShort) Create(int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUShort)(new IndexBufferUShort(size, type));
		}
		//indicesΪҪ���͵Ķ������ݣ�sizeΪ�����С
		static SPtr(IndexBufferUShort) Create(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUShort)(new IndexBufferUShort(indices, size, type));
		}
		//indicesΪҪ���͵Ķ������ݣ�lengthΪindices�ĳ��ȣ�sizeΪ�����С
		static SPtr(IndexBufferUShort) Create(const value_type* indices, int length, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUShort)(new IndexBufferUShort(indices, length, size, type));
		}

		void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }
		void UnBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		//���»����е����ݣ�����false��ʾ�������ݳ����˻���ռ��С������ʧ��
		//ʹ��ǰ�����Bind()
		bool UpdateData(const std::vector<value_type>& indices, int offset = 0);

	protected:
		IndexBufferUShort(int size = 0, Type type = STATIC_DRAW);
		IndexBufferUShort(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW);
		IndexBufferUShort(const value_type* indices, int length, int size = 0, Type type = STATIC_DRAW);
	};


	class IndexBufferUInt :public IndexBuffer
	{
	public:
		typedef unsigned int value_type;

		//����ʵ��
		//sizeΪ�����С
		static SPtr(IndexBufferUInt) Create(int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUInt)(new IndexBufferUInt(size, type));
		}
		//indicesΪҪ���͵Ķ������ݣ�sizeΪ�����С
		static SPtr(IndexBufferUInt) Create(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUInt)(new IndexBufferUInt(indices, size, type));
		}
		//indicesΪҪ���͵Ķ������ݣ�lengthΪindices�ĳ��ȣ�sizeΪ�����С
		static SPtr(IndexBufferUInt) Create(const value_type* indices, int length, int size = 0, Type type = STATIC_DRAW)
		{
			return SPtr(IndexBufferUInt)(new IndexBufferUInt(indices, length, size, type));
		}

		void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }
		void UnBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		//���»����е����ݣ�����false��ʾ�������ݳ����˻���ռ��С������ʧ��
		//ʹ��ǰ�����Bind()
		bool UpdateData(const std::vector<value_type>& indices, int offset = 0);

	protected:
		IndexBufferUInt(int size = 0, Type type = STATIC_DRAW);
		IndexBufferUInt(const std::vector<value_type>& indices, int size = 0, Type type = STATIC_DRAW);
		IndexBufferUInt(const value_type* indices, int length, int size = 0, Type type = STATIC_DRAW);
	};

	typedef IndexBuffer			EBO;
	typedef IndexBufferUByte	EBO_UByte;
	typedef IndexBufferUShort	EBO_UShort;
	typedef IndexBufferUInt		EBO_UInt;
}