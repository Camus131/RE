#include "Renderer.h"


namespace OGE
{
	void Renderer::Frame()
	{
		if (first_frame_)
		{
			Init();
			first_frame_ = false;
		}

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
								SPtr(UniformList) model_matrixs = unit->GetModelMatrixs();
								for (int num = 0; num < model_matrixs->GetUniformNum(); ++num)
									shader->SetUniform(model_matrixs->GetUniform(num));
								SPtr(UniformList) materials = unit->GetMaterials();
								for (int num = 0; num < materials->GetUniformNum(); ++num)
									shader->SetUniform(materials->GetUniform(num));
								unit->GetDrawingCall()->Draw();
							}
						}
					}
				}
			}
		}
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
			Vec3 eye(corner.x() + (box.xmax() - box.xmin()) * 0.5f, 0.5f, corner.z() + 0.5f);
			Vec3 target(eye.x(), eye.y(), eye.z() - 1.0f);
			Vec3 up = Y_AXIS;
			camera_ = PerspectiveCamera::Create(eye, target, up, 45.0f, viewport_->AspectRatio(), 0.1f, 1000.0f);
		}

		if (lights_.empty())
			lights_.emplace_back(DirLight::Create());

		SPtr(NodeVisitor) visitor = NodeVisitor::Create(lights_);
		bvh_tree_->Accept(visitor);

		state_tree_ = visitor->GetTree();
		transparent_state_tree_ = visitor->GetTransparentTree();

		glEnable(GL_DEPTH_TEST);
	}
}