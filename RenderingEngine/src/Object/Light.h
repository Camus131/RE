#pragma once

#include "ExternalObject.h"
#include "../Math/Vec3f.h"


namespace OGE
{
	class Light :public ExternalObject
	{
	public:
		//获得/设置环境光
		Vec3 GetAmbient() const { return ambient_; }
		void SetAmbient(const Vec3& ambient) { ambient_ = ambient; }

		//获得/设置漫反射
		Vec3 GetDiffuse() const { return diffuse_; }
		void SetDiffuse(const Vec3& diffuse) { diffuse_ = diffuse; }

		//获得/设置镜面反射
		Vec3 GetSpecular() const { return specular_; }
		void SetSpecular(const Vec3& specular) { specular_ = specular; }

	protected:
		Light();

	protected:
		//环境光
		Vec3		ambient_;

		//漫反射
		Vec3		diffuse_;

		//镜面反射
		Vec3		specular_;
	};


	class PointLight :public Light
	{
	public:
		//创建实例
		static SPtr(PointLight) Create()
		{
			return SPtr(PointLight)(new PointLight);
		}

		SPtr(PointLight) Copy() const;

		//获得/设置位置
		Vec3 GetPosition() const { return position_; }
		void SetPosition(const Vec3& position) { position_ = position; }

	protected:
		PointLight();

	protected:
		Vec3		position_;
	};


	class DirLight :public Light
	{
	public:
		//创建实例
		static SPtr(DirLight) Create()
		{
			return SPtr(DirLight)(new DirLight);
		}

		SPtr(DirLight) Copy() const;

		//获得/设置方向
		Vec3 GetDir() const { return direction_; }
		void SetDir(const Vec3& direction) { direction_ = direction; }

	protected:
		DirLight();

	protected:
		Vec3		direction_;
	};
}
