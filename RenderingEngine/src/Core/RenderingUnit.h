#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderSource.h"
#include "DrawingCall.h"
#include "Texture2DSource.h"
#include "UniformList.h"

#include "../Object/Mesh.h"


namespace OGE
{
	class RenderingUnit :public Object
	{
	public:
		//����ʵ��
		static SPtr(RenderingUnit) Create()
		{
			return SPtr(RenderingUnit)(new RenderingUnit);
		}

		//���/����shader
		SPtr(ShaderSource) GetShader() const { return shader_; }
		void SetShader(SPtr(ShaderSource) shader) { shader_ = shader; }

		//���/����emission map
		SPtr(Texture2DSource) GetEmissionMap() const { return emission_map_; }
		void SetEmissionMap(SPtr(Texture2DSource) emission_map) { emission_map_ = emission_map; }

		//���/����diffuse map
		SPtr(Texture2DSource) GetDiffuseMap() const { return diffuse_map_; }
		void SetDiffuseMap(SPtr(Texture2DSource) diffuse_map) { diffuse_map_ = diffuse_map; }

		//���/����specular map
		SPtr(Texture2DSource) GetSpecularMap() const { return specular_map_; }
		void SetSpecularMap(SPtr(Texture2DSource) specular_map) { specular_map_ = specular_map; }

		//���/����vbo
		SPtr(VBO) GetVBO() const { return vbo_; }
		void SetVBO(SPtr(VBO) vbo) { vbo_ = vbo; }

		//���/����ebo
		SPtr(EBO) GetEBO() const { return ebo_; }
		void SetEBO(SPtr(EBO) ebo) { ebo_ = ebo; }

		//���/����vao
		SPtr(VAO) GetVAO() const { return vao_; }
		void SetVAO(SPtr(VAO) vao) { vao_ = vao; }

		//���/����uniform�б�
		SPtr(UniformList) GetUniformList() const { return uniform_list_; }
		void SetUniformList(SPtr(UniformList) uniform_list) { uniform_list_ = uniform_list; }

		//���/����drawcall
		SPtr(DrawingCall) GetDrawingCall() const { return drawing_call_; }
		void SetDrawingCall(SPtr(DrawingCall) drawing_call) { drawing_call_ = drawing_call; }

		//���/����mesh
		SPtr(Mesh) GetMesh() const { return mesh_; }
		void SetMesh(SPtr(Mesh) mesh) { mesh_ = mesh; }

	protected:
		RenderingUnit() :
			Object()
		{
			name_ = "RenderingUnit";
		}

	protected:
		SPtr(ShaderSource)			shader_;

		SPtr(Texture2DSource)		emission_map_;

		SPtr(Texture2DSource)		diffuse_map_;

		SPtr(Texture2DSource)		specular_map_;

		SPtr(VBO)					vbo_;

		SPtr(EBO)					ebo_;

		SPtr(VAO)					vao_;

		SPtr(UniformList)			uniform_list_;

		SPtr(DrawingCall)			drawing_call_;

		SPtr(Mesh)					mesh_;
	};
}
