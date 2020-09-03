#include "Mesh.h"


namespace OGE
{
	Mesh::Mesh() :
		ExternalObject()
	{
		name_ = "Mesh";
	}


	SPtr(Mesh) Mesh::CreateBox()
	{
		SPtr(Mesh) mesh = SPtr(Mesh)(new Mesh);

		Vec3Array pos_array =
		{
			Vec3(-0.5f, 0.0f, -0.5f),
			Vec3( 0.5f, 0.0f, -0.5f),
			Vec3( 0.5f, 1.0f, -0.5f),	
			Vec3(-0.5f, 1.0f, -0.5f),	
			Vec3(-0.5f, 0.0f,  0.5f),	
			Vec3( 0.5f, 0.0f,  0.5f),	
			Vec3( 0.5f, 1.0f,  0.5f),	
			Vec3(-0.5f, 1.0f,  0.5f),	
			Vec3(-0.5f, 1.0f,  0.5f),	
			Vec3(-0.5f, 1.0f, -0.5f),	
			Vec3(-0.5f, 0.0f, -0.5f),	
			Vec3(-0.5f, 0.0f,  0.5f),	
			Vec3( 0.5f, 1.0f,  0.5f),	
			Vec3( 0.5f, 1.0f, -0.5f),	
			Vec3( 0.5f, 0.0f, -0.5f),	
			Vec3( 0.5f, 0.0f,  0.5f),	
			Vec3(-0.5f, 0.0f, -0.5f),	
			Vec3( 0.5f, 0.0f, -0.5f),	
			Vec3( 0.5f, 0.0f,  0.5f),	
			Vec3(-0.5f, 0.0f,  0.5f),	
			Vec3(-0.5f, 1.0f, -0.5f),	
			Vec3( 0.5f, 1.0f, -0.5f),	
			Vec3( 0.5f, 1.0f,  0.5f),	
			Vec3(-0.5f, 1.0f,  0.5f),	
		};

		Vec3Array normal_array =
		{
			Vec3( 0.0f,  0.0f, -1.0f),
			Vec3( 0.0f,  0.0f, -1.0f),
			Vec3( 0.0f,  0.0f, -1.0f),
			Vec3( 0.0f,  0.0f, -1.0f),
			Vec3( 0.0f,  0.0f,  1.0f),
			Vec3( 0.0f,  0.0f,  1.0f),
			Vec3( 0.0f,  0.0f,  1.0f),
			Vec3( 0.0f,  0.0f,  1.0f),
			Vec3(-1.0f,  0.0f,  0.0f),
			Vec3(-1.0f,  0.0f,  0.0f),
			Vec3(-1.0f,  0.0f,  0.0f),
			Vec3(-1.0f,  0.0f,  0.0f),
			Vec3( 1.0f,  0.0f,  0.0f),
			Vec3( 1.0f,  0.0f,  0.0f),
			Vec3( 1.0f,  0.0f,  0.0f),
			Vec3( 1.0f,  0.0f,  0.0f),
			Vec3( 0.0f, -1.0f,  0.0f),
			Vec3( 0.0f, -1.0f,  0.0f),
			Vec3( 0.0f, -1.0f,  0.0f),
			Vec3( 0.0f, -1.0f,  0.0f),
			Vec3( 0.0f,  1.0f,  0.0f),
			Vec3( 0.0f,  1.0f,  0.0f),
			Vec3( 0.0f,  1.0f,  0.0f),
			Vec3( 0.0f,  1.0f,  0.0f),
		};

		Vec2Array uv_array =
		{
			Vec2(0.0f, 0.0f),
			Vec2(1.0f, 0.0f),
			Vec2(1.0f, 1.0f),
			Vec2(0.0f, 1.0f),
			Vec2(0.0f, 0.0f),
			Vec2(1.0f, 0.0f),
			Vec2(1.0f, 1.0f),
			Vec2(0.0f, 1.0f),
			Vec2(1.0f, 0.0f),
			Vec2(1.0f, 1.0f),
			Vec2(0.0f, 1.0f),
			Vec2(0.0f, 0.0f),
			Vec2(1.0f, 0.0f),
			Vec2(1.0f, 1.0f),
			Vec2(0.0f, 1.0f),
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 1.0f),
			Vec2(1.0f, 1.0f),
			Vec2(1.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 1.0f),
			Vec2(1.0f, 1.0f),
			Vec2(1.0f, 0.0f),
			Vec2(0.0f, 0.0f),
		};

		SPtr(DrawElementsUByte) drawing_set = DrawElementsUByte::Create(DrawingSet::Mode::TRIANGLES, 0, 24);
		std::vector<unsigned char> indices =
		{
			0,1,2,
			2,3,0,
			4,5,6,
			6,7,4,
			8,9,10,
			10,11,8,
			12,13,14,
			14,15,12,
			16,17,18,
			18,19,16,
			20,21,22,
			22,23,20
		};
		drawing_set->SetIndices(indices);

		mesh->SetPosArray(pos_array);
		mesh->SetNormArray(normal_array);
		mesh->SetUvArray(uv_array);
		mesh->SetDrawingSet(drawing_set);

		return mesh;
	}
}