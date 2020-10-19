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

		//重复mesh只修改model矩阵
		if (mesh->mask_ > 1)
		{
			SPtr(RenderingUnit) unit = units_.find(mesh)->second->Copy();
			SPtr(UniformList) model_matrixs_uniforms = UniformList::Create();
			model_matrixs_uniforms->AddUniform(UniformMat::Create("model", mesh->transfer_));
			model_matrixs_uniforms->AddUniform(UniformMat::Create("normalModel", Matrix::Transpose(Matrix::Inverse(mesh->transfer_))));
			unit->SetModelMatrixs(model_matrixs_uniforms);
			tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()][unit->GetVAO()].emplace_back(unit);
			units_[mesh] = unit;
			return;
		}

		//渲染所需对象
		SPtr(VBO) vbo = nullptr;
		SPtr(EBO) ebo = nullptr;
		SPtr(VAO) vao = nullptr;
		SPtr(DrawingCall) drawing_call = nullptr;
		SPtr(UniformList) model_matrixs_uniforms = nullptr;
		SPtr(UniformList) material_uniforms = nullptr;
		SPtr(Texture2D) emission_map = nullptr;
		SPtr(Texture2D) diffuse_map = nullptr;
		SPtr(Texture2D) specular_map = nullptr;
		std::string	vertex_shader_code = "";
		std::string	fragment_shader_code = "";

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
			vbo->UpdateData(mesh->uv_array_, norm_array_size);
			vao->EnableSetAttrib(2, 2, 2 * sizeof(float), norm_array_size);
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
		model_matrixs_uniforms->AddUniform(UniformMat::Create("model", mesh->transfer_));
		model_matrixs_uniforms->AddUniform(UniformMat::Create("normalModel", Matrix::Transpose(Matrix::Inverse(mesh->transfer_))));

		//创建材质uniform
		material_uniforms = UniformList::Create();
		if (mesh->state_ == nullptr)
			mesh->state_ = state_;

		switch (mesh->state_->GetName())
		{
		case OGE_PhongState:
		{
			SPtr(PhongState) phong_state = SPtrCast(PhongState, mesh->state_);
			SPtr(Material) material = phong_state->GetMaterial();

			//添加材质
			if (material->GetEmissionMap() != nullptr)
			{
				emission_map = material->GetEmissionMap();
				material_uniforms->AddUniform(UniformInt::Create("material.emission", 0));
			}
			else
				material_uniforms->AddUniform(UniformVec3::Create("material.emission", material->GetEmissionColor()));

			if (material->GetDiffuseMap() != nullptr)
			{
				diffuse_map = material->GetDiffuseMap();
				material_uniforms->AddUniform(UniformInt::Create("material.diffuse", 1));
			}
			else
				material_uniforms->AddUniform(UniformVec3::Create("material.diffuse", material->GetDiffuseColor()));

			if (material->GetSpecularMap() != nullptr)
			{
				specular_map = material->GetSpecularMap();
				material_uniforms->AddUniform(UniformInt::Create("material.specular", 2));
			}
			else
				material_uniforms->AddUniform(UniformVec3::Create("material.specular", material->GetSpecularColor()));

			material_uniforms->AddUniform(UniformFloat::Create("material.shininess", material->GetShininess()));

			//添加光源
			material_uniforms->AddUniform(UniformVec3::Create("light.ambient", lights_[0]->GetAmbient()));
			material_uniforms->AddUniform(UniformVec3::Create("light.diffuse", lights_[0]->GetDiffuse()));
			material_uniforms->AddUniform(UniformVec3::Create("light.specular", lights_[0]->GetSpecular()));
			ObjectName name = lights_[0]->GetName();
			switch (name)
			{
			case OGE_DirLight:
			{
				SPtr(DirLight) dir_light = SPtrCast(DirLight, lights_[0]);
				material_uniforms->AddUniform(UniformVec3::Create("light.direction", dir_light->GetDir()));
			}break;
			case OGE_PointLight:
			{
				SPtr(PointLight) point_light = SPtrCast(PointLight, lights_[0]);
				material_uniforms->AddUniform(UniformVec3::Create("light.position", point_light->GetPosition()));
			}break;
			}

			//创建shader
			bool NORMAL = norm_array_size > 0;
			bool TEXCOORD = uv_array_size > 0;
			bool EMISSION_MAP = emission_map != nullptr;
			bool DIFFUSE_MAP = diffuse_map != nullptr;
			bool SPECULAR_MAP = specular_map != nullptr;
			bool DIR_LIGHT = name == OGE_DirLight;
			bool POINT_LIGHT = name == OGE_PointLight;

			vertex_shader_code +=
				"#version 450 core\n"
				"out vec3 Pos;\n";

			if (NORMAL)
				vertex_shader_code +=
				"out vec3 Normal;\n";

			if (TEXCOORD)
				vertex_shader_code +=
				"out vec2 TexCoord;\n";

			vertex_shader_code +=
				"layout(location = 0) in vec3 aPos;\n";

			if (NORMAL)
				vertex_shader_code +=
				"layout(location = 1) in vec3 aNormal;\n";

			if (TEXCOORD)
				vertex_shader_code +=
				"layout(location = 2) in vec2 aTexCoord;\n";


			vertex_shader_code +=
				"uniform mat4 model;\n"
				"uniform mat4 normalModel;\n"
				"uniform mat4 view;\n"
				"uniform mat4 projection;\n"

				"void main()\n"
				"{\n"
				"	Pos = vec3(view * model * vec4(aPos, 1.0f));\n";

			if (NORMAL)
				vertex_shader_code +=
				"	Normal = mat3(view) * mat3(normalModel) * aNormal;\n";

			if (TEXCOORD)
				vertex_shader_code +=
				"	TexCoord = aTexCoord;\n";

			vertex_shader_code +=
				"	gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
				"}";


			fragment_shader_code +=
				"#version 450 core\n"
				"out vec4 FragColor;\n"
				"in vec3 Pos;\n";

			if (NORMAL)
				fragment_shader_code +=
				"in vec3 Normal;\n";

			if (TEXCOORD)
				fragment_shader_code +=
				"in vec2 TexCoord;\n";

			fragment_shader_code +=
				"struct Material\n"
				"{\n";

			if (EMISSION_MAP)
				fragment_shader_code +=
				"	sampler2D emission;\n";
			else
				fragment_shader_code +=
				"	vec3 emission;\n";

			if (DIFFUSE_MAP)
				fragment_shader_code +=
				"	sampler2D diffuse;\n";
			else
				fragment_shader_code +=
				"	vec3 diffuse;\n";

			if (SPECULAR_MAP)
				fragment_shader_code +=
				"	sampler2D specular;\n";
			else
				fragment_shader_code +=
				"	vec3 specular;\n";

			fragment_shader_code +=
				"	float shininess;\n"
				"};\n"

				"struct Light\n"
				"{\n"
				"	vec3 ambient;\n"
				"	vec3 diffuse;\n"
				"	vec3 specular;\n";

			if (DIR_LIGHT)
				fragment_shader_code +=
				"	vec3 direction;\n";
			else if (POINT_LIGHT)
				fragment_shader_code +=
				"	vec3 position;\n";

			fragment_shader_code +=
				"};\n"

				"uniform vec3 viewPos;\n"
				"uniform Material material;\n"
				"uniform Light light;\n"


				"void main()\n"
				"{\n"


				"	vec3 result = vec3(0.0f, 0.0f, 0.0f);\n";


			if (TEXCOORD && EMISSION_MAP)
				fragment_shader_code +=
				"	vec3 emission = texture(material.emission, TexCoord).rgb;\n";
			else
				fragment_shader_code +=
				"	vec3 emission = material.emission;\n";
			fragment_shader_code +=
				"	result += emission;\n";



			if (TEXCOORD && DIFFUSE_MAP)
				fragment_shader_code +=
				"	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;\n";
			else
				fragment_shader_code +=
				"	vec3 ambient = light.ambient * material.diffuse;\n";
			fragment_shader_code +=
				"	result += ambient;\n";


			if (NORMAL)
			{
				fragment_shader_code +=
					"	vec3 normal = normalize(Normal);\n";


				if (DIR_LIGHT)
					fragment_shader_code +=
					"	vec3 lightDir = normalize(light.direction);\n";
				else if (POINT_LIGHT)
					fragment_shader_code +=
					"	vec3 lightDir = normalize(Pos - light.position);\n";

				fragment_shader_code +=
					"	float diff = max(dot(normal, -lightDir), 0.0f);\n";


				if (TEXCOORD && DIFFUSE_MAP)
					fragment_shader_code +=
					"	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;\n";
				else
					fragment_shader_code +=
					"	vec3 diffuse = light.diffuse * diff * material.diffuse;\n";
				fragment_shader_code +=
					"	result += diffuse;\n";

				fragment_shader_code +=
					"	vec3 viewDir = normalize(-Pos);\n"
					"	vec3 reflectDir = reflect(lightDir, normal);\n"
					"	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);\n";
				if (TEXCOORD && SPECULAR_MAP)
					fragment_shader_code +=
					"	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;\n";
				else
					fragment_shader_code +=
					"	vec3 specular = light.specular * spec * material.specular;\n";
				fragment_shader_code +=
					"	result += specular;\n";
			}

			fragment_shader_code +=
				"	FragColor = vec4(result, 1.0f);\n"
				"}";



			//创建渲染元
			SPtr(RenderingUnit) unit = RenderingUnit::Create();
			unit->SetLeaf(mesh);
			unit->SetVBO(vbo);
			unit->SetEBO(ebo);
			unit->SetVAO(vao);
			unit->SetDrawingCall(drawing_call);
			unit->SetModelMatrixs(model_matrixs_uniforms);
			unit->SetMaterials(material_uniforms);

			if (EMISSION_MAP)
			{
				auto iter = emission_maps_.find(emission_map);
				if (iter != emission_maps_.end())
					unit->SetEmissionMap(iter->second);
				else
				{
					SPtr(Texture2DSource) texture = Texture2DSource::Create(emission_map);
					emission_maps_[emission_map] = texture;
					unit->SetEmissionMap(texture);
				}
			}
			if (DIFFUSE_MAP)
			{
				auto iter = diffuse_maps_.find(diffuse_map);
				if (iter != diffuse_maps_.end())
					unit->SetDiffuseMap(iter->second);
				else
				{
					SPtr(Texture2DSource) texture = Texture2DSource::Create(diffuse_map);
					diffuse_maps_[diffuse_map] = texture;
					unit->SetDiffuseMap(texture);
				}
			}
			if (SPECULAR_MAP)
			{
				auto iter = specular_maps_.find(specular_map);
				if (iter != specular_maps_.end())
					unit->SetSpecularMap(iter->second);
				else
				{
					SPtr(Texture2DSource) texture = Texture2DSource::Create(specular_map);
					specular_maps_[specular_map] = texture;
					unit->SetSpecularMap(texture);
				}
			}
			{
				std::vector<std::string> shaders_code;
				shaders_code.reserve(2);
				shaders_code.emplace_back(vertex_shader_code);
				shaders_code.emplace_back(fragment_shader_code);
				auto iter = shaders_.find(shaders_code);
				if (iter != shaders_.end())
					unit->SetShader(iter->second);
				else
				{
					SPtr(Program) program = Program::Create();
					program->AddShader(Shader::Create(Shader::Type::VERTEX_SHADER, vertex_shader_code));
					program->AddShader(Shader::Create(Shader::Type::FRAGMENT_SHADER, fragment_shader_code));
					SPtr(ShaderSource) shader = ShaderSource::Create(program);
					shaders_[shaders_code] = shader;
					unit->SetShader(shader);
				}
			}

			//添加至状态树
			tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()][unit->GetVAO()].emplace_back(unit);
			units_[mesh] = unit;
		}break;
		case OGE_CustomState:
		{
			//...
		}break;
		}
	}


	void NodeVisitor::Process(SPtr(Cube) cube)
	{
		cube->mask_++;

		//重复mesh只修改model矩阵
		if (cube->mask_ > 1)
		{
			SPtr(RenderingUnit) unit = units_.find(cube)->second->Copy();
			SPtr(UniformList) model_matrixs_uniforms = UniformList::Create();
			model_matrixs_uniforms->AddUniform(UniformMat::Create("model", cube->transfer_));
			model_matrixs_uniforms->AddUniform(UniformMat::Create("normalModel", Matrix::Transpose(Matrix::Inverse(cube->transfer_))));
			unit->SetModelMatrixs(model_matrixs_uniforms);
			tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()][unit->GetVAO()].emplace_back(unit);
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
		SPtr(UniformList) material_uniforms = nullptr;
		SPtr(Texture2D) emission_map = nullptr;
		SPtr(Texture2D) diffuse_map = nullptr;
		SPtr(Texture2D) specular_map = nullptr;
		std::string	vertex_shader_code = "";
		std::string	fragment_shader_code = "";

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
			vbo->UpdateData(uv_array, norm_array_size);
			vao->EnableSetAttrib(2, 2, 2 * sizeof(float), norm_array_size);
		}

		ebo = EBO_UByte::Create(indices);

		vao->UnBind();

		//创建drawing call
		drawing_call = DrawingCall::Create(drawing_set);

		//创建模型矩阵uniform
		model_matrixs_uniforms = UniformList::Create();
		model_matrixs_uniforms->AddUniform(UniformMat::Create("model", cube->transfer_));
		model_matrixs_uniforms->AddUniform(UniformMat::Create("normalModel", Matrix::Transpose(Matrix::Inverse(cube->transfer_))));

		//创建材质uniform
		material_uniforms = UniformList::Create();
		if (cube->state_ == nullptr)
			cube->state_ = state_;

		switch (cube->state_->GetName())
		{
		case OGE_PhongState:
		{
			SPtr(PhongState) phong_state = SPtrCast(PhongState, cube->state_);
			SPtr(Material) material = phong_state->GetMaterial();

			//添加材质
			if (material->GetEmissionMap() != nullptr)
			{
				emission_map = material->GetEmissionMap();
				material_uniforms->AddUniform(UniformInt::Create("material.emission", 0));
			}
			else
				material_uniforms->AddUniform(UniformVec3::Create("material.emission", material->GetEmissionColor()));

			if (material->GetDiffuseMap() != nullptr)
			{
				diffuse_map = material->GetDiffuseMap();
				material_uniforms->AddUniform(UniformInt::Create("material.diffuse", 1));
			}
			else
				material_uniforms->AddUniform(UniformVec3::Create("material.diffuse", material->GetDiffuseColor()));

			if (material->GetSpecularMap() != nullptr)
			{
				specular_map = material->GetSpecularMap();
				material_uniforms->AddUniform(UniformInt::Create("material.specular", 2));
			}
			else
				material_uniforms->AddUniform(UniformVec3::Create("material.specular", material->GetSpecularColor()));

			material_uniforms->AddUniform(UniformFloat::Create("material.shininess", material->GetShininess()));

			//添加光源
			material_uniforms->AddUniform(UniformVec3::Create("light.ambient", lights_[0]->GetAmbient()));
			material_uniforms->AddUniform(UniformVec3::Create("light.diffuse", lights_[0]->GetDiffuse()));
			material_uniforms->AddUniform(UniformVec3::Create("light.specular", lights_[0]->GetSpecular()));
			ObjectName name = lights_[0]->GetName();
			switch (name)
			{
			case OGE_DirLight:
			{
				SPtr(DirLight) dir_light = SPtrCast(DirLight, lights_[0]);
				material_uniforms->AddUniform(UniformVec3::Create("light.direction", dir_light->GetDir()));
			}break;
			case OGE_PointLight:
			{
				SPtr(PointLight) point_light = SPtrCast(PointLight, lights_[0]);
				material_uniforms->AddUniform(UniformVec3::Create("light.position", point_light->GetPosition()));
			}break;
			}

			//创建shader
			bool NORMAL = norm_array_size > 0;
			bool TEXCOORD = uv_array_size > 0;
			bool EMISSION_MAP = emission_map != nullptr;
			bool DIFFUSE_MAP = diffuse_map != nullptr;
			bool SPECULAR_MAP = specular_map != nullptr;
			bool DIR_LIGHT = name == OGE_DirLight;
			bool POINT_LIGHT = name == OGE_PointLight;

			vertex_shader_code +=
				"#version 450 core\n"
				"out vec3 Pos;\n";

			if (NORMAL)
				vertex_shader_code +=
				"out vec3 Normal;\n";

			if (TEXCOORD)
				vertex_shader_code +=
				"out vec2 TexCoord;\n";

			vertex_shader_code +=
				"layout(location = 0) in vec3 aPos;\n";

			if (NORMAL)
				vertex_shader_code +=
				"layout(location = 1) in vec3 aNormal;\n";

			if (TEXCOORD)
				vertex_shader_code +=
				"layout(location = 2) in vec2 aTexCoord;\n";


			vertex_shader_code +=
				"uniform mat4 model;\n"
				"uniform mat4 normalModel;\n"
				"uniform mat4 view;\n"
				"uniform mat4 projection;\n"

				"void main()\n"
				"{\n"
				"	Pos = vec3(view * model * vec4(aPos, 1.0f));\n";

			if (NORMAL)
				vertex_shader_code +=
				"	Normal = mat3(view) * mat3(normalModel) * aNormal;\n";

			if (TEXCOORD)
				vertex_shader_code +=
				"	TexCoord = aTexCoord;\n";

			vertex_shader_code +=
				"	gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
				"}";


			fragment_shader_code +=
				"#version 450 core\n"
				"out vec4 FragColor;\n"
				"in vec3 Pos;\n";

			if (NORMAL)
				fragment_shader_code +=
				"in vec3 Normal;\n";

			if (TEXCOORD)
				fragment_shader_code +=
				"in vec2 TexCoord;\n";

			fragment_shader_code +=
				"struct Material\n"
				"{\n";

			if (EMISSION_MAP)
				fragment_shader_code +=
				"	sampler2D emission;\n";
			else
				fragment_shader_code +=
				"	vec3 emission;\n";

			if (DIFFUSE_MAP)
				fragment_shader_code +=
				"	sampler2D diffuse;\n";
			else
				fragment_shader_code +=
				"	vec3 diffuse;\n";

			if (SPECULAR_MAP)
				fragment_shader_code +=
				"	sampler2D specular;\n";
			else
				fragment_shader_code +=
				"	vec3 specular;\n";

			fragment_shader_code +=
				"	float shininess;\n"
				"};\n"

				"struct Light\n"
				"{\n"
				"	vec3 ambient;\n"
				"	vec3 diffuse;\n"
				"	vec3 specular;\n";

			if (DIR_LIGHT)
				fragment_shader_code +=
				"	vec3 direction;\n";
			else if (POINT_LIGHT)
				fragment_shader_code +=
				"	vec3 position;\n";

			fragment_shader_code +=
				"};\n"

				"uniform vec3 viewPos;\n"
				"uniform Material material;\n"
				"uniform Light light;\n"


				"void main()\n"
				"{\n"


				"	vec3 result = vec3(0.0f, 0.0f, 0.0f);\n";


			if (TEXCOORD && EMISSION_MAP)
				fragment_shader_code +=
				"	vec3 emission = texture(material.emission, TexCoord).rgb;\n";
			else
				fragment_shader_code +=
				"	vec3 emission = material.emission;\n";
			fragment_shader_code +=
				"	result += emission;\n";



			if (TEXCOORD && DIFFUSE_MAP)
				fragment_shader_code +=
				"	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;\n";
			else
				fragment_shader_code +=
				"	vec3 ambient = light.ambient * material.diffuse;\n";
			fragment_shader_code +=
				"	result += ambient;\n";


			if (NORMAL)
			{
				fragment_shader_code +=
					"	vec3 normal = normalize(Normal);\n";


				if (DIR_LIGHT)
					fragment_shader_code +=
					"	vec3 lightDir = normalize(light.direction);\n";
				else if (POINT_LIGHT)
					fragment_shader_code +=
					"	vec3 lightDir = normalize(Pos - light.position);\n";

				fragment_shader_code +=
					"	float diff = max(dot(normal, -lightDir), 0.0f);\n";


				if (TEXCOORD && DIFFUSE_MAP)
					fragment_shader_code +=
					"	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;\n";
				else
					fragment_shader_code +=
					"	vec3 diffuse = light.diffuse * diff * material.diffuse;\n";
				fragment_shader_code +=
					"	result += diffuse;\n";

				fragment_shader_code +=
					"	vec3 viewDir = normalize(-Pos);\n"
					"	vec3 reflectDir = reflect(lightDir, normal);\n"
					"	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);\n";
				if (TEXCOORD && SPECULAR_MAP)
					fragment_shader_code +=
					"	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;\n";
				else
					fragment_shader_code +=
					"	vec3 specular = light.specular * spec * material.specular;\n";
				fragment_shader_code +=
					"	result += specular;\n";
			}

			fragment_shader_code +=
				"	FragColor = vec4(result, 1.0f);\n"
				"}";



			//创建渲染元
			SPtr(RenderingUnit) unit = RenderingUnit::Create();
			unit->SetLeaf(cube);
			unit->SetVBO(vbo);
			unit->SetEBO(ebo);
			unit->SetVAO(vao);
			unit->SetDrawingCall(drawing_call);
			unit->SetModelMatrixs(model_matrixs_uniforms);
			unit->SetMaterials(material_uniforms);

			if (EMISSION_MAP)
			{
				auto iter = emission_maps_.find(emission_map);
				if (iter != emission_maps_.end())
					unit->SetEmissionMap(iter->second);
				else
				{
					SPtr(Texture2DSource) texture = Texture2DSource::Create(emission_map);
					emission_maps_[emission_map] = texture;
					unit->SetEmissionMap(texture);
				}
			}
			if (DIFFUSE_MAP)
			{
				auto iter = diffuse_maps_.find(diffuse_map);
				if (iter != diffuse_maps_.end())
					unit->SetDiffuseMap(iter->second);
				else
				{
					SPtr(Texture2DSource) texture = Texture2DSource::Create(diffuse_map);
					diffuse_maps_[diffuse_map] = texture;
					unit->SetDiffuseMap(texture);
				}
			}
			if (SPECULAR_MAP)
			{
				auto iter = specular_maps_.find(specular_map);
				if (iter != specular_maps_.end())
					unit->SetSpecularMap(iter->second);
				else
				{
					SPtr(Texture2DSource) texture = Texture2DSource::Create(specular_map);
					specular_maps_[specular_map] = texture;
					unit->SetSpecularMap(texture);
				}
			}
			{
				std::vector<std::string> shaders_code;
				shaders_code.reserve(2);
				shaders_code.emplace_back(vertex_shader_code);
				shaders_code.emplace_back(fragment_shader_code);
				auto iter = shaders_.find(shaders_code);
				if (iter != shaders_.end())
					unit->SetShader(iter->second);
				else
				{
					SPtr(Program) program = Program::Create();
					program->AddShader(Shader::Create(Shader::Type::VERTEX_SHADER, vertex_shader_code));
					program->AddShader(Shader::Create(Shader::Type::FRAGMENT_SHADER, fragment_shader_code));
					SPtr(ShaderSource) shader = ShaderSource::Create(program);
					shaders_[shaders_code] = shader;
					unit->SetShader(shader);
				}
			}

			//添加至状态树
			tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()][unit->GetVAO()].emplace_back(unit);
			units_[cube] = unit;
		}break;
		case OGE_CustomState:
		{
			//...
		}break;
		}
	}


	void NodeVisitor::Process(SPtr(Group) group)
	{
		//确保每个节点只处理一次
		if (group->mask_)
			return;
		group->mask_ = 1;

		if (group->children_.size() == 0)
			return;

		for (unsigned int i = 0; i < group->children_.size(); ++i)
		{
			SPtr(Node) child = group->children_[i];

			//传递state和矩阵
			child->transfer_ = group->transfer_;
			if (child->state_ == nullptr)
				child->state_ = group->state_;
			
			Visit(child);
		}
	}


	void NodeVisitor::Process(SPtr(Transform) transform)
	{
		//确保每个节点只处理一次
		if (transform->mask_)
			return;
		transform->mask_ = 1;

		if (transform->children_.size() == 0)
			return;

		for (unsigned int i = 0; i < transform->children_.size(); ++i)
		{
			SPtr(Node) child = transform->children_[i];

			//传递state和矩阵
			child->transfer_ = transform->transfer_ * transform->matrix_;
			if (child->state_ == nullptr)
				child->state_ = transform->state_;

			Visit(child);
		}
	}
}