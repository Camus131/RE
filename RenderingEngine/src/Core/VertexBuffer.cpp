#include "VertexBuffer.h"

#include "../Math/Math.h"


namespace OGE
{
	VertexBuffer::VertexBuffer(const std::vector<value_type>& vertices, int size, Type type) :
		Buffer()
	{
		int data_size = vertices.size() * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glGenBuffers(1, &id_);
		glBindBuffer(GL_ARRAY_BUFFER, id_);
		glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, &vertices[0]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	VertexBuffer::VertexBuffer(const value_type* vertices, int length, int size, Type type) :
		Buffer()
	{
		int data_size = length * sizeof(value_type);
		size_ = OGE::Maximum(data_size, size);

		glGenBuffers(1, &id_);
		glBindBuffer(GL_ARRAY_BUFFER, id_);
		glBufferData(GL_ARRAY_BUFFER, size_, nullptr, type);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	bool VertexBuffer::UpdateData(const std::vector<value_type>& vertices, int offset)
	{
		int data_size = vertices.size() * sizeof(value_type);
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