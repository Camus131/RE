#pragma once

#include "Texture2D.h"

#include "Math/Vec3f.h"


namespace OGE
{
	class Material :public Interviewee
	{
	public:
		//����ʵ��
		static SPtr(Material) Create()
		{
			return SPtr(Material)(new Material);
		}

		SPtr(Material) Copy() const;

		//���/�������������
		Vec3 GetDiffuseColor() const { return diffuse_color_; }
		void SetDiffuseColor(const Vec3& color) { diffuse_color_ = color; }
		SPtr(Texture2D) GetDiffuseMap() const { return diffuse_map_; }
		void SetDiffuseMap(SPtr(Texture2D) map) { diffuse_map_ = map; }

		//���/���þ��淴�����
		Vec3 GetSpecularColor() const { return specular_color_; }
		void SetSpecularColor(const Vec3& color) { specular_color_ = color; }
		SPtr(Texture2D) GetSpecularMap() const { return specular_map_; }
		void SetSpecularMap(SPtr(Texture2D) map) { specular_map_ = map; }
		float GetShininess() const { return shininess_; }
		void SetShininess(float shininess) { shininess_ = shininess; }

		//���/�������������
		Vec3 GetEmissionColor() const { return emission_color_; }
		void SetEmissionColor(const Vec3& color) { emission_color_ = color; }
		SPtr(Texture2D) GetEmissionMap() const { return emission_map_; }
		void SetEmissionMap(SPtr(Texture2D) map) { emission_map_ = map; }

	protected:
		Material() :
			Interviewee(),
			diffuse_color_(Vec3(0.8f, 0.8f, 0.8f)),
			specular_color_(Vec3(0.0f, 0.0f, 0.0f)),
			shininess_(1.0f),
			emission_color_(Vec3(0.0f, 0.0f, 0.0f))
		{
			name_ = OGE_Material;
		}

	protected:
		//���������
		Vec3				diffuse_color_;
		SPtr(Texture2D)		diffuse_map_;

		//���淴�����
		Vec3				specular_color_;
		SPtr(Texture2D)		specular_map_;
		float				shininess_;

		//�������
		Vec3				emission_color_;
		SPtr(Texture2D)		emission_map_;
	};
}
