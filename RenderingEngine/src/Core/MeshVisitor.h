#pragma once

#include "Visitor.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "DrawingCall.h"
#include "UniformList.h"

#include "../Object/Mesh.h"


namespace OGE
{
	class MeshVisitor :public Visitor
	{
	public:
		//´´½¨ÊµÀý
		static SPtr(MeshVisitor) Create()
		{
			return SPtr(MeshVisitor)(new MeshVisitor);
		}

		virtual void Visit(SPtr(ExternalObject) object);

		SPtr(Mesh) GetMesh() const { return mesh_; }
		SPtr(VBO) GetVBO() const { return vbo_; }
		SPtr(EBO) GetEBO() const { return ebo_; }
		SPtr(VAO) GetVAO() const { return vao_; }
		SPtr(DrawingCall) GetDrawingCall() const { return drawing_call_; }
		SPtr(UniformList) GetUniformList() const { return uniform_list_; }
		SPtr(Texture2D) GetEmissionMap() const { return emission_map_; }
		SPtr(Texture2D) GetDiffuseMap() const { return diffuse_map_; }
		SPtr(Texture2D) GetSpecularMap() const { return specular_map_; }
		std::string GetVertexShaderCode() const { return vertex_shader_code_; }
		std::string GetFragmentShaderCode() const { return fragment_shader_code_; }

	protected:
		MeshVisitor();

		void GenVertexArray();
		void GenMaterial();
		void GenShaderCode();

	protected:
		SPtr(Mesh)			mesh_;
		SPtr(VBO)			vbo_;
		SPtr(EBO)			ebo_;
		SPtr(VAO)			vao_;
		SPtr(DrawingCall)	drawing_call_;
		SPtr(UniformList)	uniform_list_;
		SPtr(Texture2D)		emission_map_;
		SPtr(Texture2D)		diffuse_map_;
		SPtr(Texture2D)		specular_map_;
		std::string			vertex_shader_code_;
		std::string			fragment_shader_code_;
	};
}