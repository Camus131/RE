#include "IndexBuffer.h"

#include "Math/Math.h"


namespace OGE
{
	void IndexBuffer::ResetMemory(int size, Type type)
	{
		size_ = size;
		type_ = type;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type_);
	}


	IndexBufferUByte::IndexBufferUByte(int size, Type type) :
		IndexBuffer(size, type)
	{
		name_ = OGE_IndexBufferUByte;

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type_);
		}
	}


	IndexBufferUByte::IndexBufferUByte(const std::vector<value_type>& indices, int size, Type type) :
		IndexBuffer(size, type)
	{
		name_ = OGE_IndexBufferUByte;

		int data_size = indices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size_);

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type_);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, &indices[0]);
		}
	}


	bool IndexBufferUByte::UpdateData(const std::vector<value_type>& indices, int offset)
	{
		int data_size = indices.size() * sizeof(value_type);
		if (offset<0 || data_size + offset > size_)
			return false;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, data_size, &indices[0]);
		return true;
	}


	IndexBufferUShort::IndexBufferUShort(int size, Type type) :
		IndexBuffer(size, type)
	{
		name_ = OGE_IndexBufferUShort;

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type_);
		}
	}


	IndexBufferUShort::IndexBufferUShort(const std::vector<value_type>& indices, int size, Type type) :
		IndexBuffer(size, type)
	{
		name_ = OGE_IndexBufferUShort;

		int data_size = indices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size_);

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type_);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, &indices[0]);
		}
	}


	bool IndexBufferUShort::UpdateData(const std::vector<value_type>& indices, int offset)
	{
		int data_size = indices.size() * sizeof(value_type);
		if (offset<0 || data_size + offset > size_)
			return false;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, data_size, &indices[0]);
		return true;
	}


	IndexBufferUInt::IndexBufferUInt(int size, Type type) :
		IndexBuffer(size, type)
	{
		name_ = OGE_IndexBufferUInt;

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type_);
		}
	}


	IndexBufferUInt::IndexBufferUInt(const std::vector<value_type>& indices, int size, Type type) :
		IndexBuffer(size, type)
	{
		name_ = OGE_IndexBufferUInt;

		int data_size = indices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size_);

		if (size_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, nullptr, type_);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data_size, &indices[0]);
		}
	}


	bool IndexBufferUInt::UpdateData(const std::vector<value_type>& indices, int offset)
	{
		int data_size = indices.size() * sizeof(value_type);
		if (offset<0 || data_size + offset > size_)
			return false;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, data_size, &indices[0]);
		return true;
	}
}