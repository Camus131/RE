#include "NodeVisitor.h"

#include "Object/DrawArrays.h"
#include "Object/DrawElements.h"


namespace OGE
{
	NodeVisitor::NodeVisitor(const std::vector<SPtr(Light)>& lights) :
		Visitor(),
		lights_(lights)
	{
		name_ = OGE_NodeVisitor;
		state_ = PhongState::Create();
		state_visitor_ = StateVisitor::Create(lights_);
	}


	void NodeVisitor::Visit(SPtr(Interviewee) object)
	{
		if (object == nullptr)
			return;

		switch (object->GetName())
		{
		case OGE_Mesh:
			Process(SPtrCast(Mesh, object));
			break;
		case OGE_Cube:
			Process(SPtrCast(Cube, object));
			break;
		case OGE_Group:
			Process(SPtrCast(Group, object));
			break;
		case OGE_Transform:
			Process(SPtrCast(Transform, object));
			break;
		}
	}


	void NodeVisitor::Process(SPtr(Mesh) mesh)
	{
		mesh->mask_++;

		//重复mesh只修改uniform list
		if (mesh->mask_ > 1)
		{
			SPtr(RenderingUnit) unit = units_.find(mesh)->second->Copy();

			//创建模型矩阵uniform
			SPtr(UniformList) model_matrixs_uniforms = UniformList::Create();
			model_matrixs_uniforms->AddUniform(UniformMat::Create("model", mesh->transfer_matrix_));
			model_matrixs_uniforms->AddUniform(UniformMat::Create("normalModel", Matrix::Transpose(Matrix::Inverse(mesh->transfer_matrix_))));
			unit->SetModelMatrixs(model_matrixs_uniforms);

			//创建材质uniform
			if (mesh->state_ == nullptr && mesh->transfer_state_ != state_)
			{
				mesh->transfer_state_->Accept(state_visitor_);
				unit->SetMaterials(state_visitor_->materials_);
				unit->SetEmissionMap(state_visitor_->emission_map_);
				unit->SetDiffuseMap(state_visitor_->diffuse_map_);
				unit->SetSpecularMap(state_visitor_->specular_map_);
				unit->SetShader(state_visitor_->shader_);
			}

			//添加至状态树
			if (OGE::IsEqual(SPtrCast(UniformFloat, unit->GetMaterials()->GetUniform("alpha"))->GetValue(), 1.0f))
				tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()][unit->GetVAO()].emplace_back(unit);
			else
				transparent_tree_.emplace_back(unit);

			units_[mesh] = unit;
			return;
		}

		//渲染所需对象
		SPtr(VBO) vbo = nullptr;
		SPtr(EBO) ebo = nullptr;
		SPtr(VAO) vao = nullptr;
		SPtr(DrawingCall) drawing_call = nullptr;
		SPtr(UniformList) model_matrixs_uniforms = nullptr;

		//计算所有顶点属性字节数
		int pos_array_size = mesh->position_array_.size() * sizeof(float) * 3;
		int norm_array_size = mesh->normal_array_.size() * sizeof(float) * 3;
		int uv_array_size = mesh->uv_array_.size() * sizeof(float) * 2;

		//检查是否设置drawing set
		if (mesh->drawing_set_ == nullptr)
			mesh->drawing_set_ = DrawArrays::Create(DrawArrays::Mode::TRIANGLES, 0, mesh->position_array_.size());

		//创建VBO，EBO，VAO
		vao = VAO::Create();
		vbo = VBO::Create(pos_array_size + norm_array_size + uv_array_size);

