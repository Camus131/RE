#pragma once

#include "RenderingUnit.h"

#include "../Scene/FPSCamera.h"


namespace OGE
{
	class Renderer :public Object
	{
	public:
		//创建实例
		static SPtr(Renderer) Create()
		{
			return SPtr(Renderer)(new Renderer);
		}

		//设置/获得相机
		void SetCamera(SPtr(FPSCamera) camera) { camera_ = camera; }
		SPtr(FPSCamera) GetCamera() const { return camera_; }

		//设置场景树
		void SetScene(const std::vector<SPtr(Mesh)>& meshes);

		//渲染一帧
		void Frame();

		//获得/设置视口
		int GetWidth() const { return width_; }
		void SetWidth(int width) { width_ = width; }
		int GetHeight() const { return height_; }
		void SetHeight(int height) { height_ = height; }
		void SetViewPort() const { glViewport(0, 0, width_, height_); }

	protected:
		Renderer();

		//更新渲染树
		void Update();

	protected:
		//相机
		SPtr(FPSCamera)						camera_;

		//视口
		int									width_;
		int									height_;

		//更新开关
		bool								update_switch_;

		//场景树
		std::vector<SPtr(Mesh)>				meshes_;

		std::vector<SPtr(RenderingUnit)>	rendering_units_;

		typedef std::map<SPtr(ShaderSource), std::map<SPtr(Texture2DSource), std::map<SPtr(Texture2DSource), std::map<SPtr(Texture2DSource), std::vector<SPtr(RenderingUnit)>>>>> RenderTree;
		//渲染树
		RenderTree render_tree_;
	};
}