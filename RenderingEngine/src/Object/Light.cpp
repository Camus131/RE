#include "Light.h"


namespace OGE
{
	SPtr(PointLight) PointLight::Copy() const
	{
		SPtr(PointLight) light = SPtr(PointLight)(new PointLight);
		light->ambient_ = ambient_;
		light->diffuse_ = diffuse_;
		light->specular_ = specular_;
		light->position_ = position_;
		return light;
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