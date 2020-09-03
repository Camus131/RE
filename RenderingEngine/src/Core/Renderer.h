#pragma once

#include "RenderingUnit.h"

#include "../Scene/FPSCamera.h"


namespace OGE
{
	class Renderer :public Object
	{
	public:
		//����ʵ��
		static SPtr(Renderer) Create()
		{
			return SPtr(Renderer)(new Renderer);
		}

		//����/������
		void SetCamera(SPtr(FPSCamera) camera) { camera_ = camera; }
		SPtr(FPSCamera) GetCamera() const { return camera_; }

		//���ó�����
		void SetScene(const std::vector<SPtr(Mesh)>& meshes);

		//��Ⱦһ֡
		void Frame();

		//���/�����ӿ�
		int GetWidth() const { return width_; }
		void SetWidth(int width) { width_ = width; }
		int GetHeight() const { return height_; }
		void SetHeight(int height) { height_ = height; }
		void SetViewPort() const { glViewport(0, 0, width_, height_); }

	protected:
		Renderer();

		//������Ⱦ��
		void Update();

	protected:
		//���
		SPtr(FPSCamera)						camera_;

		//�ӿ�
		int									width_;
		int									height_;

		//���¿���
		bool								update_switch_;

		//������
		std::vector<SPtr(Mesh)>				meshes_;

		std::vector<SPtr(RenderingUnit)>	rendering_units_;

		typedef std::map<SPtr(ShaderSource), std::map<SPtr(Texture2DSource), std::map<SPtr(Texture2DSource), std::map<SPtr(Texture2DSource), std::vector<SPtr(RenderingUnit)>>>>> RenderTree;
		//��Ⱦ��
		RenderTree render_tree_;
	};
}