		vao->Bind();
		if (pos_array_size > 0)
		{
			vbo->UpdateData(mesh->position_array_);
			vao->EnableSetAttrib(0, 3, 3 * sizeof(float));
		}
		if (norm_array_size > 0)
		{
			vbo->UpdateData(mesh->normal_array_, pos_array_size);
			vao->EnableSetAttrib(1, 3, 3 * sizeof(float), pos_array_size);
		}
		if (uv_array_size > 0)
		{
			vbo->UpdateData(mesh->uv_array_, pos_array_size + norm_array_size);
			vao->EnableSetAttrib(2, 2, 2 * sizeof(float), pos_array_size + norm_array_size);
		}
		switch (mesh->drawing_set_->GetName())
		{
		case OGE_DrawElementsUByte:
			ebo = EBO_UByte::Create(SPtrCast(DrawElementsUByte, mesh->drawing_set_)->GetIndices());
			break;
		case OGE_DrawElementsUShort:
			ebo = EBO_UShort::Create(SPtrCast(DrawElementsUShort, mesh->drawing_set_)->GetIndices());
			break;
		case OGE_DrawElementsUInt:
			ebo = EBO_UInt::Create(SPtrCast(DrawElementsUInt, mesh->drawing_set_)->GetIndices());
			break;
		}
		vao->UnBind();

		//创建drawing call
		drawing_call = DrawingCall::Create(mesh->drawing_set_);

		//创建模型矩阵uniform
		model_matrixs_uniforms = UniformList::Create();
		model_matrixs_uniforms->AddUniform(UniformMat::Create("model", mesh->transfer_matrix_));
		model_matrixs_uniforms->AddUniform(UniformMat::Create("normalModel", Matrix::Transpose(Matrix::Inverse(mesh->transfer_matrix_))));

		//创建材质uniform
		SPtr(State) state = nullptr;
		if (mesh->state_ != nullptr)
			state = mesh->state_;
		else if (mesh->transfer_state_ != nullptr)
			state = mesh->transfer_state_;
		else
		{
			mesh->transfer_state_ = state_;
			state = state_;
		}
		state->Accept(state_visitor_);

		//创建渲染元
		SPtr(RenderingUnit) unit = RenderingUnit::Create();
		unit->SetLeaf(mesh);
		unit->SetVBO(vbo);
		unit->SetEBO(ebo);
		unit->SetVAO(vao);
		unit->SetDrawingCall(drawing_call);
		unit->SetModelMatrixs(model_matrixs_uniforms);
		unit->SetMaterials(state_visitor_->materials_);
		unit->SetEmissionMap(state_visitor_->emission_map_);
		unit->SetDiffuseMap(state_visitor_->diffuse_map_);
		unit->SetSpecularMap(state_visitor_->specular_map_);
		unit->SetShader(state_visitor_->shader_);

