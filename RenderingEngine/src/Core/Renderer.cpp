#include "Renderer.h"

#include <windows.h>
#include <ctime>


namespace OGE
{
	void Renderer::Frame()
	{
		if (first_frame_)
		{
			Init();
			first_frame_ = false;
		}

		//记时
		clock_t start_time = clock();

		glClearColor(0.2f, 0.8f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SPtr(UniformMat) view = UniformMat::Create("view", camera_->ViewMatrix());
		SPtr(UniformMat) projection = UniformMat::Create("projection", camera_->ProjectionMatrix());

		for (auto iter_shader = state_tree_.begin(); iter_shader != state_tree_.end(); ++iter_shader)
		{
			SPtr(ShaderSource) shader = iter_shader->first;
			shader->Bind();
			shader->SetUniform(projection);
			shader->SetUniform(view);
			shader->SetUniforms(lights_uniforms_);
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
						for (auto iter_vao = iter_t2->second.begin(); iter_vao != iter_t2->second.end(); ++iter_vao)
						{
							SPtr(VAO) vao = iter_vao->first;
							vao->Bind();
							for (int i = 0; i < iter_vao->second.size(); ++i)
							{
								SPtr(RenderingUnit) unit = (iter_vao->second)[i];
								shader->SetUniforms(unit->GetModelMatrixs());
								shader->SetUniforms(unit->GetMaterials());
								unit->GetDrawingCall()->Draw();
							}
						}
					}
				}
			}
		}

		if (!transparent_state_tree_.empty())
		{
			glDepthMask(GL_FALSE);
			std::map<float, std::vector<SPtr(RenderingUnit)>> transparent_map;
			for (int i = 0; i < transparent_state_tree_.size(); ++i)
			{
				Matrix  model_matrix = SPtrCast(UniformMat, transparent_state_tree_[i]->GetModelMatrixs()->GetUniform("model"))->GetValue();
				Vec3 center = transparent_state_tree_[i]->GetLeaf()->GetBoundingBox().Center();
				center = camera_->ViewMatrix() * model_matrix * center;
				transparent_map[center.z()].emplace_back(transparent_state_tree_[i]);
			}
			for (auto iter = transparent_map.begin(); iter != transparent_map.end(); ++iter)
			{
				float t = iter->first;
				for (int i = 0; i < iter->second.size(); ++i)
				{
					SPtr(RenderingUnit) unit = iter->second[i];
					SPtr(ShaderSource) shader = unit->GetShader();
					shader->Bind();
					shader->SetUniform(projection);
					shader->SetUniform(view);
					shader->SetUniforms(lights_uniforms_);
					SPtr(Texture2DSource) texture0 = unit->GetEmissionMap();
					if (texture0 != nullptr)
						texture0->Bind();
					SPtr(Texture2DSource) texture1 = unit->GetDiffuseMap();
					if (texture1 != nullptr)
						texture1->Bind(1);
					SPtr(Texture2DSource) texture2 = unit->GetSpecularMap();
					if (texture2 != nullptr)
						texture2->Bind(2);
					unit->GetVAO()->Bind();
					shader->SetUniforms(unit->GetModelMatrixs());
					shader->SetUniforms(unit->GetMaterials());
					unit->GetDrawingCall()->Draw();
				}
			}
			glDepthMask(GL_TRUE);
		}

		//记录帧率
		clock_t end_time = clock();
		double frame_time = static_cast<double>(end_time - start_time);
		double sleep_time = 50.0 / 3.0 - frame_time;
		if (sleep_time > 0.0)
		{
			Sleep(sleep_time);
			frame_time += sleep_time;
		}
		fps_ = 1000.0 / frame_time;
		std::cout << fps_ << std::endl;
	}


	void Renderer::Init()
	{
		if (bvh_tree_ == nullptr)
			return;

		if (viewport_ == nullptr)
			viewport_ = Viewport::Create();

		if (camera_ == nullptr)
		{
			BoundingBox box = bvh_tree_->GetBoundingBox();
			Vec3 corner = box.Corner(4);
			Vec3 eye(corner.x() + (box.xmax() - box.xmin()) * 0.5f, corner.y() + (box.ymax() - box.ymin()) * 0.5f, corner.z() + (box.zmax() - box.zmin()) * 0.5f);
			Vec3 target(eye.x(), eye.y(), eye.z() - 1.0f);
			Vec3 up = Y_AXIS;
			camera_ = PerspectiveCamera::Create(eye, target, up, 45.0f, viewport_->AspectRatio(), 0.1f, 1000.0f);
			camera_->SetMovingSpeed(5.0f);
		}

		if (lights_.empty())
			lights_.emplace_back(DirLight::Create());

		//添加光源
		lights_uniforms_ = UniformList::Create();
		ObjectName name = lights_[0]->GetName();
		switch (name)
		{
		case OGE_DirLight:
		{
			SPtr(DirLight) dir_light = SPtrCast(DirLight, lights_[0]);
			lights_uniforms_->AddUniform(UniformVec3::Create("dirLight.ambient", dir_light->GetAmbient()));
			lights_uniforms_->AddUniform(UniformVec3::Create("dirLight.diffuse", dir_light->GetDiffuse()));
			lights_uniforms_->AddUniform(UniformVec3::Create("dirLight.specular", dir_light->GetSpecular()));
			lights_uniforms_->AddUniform(UniformVec3::Create("dirLight.direction", dir_light->GetDir()));
		}break;
		case OGE_PointLight:
		{

		}break;
		}

		SPtr(NodeVisitor) visitor = NodeVisitor::Create(lights_);
		bvh_tree_->Accept(visitor);

		state_tree_ = visitor->GetTree();
		transparent_state_tree_ = visitor->GetTransparentTree();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}