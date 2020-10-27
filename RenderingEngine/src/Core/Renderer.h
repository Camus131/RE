#pragma once

#include "PerspectiveCamera.h"
#include "NodeVisitor.h"

#include "Object/Viewport.h"
#include "Object/Group.h"
#include "Object/Light.h"


namespace OGE
{
	class Renderer :public BaseObject
	{
	public:
		//����ʵ��
		static SPtr(Renderer) Create()
		{
			return SPtr(Renderer)(new Renderer);
		}

		//����/������
		SPtr(PerspectiveCamera) GetCamera() const { return camera_; }
		void SetCamera(SPtr(PerspectiveCamera) camera) { camera_ = camera; }

		//���/���ó���
		SPtr(Group) GetScene() const { return bvh_tree_; }
		void SetScene(SPtr(Group) tree) { bvh_tree_ = tree; }

		//���/�����ӿ�
		SPtr(Viewport) GetViewport() const { return viewport_; }
		void SetViewport(SPtr(Viewport) viewport) { viewport_ = viewport; }
		void UpdateViewport() { glViewport(viewport_->GetX(), viewport_->GetY(), viewport_->GetWidth(), viewport_->GetHeight()); }

		//���/���ù�Դ
		std::vector<SPtr(Light)> GetLights() const { return lights_; }
		void SetLights(const std::vector<SPtr(Light)>& lights) { lights_ = lights; }

		//��Ⱦһ֡
		void Frame();

	protected:
		Renderer() :
			BaseObject(),
			first_frame_(true),
			fps_(0.0)
		{
			name_ = OGE_Renderer;
		}

		//��ʼ��
		void Init();

	protected:
		bool								first_frame_;

		SPtr(PerspectiveCamera)				camera_;

		SPtr(Group)							bvh_tree_;

		SPtr(Viewport)						viewport_;

		std::vector<SPtr(Light)>		    lights_;

		NodeVisitor::StateTree				state_tree_;

		std::vector<SPtr(RenderingUnit)>	transparent_state_tree_;

		SPtr(UniformList)					lights_uniforms_;

		//֡��
		double								fps_;
	};
}