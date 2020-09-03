#include "Renderer.h"
#include "MeshVisitor.h"


namespace OGE
{
	Renderer::Renderer() :
		Object()
	{
		name_ = "Renderer";
		update_switch_ = false;
		width_ = 1920;
		height_ = 1080;
		camera_ = SPtr(FPSCamera)(new FPSCamera(Vec3(0.0f, 0.5f, 4.0f), Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, 1.0f, 0.0f)));
	}


	void Renderer::SetScene(const std::vector<SPtr(Mesh)>& meshes)
	{
		int num = 0;
		for (int i = 0; i < meshes.size(); ++i)
		{
			if (meshes[i]->SizeOfPosArray() > 0)
				++num;
		}
		meshes_.reserve(num);
		for (int i = 0; i < meshes.size(); ++i)
		{
			if (meshes[i]->SizeOfPosArray() > 0)
				meshes_.emplace_back(meshes[i]);
		}
		update_switch_ = true;
	}


	void Renderer::Frame()
	{
		if (update_switch_)
			Update();

		glClearColor(0.2f, 0.8f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SPtr(UniformMat) view = UniformMat::Create("view", camera_->ViewMatrix());
		SPtr(UniformMat) projection = UniformMat::Create("projection", Matrix::Perspective(camera_->GetFov(), (float)width_ / (float)height_, 0.1f, 100.0f));

		for (auto iter_shader = render_tree_.begin(); iter_shader != render_tree_.end(); ++iter_shader)
		{
			SPtr(ShaderSource) shader = iter_shader->first;
			shader->Bind();
			shader->SetUniform(projection);
			shader->SetUniform(view);
			for (auto iter_t0 = iter_shader->second.begin(); iter_t0 != iter_shader->second.end(); ++iter_t0)
			{
				SPtr(Texture2DSource) texture0 = iter_t0->first;
				if (texture0 != nullptr)
					texture0->Bind();
				for (auto iter_t1 = iter_t0->second.begin(); iter_t1 != iter_t0->second.end(); ++iter_t1)
				{
					SPtr(Texture2DSource) texture1 = iter_t1->first;
					if (texture1 != nullptr)
						texture1->Bind(1);
					for (auto iter_t2 = iter_t1->second.begin(); iter_t2 != iter_t1->second.end(); ++iter_t2)
					{
						SPtr(Texture2DSource) texture2 = iter_t2->first;
						if (texture2 != nullptr)
							texture2->Bind(2);
						for (int i = 0; i < iter_t2->second.size(); ++i)
						{
							SPtr(RenderingUnit) unit = (iter_t2->second)[i];
							SPtr(UniformList) uniform_list = unit->GetUniformList();
							unit->GetVAO()->Bind();
							for (int num = 0; num < uniform_list->GetUniformNum(); ++num)
								shader->SetUniform(uniform_list->GetUniform(num));
							unit->GetDrawingCall()->Draw();
						}
					}
				}
			}
		}

	}


	void Renderer::Update()
	{
		std::map<std::vector<std::string>, std::vector<int>> shader_code_map;
		std::map<SPtr(Texture2D), std::vector<int>> emission_map;
		std::map<SPtr(Texture2D), std::vector<int>> diffuse_map;
		std::map<SPtr(Texture2D), std::vector<int>> specular_map;

		rendering_units_.reserve(meshes_.size());

		SPtr(MeshVisitor) mesh_visitor = MeshVisitor::Create();
		SPtr(PhongState) state = PhongState::Create();
		SPtr(Material) material = Material::Create();
		SPtr(DirLight) dirlight = DirLight::Create();
		state->SetMaterial(material);
		state->SetLight(dirlight);

		for (int i = 0; i < meshes_.size(); ++i)
		{
			SPtr(Mesh) temp_mesh = meshes_[i];

			if (temp_mesh->GetState() == nullptr)
				temp_mesh->SetState(state);

			if (temp_mesh->GetState()->GetName() == "PhongState")
			{
				SPtr(PhongState) phong_state = SPCast(PhongState)(temp_mesh->GetState());
				if (phong_state->GetMaterial() == nullptr)
					phong_state->SetMaterial(material);
				if (phong_state->GetLight() == nullptr)
					phong_state->SetLight(dirlight);
			}

			temp_mesh->Accept(mesh_visitor);

			SPtr(RenderingUnit) unit = RenderingUnit::Create();
			unit->SetMesh(temp_mesh);
			unit->SetVBO(mesh_visitor->GetVBO());
			unit->SetEBO(mesh_visitor->GetEBO());
			unit->SetVAO(mesh_visitor->GetVAO());
			unit->SetDrawingCall(mesh_visitor->GetDrawingCall());
			unit->SetUniformList(mesh_visitor->GetUniformList());
			if (mesh_visitor->GetEmissionMap() != nullptr)
			{
				SPtr(Texture2D) map = mesh_visitor->GetEmissionMap();
				if (emission_map.find(map) == emission_map.end())
					emission_map[map].emplace_back(i);
			}
			if (mesh_visitor->GetDiffuseMap() != nullptr)
			{
				SPtr(Texture2D) map = mesh_visitor->GetDiffuseMap();
				if (diffuse_map.find(map) == diffuse_map.end())
					diffuse_map[map].emplace_back(i);
			}
			if (mesh_visitor->GetSpecularMap() != nullptr)
			{
				SPtr(Texture2D) map = mesh_visitor->GetSpecularMap();
				if (specular_map.find(map) == specular_map.end())
					specular_map[map].emplace_back(i);
			}
			std::vector<std::string> temp;
			temp.reserve(2);
			temp.emplace_back(mesh_visitor->GetVertexShaderCode());
			temp.emplace_back(mesh_visitor->GetFragmentShaderCode());
			if (shader_code_map.find(temp) == shader_code_map.end())
				shader_code_map[temp].emplace_back(i);
			rendering_units_.emplace_back(unit);
		}

		for (auto iter = shader_code_map.begin(); iter != shader_code_map.end(); ++iter)
		{
			std::string vs_code = (iter->first)[0];
			std::string fs_code = (iter->first)[1];
			SPtr(Program) program = Program::Create();
			program->AddShader(Shader::Create(Shader::Type::VERTEX_SHADER, vs_code));
			program->AddShader(Shader::Create(Shader::Type::FRAGMENT_SHADER, fs_code));
			SPtr(ShaderSource) sp = ShaderSource::Create(program);
			for (int i = 0; i < iter->second.size(); ++i)
			{
				int id = (iter->second)[i];
				rendering_units_[id]->SetShader(sp);
			}
		}

		for (auto iter = emission_map.begin(); iter != emission_map.end(); ++iter)
		{
			SPtr(Texture2D) map = iter->first;
			SPtr(Texture2DSource) texture = Texture2DSource::Create(map);
			for (int i = 0; i < iter->second.size(); ++i)
			{
				int id = (iter->second)[i];
				rendering_units_[id]->SetEmissionMap(texture);
			}
		}

		for (auto iter = diffuse_map.begin(); iter != diffuse_map.end(); ++iter)
		{
			SPtr(Texture2D) map = iter->first;
			SPtr(Texture2DSource) texture = Texture2DSource::Create(map);
			for (int i = 0; i < iter->second.size(); ++i)
			{
				int id = (iter->second)[i];
				rendering_units_[id]->SetDiffuseMap(texture);
			}
		}

		for (auto iter = specular_map.begin(); iter != specular_map.end(); ++iter)
		{
			SPtr(Texture2D) map = iter->first;
			SPtr(Texture2DSource) texture = Texture2DSource::Create(map);
			for (int i = 0; i < iter->second.size(); ++i)
			{
				int id = (iter->second)[i];
				rendering_units_[id]->SetSpecularMap(texture);
			}
		}

		for (int i = 0; i < rendering_units_.size(); ++i)
		{
			SPtr(RenderingUnit) unit = rendering_units_[i];
			render_tree_[unit->GetShader()][unit->GetEmissionMap()][unit->GetDiffuseMap()][unit->GetSpecularMap()].emplace_back(unit);
		}

		glEnable(GL_DEPTH_TEST);
		update_switch_ = false;
	}
}