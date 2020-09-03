#pragma once

#include "ExternalObject.h"
#include "../Math/Vec3f.h"


namespace OGE
{
	class Light :public ExternalObject
	{
	public:
		//���/���û�����
		Vec3 GetAmbient() const { return ambient_; }
		void SetAmbient(const Vec3& ambient) { ambient_ = ambient; }

		//���/����������
		Vec3 GetDiffuse() const { return diffuse_; }
		void SetDiffuse(const Vec3& diffuse) { diffuse_ = diffuse; }

		//���/���þ��淴��
		Vec3 GetSpecular() const { return specular_; }
		void SetSpecular(const Vec3& specular) { specular_ = specular; }

	protected:
		Light();

	protected:
		//������
		Vec3		ambient_;

		//������
		Vec3		diffuse_;

		//���淴��
		Vec3		specular_;
	};


	class PointLight :public Light
	{
	public:
		//����ʵ��
		static SPtr(PointLight) Create()
		{
			return SPtr(PointLight)(new PointLight);
		}

		SPtr(PointLight) Copy() const;

		//���/����λ��
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
		//����ʵ��
		static SPtr(DirLight) Create()
		{
			return SPtr(DirLight)(new DirLight);
		}

		SPtr(DirLight) Copy() const;

		//���/���÷���
		Vec3 GetDir() const { return direction_; }
		void SetDir(const Vec3& direction) { direction_ = direction; }

	protected:
		DirLight();

	protected:
		Vec3		direction_;
	};
}
