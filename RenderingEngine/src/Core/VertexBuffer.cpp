#include "VertexBuffer.h"


namespace OGE
{
	VertexBuffer::VertexBuffer(int size, Type type) :
		Buffer(size, type)
	{
		name_ = OGE_VertexBuffer;

		if (size_ > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id_);
			glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type_);
		}
	}


	VertexBuffer::VertexBuffer(const std::vector<value_type>& vertices, int size, Type type) :
		Buffer(size, type)
	{
		name_ = OGE_VertexBuffer;

		int data_size = vertices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size_);

		if (size_ > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id_);
			glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, &vertices[0]);
		}
	}


	bool VertexBuffer::UpdateData(const std::vector<value_type>& vertices, int offset)
	{
		int data_size = vertices.size() * sizeof(value_type);
		if (offset<0 || data_size + offset > size_)
			return false;

		glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, &vertices[0]);
		return true;
	}


	bool VertexBuffer::UpdateData(const Vec2Array& vertices, int offset)
	{
		int data_size = vertices.size() * sizeof(value_type) * 2;
		if (offset<0 || data_size + offset > size_)
			return false;

		glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, &vertices[0]);
		return true;
	}


	bool VertexBuffer::UpdateData(const Vec3Array& vertices, int offset)
	{
		int data_size = vertices.size() * sizeof(value_type) * 3;
		if (offset<0 || data_size + offset > size_)
			return false;

		glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, &vertices[0]);
		return true;
	}


	void VertexBuffer::ResetMemory(int size, Type type)
	{
		size_ = size;
		type_ = type;
		glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type_);
	}
}