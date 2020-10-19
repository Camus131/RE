#include "Material.h"


namespace OGE
{
	SPtr(Material) Material::Copy() const
	{
		SPtr(Material) material = SPtr(Material)(new Material);
		material->diffuse_color_ = diffuse_color_;
		material->diffuse_map_ = diffuse_map_;
		material->specular_color_ = specular_color_;
		material->specular_map_ = specular_map_;
		material->shininess_ = shininess_;
		material->emission_color_ = emission_color_;
		material->emission_map_ = emission_map_;
		return material;
	}
}