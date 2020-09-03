#pragma once

#include "../Math/Vec2f.h"
#include "../Math/Vec3f.h"


namespace OGE
{
	//顶点属性格式
	struct Vertex
	{
		Vec3	Position;
	};

	struct Vertex_1 :public Vertex
	{
		Vec3	Normal;
	};

	struct Vertex_2 :public Vertex
	{
		Vec3	Normal;
		Vec2	TexCoord;
	};

	struct Vertex_3 :public Vertex
	{
		Vec3	Normal;
		Vec2	TexCoord;
		Vec3	Tangent;
		Vec3	Bitangent;
	};

	//索引格式
	struct Index
	{
	};

	struct IndexUByte :public Index
	{
		unsigned char	Index;
	};

	struct IndexUShort :public Index
	{
		unsigned short	Index;
	};

	struct IndexUInt :public Index
	{
		unsigned int	Index;
	};
}