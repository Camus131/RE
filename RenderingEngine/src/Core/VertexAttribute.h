#pragma once

#include "../Math/Vec2f.h"
#include "../Math/Vec3f.h"
#include "../Math/Vec4f.h"
#include "../Math/Matrixf.h"


namespace OGE
{
	//������ɫ���������Ը�ʽ

	//�𶥵�
	struct VertexAttrib_0
	{
		Vec3f	Position;
		Vec3f	Normal;
	};

	struct VertexAttrib_1
	{
		Vec3f	Position;
		Vec3f	Normal;
		Vec2f	TexCoord;
	};

	struct VertexAttrib_2
	{
		Vec3f	Position;
		Vec3f	Normal;
		Vec2f	TexCoord;
		Vec3f	Tangent;
		Vec3f	Bitangent;
	};

	//��ʵ��
	struct VertexAttrib_10
	{
		Matrixf		Transform;
	};
}