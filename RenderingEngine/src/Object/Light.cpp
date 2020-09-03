#include "Light.h"


namespace OGE
{
	Light::Light() :
		ExternalObject(),
		ambient_(Vec3(0.2f, 0.2f, 0.2f)),
		diffuse_(Vec3(0.8f, 0.8f, 0.8f)),
		specular_(Vec3(0.8f, 0.8f, 0.8f))
	{
	}


	PointLight::PointLight() :
		Light()
	{
		name_ = "PointLight";
	}


	SPtr(PointLight) PointLight::Copy() const
	{
		SPtr(PointLight) light = SPtr(PointLight)(new PointLight);
		light->ambient_ = ambient_;
		light->diffuse_ = diffuse_;
		light->specular_ = specular_;
		light->position_ = position_;
		return light;
	}


	DirLight::DirLight() :
		Light()
	{
		name_ = "DirLight";
		direction_ = Vec3(0.0f, 0.0f, -1.0f);
	}


	SPtr(DirLight) DirLight::Copy() const
	{
		SPtr(DirLight) light = SPtr(DirLight)(new DirLight);
		light->ambient_ = ambient_;
		light->diffuse_ = diffuse_;
		light->specular_ = specular_;
		light->direction_ = direction_;
		return light;
	}
}