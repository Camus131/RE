#include "IndexBuffer.h"

#include "../Math/Math.h"


namespace OGE
{
	void IndexBuffer::ResetMemory(int size, Type type)
	{
		size_ = size;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
	}


	IndexBufferUByte::IndexBufferUByte(int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUByte";

		size_ = OGE::Maximum(0, size);

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		}
	}


	IndexBufferUByte::IndexBufferUByte(const std::vector<value_type>& indices, int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUByte";

		int data_size = indices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, &indices[0]);
	}


	IndexBufferUByte::IndexBufferUByte(const value_type* indices, int length, int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUByte";

		int data_size = length * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, indices);
	}


	bool IndexBufferUByte::UpdateData(const std::vector<value_type>& indices, int offset)
	{
		int data_size = indices.size() * sizeof(value_type);
		if (data_size + offset > size_)
			return false;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, data_size, &indices[0]);
		return true;
	}


	IndexBufferUShort::IndexBufferUShort(int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUShort";

		size_ = OGE::Maximum(0, size);

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		}
	}


	IndexBufferUShort::IndexBufferUShort(const std::vector<value_type>& indices, int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUShort";

		int data_size = indices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, &indices[0]);
	}


	IndexBufferUShort::IndexBufferUShort(const value_type* indices, int length, int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUShort";

		int data_size = length * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, indices);
	}


	bool IndexBufferUShort::UpdateData(const std::vector<value_type>& indices, int offset)
	{
		int data_size = indices.size() * sizeof(value_type);
		if (data_size + offset > size_)
			return false;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, data_size, &indices[0]);
		return true;
	}


	IndexBufferUInt::IndexBufferUInt(int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUInt";

		size_ = OGE::Maximum(0, size);

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		}
	}


	IndexBufferUInt::IndexBufferUInt(const std::vector<value_type>& indices, int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUInt";

		int data_size = indices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, &indices[0]);
	}


	IndexBufferUInt::IndexBufferUInt(const value_type* indices, int length, int size, Type type) :
		IndexBuffer()
	{
		name_ = "IndexBufferUInt";

		int data_size = length * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, indices);
	}


	bool IndexBufferUInt::UpdateData(const std::vector<value_type>& indices, int offset)
	{
		int data_size = indices.size() * sizeof(value_type);
		if (data_size + offset > size_)
			return false;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, data_size, &indices[0]);
		return true;
	}
}