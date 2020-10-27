#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderSource.h"
#include "DrawingCall.h"
#include "Texture2DSource.h"

#include "Object/Leaf.h"


namespace OGE
{
	class RenderingUnit :public BaseObject
	{
	public:
		//����ʵ��
		static SPtr(RenderingUnit) Create()
		{
			return SPtr(RenderingUnit)(new RenderingUnit);
		}

		SPtr(RenderingUnit) Copy() const
		{
			SPtr(RenderingUnit) unit = RenderingUnit::Create();
			unit->shader_ = shader_;
			unit->emission_map_ = emission_map_;
			unit->diffuse_map_ = diffuse_map_;
			unit->specular_map_ = specular_map_;
			unit->vbo_ = vbo_;
			unit->ebo_ = ebo_;
			unit->vao_ = vao_;
			unit->model_matrixs_ = model_matrixs_;
			unit->materials_ = materials_;
			unit->drawing_call_ = drawing_call_;
			unit->leaf_ = leaf_;
			return unit;
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

		//���/����model matrixs
		SPtr(UniformList) GetModelMatrixs() const { return model_matrixs_; }
		void SetModelMatrixs(SPtr(UniformList) model_matrixs) { model_matrixs_ = model_matrixs; }

		//���/����materials
		SPtr(UniformList) GetMaterials() const { return materials_; }
		void SetMaterials(SPtr(UniformList) materials) { materials_ = materials; }

		//���/����drawcall
		SPtr(DrawingCall) GetDrawingCall() const { return drawing_call_; }
		void SetDrawingCall(SPtr(DrawingCall) drawing_call) { drawing_call_ = drawing_call; }

		//���/����Դ����
		SPtr(Leaf) GetLeaf() const { return leaf_; }
		void SetLeaf(SPtr(Leaf) leaf) { leaf_ = leaf; }

	protected:
		RenderingUnit() :
			BaseObject()
		{
			name_ = OGE_RenderingUnit;
		}

	protected:
		SPtr(ShaderSource)			shader_;

		SPtr(Texture2DSource)		emission_map_;

		SPtr(Texture2DSource)		diffuse_map_;

		SPtr(Texture2DSource)		specular_map_;

		SPtr(VBO)					vbo_;

		SPtr(EBO)					ebo_;

		SPtr(VAO)					vao_;

		SPtr(UniformList)			model_matrixs_;

		SPtr(UniformList)			materials_;

		SPtr(DrawingCall)			drawing_call_;

		SPtr(Leaf)					leaf_;
	};
}