		//添加至状态树
		if (OGE::IsEqual(state_visitor_->alpha_, 1.0f))
			tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()][unit->GetVAO()].emplace_back(unit);
		else
			transparent_tree_.emplace_back(unit);

		units_[mesh] = unit;
	}


	void NodeVisitor::Process(SPtr(Cube) cube)
	{
		cube->mask_++;

		//重复mesh只修改uniform list
		if (cube->mask_ > 1)
		{
			SPtr(RenderingUnit) unit = units_.find(cube)->second->Copy();

			//创建模型矩阵uniform
			SPtr(UniformList) model_matrixs_uniforms = UniformList::Create();
			model_matrixs_uniforms->AddUniform(UniformMat::Create("model", cube->transfer_matrix_));
			model_matrixs_uniforms->AddUniform(UniformMat::Create("normalModel", Matrix::Transpose(Matrix::Inverse(cube->transfer_matrix_))));
			unit->SetModelMatrixs(model_matrixs_uniforms);

			//创建材质uniform
			if (cube->state_ == nullptr && cube->transfer_state_ != state_)
			{
				cube->transfer_state_->Accept(state_visitor_);
				unit->SetMaterials(state_visitor_->materials_);
				unit->SetEmissionMap(state_visitor_->emission_map_);
				unit->SetDiffuseMap(state_visitor_->diffuse_map_);
				unit->SetSpecularMap(state_visitor_->specular_map_);
				unit->SetShader(state_visitor_->shader_);
			}

			//添加至状态树
			if (OGE::IsEqual(SPtrCast(UniformFloat, unit->GetMaterials()->GetUniform("alpha"))->GetValue(), 1.0f))
				tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()][unit->GetVAO()].emplace_back(unit);
			else
				transparent_tree_.emplace_back(unit);

			units_[cube] = unit;
			return;
		}

		//生成顶点，索引数据
		BoundingBox box = cube->GetBoundingBox();
		Vec3 corner0 = box.Corner(0);
		Vec3 corner1 = box.Corner(1);
		Vec3 corner2 = box.Corner(2);
		Vec3 corner3 = box.Corner(3);
		Vec3 corner4 = box.Corner(4);
		Vec3 corner5 = box.Corner(5);
		Vec3 corner6 = box.Corner(6);
		Vec3 corner7 = box.Corner(7);

		Vec3Array pos_array =
		{
			//前
			corner4,
			corner7,
			corner6,
			//corner4,
			corner5,
			//corner7,

			//后
			corner1,
			corner2,
			corner3,
			//corner1,
			corner0,
			//corner2,

			//左
			corner0,
			corner6,
			corner2,
			//corner0,
			corner4,
			//corner6,

			//右
			corner5,
			corner3,
			corner7,
			//corner5,
			corner1,
			//corner3,

			//上
			corner6,
			corner3,
			corner2,
			//corner6,
			corner7,
			//corner3,

			//下
			corner0,
			corner5,
			corner4,
			//corner0,
			corner1,
			//corner5,
		};

		Vec3Array norm_array =
		{
			//前
			Z_AXIS,
			Z_AXIS,
			Z_AXIS,
			//Z_AXIS,
			Z_AXIS,
			//Z_AXIS,

			//后
			-Z_AXIS,
			-Z_AXIS,
			-Z_AXIS,
			//-Z_AXIS,
			-Z_AXIS,
			//-Z_AXIS,

			//左
			-X_AXIS,
			-X_AXIS,
			-X_AXIS,
			//-X_AXIS,
			-X_AXIS,
			//-X_AXIS,

			//右
			X_AXIS,
			X_AXIS,
			X_AXIS,
			//X_AXIS,
			X_AXIS,
			//X_AXIS,

			//上
			Y_AXIS,
			Y_AXIS,
			Y_AXIS,
			//Y_AXIS,
			Y_AXIS,
			//Y_AXIS,

			//下
			-Y_AXIS,
			-Y_AXIS,
			-Y_AXIS,
			//-Y_AXIS,
			-Y_AXIS,
			//-Y_AXIS,
		};

		Vec2 left_bottom(0.0f, 0.0f);
		Vec2 left_top(0.0f, 1.0f);
		Vec2 right_bottom(1.0f, 0.0f);
		Vec2 right_top(1.0f, 1.0f);

		Vec2Array uv_array =
		{
			//前
			left_bottom,
			right_top,
			left_top,
			//left_bottom,
			right_bottom,
			//right_top,

			//后
			left_bottom,
			right_top,
			left_top,
			//left_bottom,
			right_bottom,
			//right_top,

			//左
			left_bottom,
			right_top,
			left_top,
			//left_bottom,
			right_bottom,
			//right_top,

			//右
			left_bottom,
			right_top,
			left_top,
			//left_bottom,
			right_bottom,
			//right_top,

			//上
			left_bottom,
			right_top,
			left_top,
			//left_bottom,
			right_bottom,
			//right_top,

			//下
			left_bottom,
			right_top,
			left_top,
			//left_bottom,
			right_bottom,
			//right_top,
		};

		std::vector<unsigned char> indices =
		{
			//前
			0,1,2,
			0,3,1,
			//后
			4,5,6,
			4,7,5,
			//左
			8,9,10,
			8,11,9,
			//右
			12,13,14,
			12,15,13,
			//上
			16,17,18,
			16,19,17,
			//下
			20,21,22,
			20,23,21,
		};

		//渲染所需对象
		SPtr(VBO) vbo = nullptr;
		SPtr(EBO) ebo = nullptr;
		SPtr(VAO) vao = nullptr;
		SPtr(DrawingCall) drawing_call = nullptr;
		SPtr(UniformList) model_matrixs_uniforms = nullptr;

		//计算所有顶点属性字节数
		int pos_array_size = pos_array.size() * sizeof(float) * 3;
		int norm_array_size = norm_array.size() * sizeof(float) * 3;
		int uv_array_size = (cube->GetUvEnable() ? uv_array.size() : 0) * sizeof(float) * 2;

		//创建drawing set
		SPtr(DrawElementsUByte) drawing_set = DrawElementsUByte::Create(DrawElementsUByte::Mode::TRIANGLES, 0, indices.size());
		drawing_set->SetIndices(indices);

		//创建VBO，EBO，VAO
		vao = VAO::Create();
		vbo = VBO::Create(pos_array_size + norm_array_size + uv_array_size);

		vao->Bind();
		if (pos_array_size > 0)
		{
			vbo->UpdateData(pos_array);
			vao->EnableSetAttrib(0, 3, 3 * sizeof(float));
		}
		if (norm_array_size > 0)
		{
			vbo->UpdateData(norm_array, pos_array_size);
			vao->EnableSetAttrib(1, 3, 3 * sizeof(float), pos_array_size);
		}
		if (uv_array_size > 0)
		{
			vbo->UpdateData(uv_array, pos_array_size + norm_array_size);
			vao->EnableSetAttrib(2, 2, 2 * sizeof(float), pos_array_size + norm_array_size);
		}

		ebo = EBO_UByte::Create(indices);

		vao->UnBind();

		//创建drawing call
		drawing_call = DrawingCall::Create(drawing_set);

		//创建模型矩阵uniform
		model_matrixs_uniforms = UniformList::Create();
		model_matrixs_uniforms->AddUniform(UniformMat::Create("model", cube->transfer_matrix_));
		model_matrixs_uniforms->AddUniform(UniformMat::Create("normalModel", Matrix::Transpose(Matrix::Inverse(cube->transfer_matrix_))));

		//创建材质uniform
		SPtr(State) state = nullptr;
		if (cube->state_ != nullptr)
			state = cube->state_;
		else if (cube->transfer_state_ != nullptr)
			state = cube->transfer_state_;
		else
			state = state_;
		state->Accept(state_visitor_);

		//创建渲染元
		SPtr(RenderingUnit) unit = RenderingUnit::Create();
		unit->SetLeaf(cube);
		unit->SetVBO(vbo);
		unit->SetEBO(ebo);
		unit->SetVAO(vao);
		unit->SetDrawingCall(drawing_call);
		unit->SetModelMatrixs(model_matrixs_uniforms);
		unit->SetMaterials(state_visitor_->materials_);
		unit->SetEmissionMap(state_visitor_->emission_map_);
		unit->SetDiffuseMap(state_visitor_->diffuse_map_);
		unit->SetSpecularMap(state_visitor_->specular_map_);
		unit->SetShader(state_visitor_->shader_);

		//添加至状态树
		if (OGE::IsEqual(state_visitor_->alpha_, 1.0f))
			tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()][unit->GetVAO()].emplace_back(unit);
		else
			transparent_tree_.emplace_back(unit);

		units_[cube] = unit;
	}


	void NodeVisitor::Process(SPtr(Group) group)
	{
		//if (group->mask_)
		//	return;
		//group->mask_ = 1;

		if (group->children_.empty())
			return;

		for (unsigned int i = 0; i < group->children_.size(); ++i)
		{
			SPtr(Node) child = group->children_[i];

			//传递state和矩阵
			if (child->transfer_state_ == nullptr)
				child->transfer_state_ = group->transfer_state_;
			child->transfer_matrix_ = group->transfer_matrix_;
			
			Visit(child);
		}
	}


	void NodeVisitor::Process(SPtr(Transform) transform)
	{
		//if (transform->mask_)
		//	return;
		//transform->mask_ = 1;

		if (transform->children_.empty())
			return;

		for (unsigned int i = 0; i < transform->children_.size(); ++i)
		{
			SPtr(Node) child = transform->children_[i];

			//传递state和矩阵
			if (child->transfer_state_ == nullptr || child->GetName() == OGE_Mesh || child->GetName() == OGE_Cube)
				child->transfer_state_ = transform->transfer_state_;
			child->transfer_matrix_ = transform->transfer_matrix_ * transform->matrix_;

			Visit(child);
		}
	}
}