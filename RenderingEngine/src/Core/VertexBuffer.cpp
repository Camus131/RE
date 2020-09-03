#include "VertexBuffer.h"

#include "../Math/Math.h"


namespace OGE
{
	VertexBuffer::VertexBuffer(int size, Type type) :
		Buffer()
	{
		name_ = "VertexBuffer";

		size_ = OGE::Maximum(0, size);

		if (size_ > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id_);
			glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type);
		}
	}


	VertexBuffer::VertexBuffer(const std::vector<value_type>& vertices, int size, Type type) :
		Buffer()
	{
		name_ = "VertexBuffer";

		int data_size = vertices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glBindBuffer(GL_ARRAY_BUFFER, id_);
		glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, &vertices[0]);
	}


	VertexBuffer::VertexBuffer(const value_type* vertices, int length, int size, Type type) :
		Buffer()
	{
		name_ = "VertexBuffer";

		int data_size = length * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glBindBuffer(GL_ARRAY_BUFFER, id_);
		glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, vertices);
	}


	bool VertexBuffer::UpdateData(const std::vector<value_type>& vertices, int offset)
	{
		int data_size = vertices.size() * sizeof(value_type);
		if (data_size + offset > size_)
			return false;

		glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, &vertices[0]);
		return true;
	}


	bool VertexBuffer::UpdateData(const Vec2Array& vertices, int offset)
	{
		int data_size = vertices.size() * sizeof(value_type) * 2;
		if (data_size + offset > size_)
			return false;

		glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, &vertices[0]);
		return true;
	}


	bool VertexBuffer::UpdateData(const Vec3Array& vertices, int offset)
	{
		int data_size = vertices.size() * sizeof(value_type) * 3;
		if (data_size + offset > size_)
			return false;

		glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, &vertices[0]);
		return true;
	}


	void VertexBuffer::ResetMemory(int size, Type type)
	{
		size_ = size;
		glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type);
	}
}