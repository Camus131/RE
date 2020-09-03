#include "Uniform.h"


namespace OGE
{
	UniformFloat::UniformFloat(const std::string& uniform_name, value_type value)
	{
		name_ = "UniformFloat";
		uniform_name_ = uniform_name;
		value_ = value;
	}


	UniformInt::UniformInt(const std::string& uniform_name, value_type value)
	{
		name_ = "UniformInt";
		uniform_name_ = uniform_name;
		value_ = value;
	}


	UniformVec2::UniformVec2(const std::string& uniform_name, const value_type& value)
	{
		name_ = "UniformVec2";
		uniform_name_ = uniform_name;
		value_ = value;
	}


	UniformVec3::UniformVec3(const std::string& uniform_name, const value_type& value)
	{
		name_ = "UniformVec3";
		uniform_name_ = uniform_name;
		value_ = value;
	}


	UniformVec4::UniformVec4(const std::string& uniform_name, const value_type& value)
	{
		name_ = "UniformVec4";
		uniform_name_ = uniform_name;
		value_ = value;
	}


	UniformMat::UniformMat(const std::string& uniform_name, const value_type& value)
	{
		name_ = "UniformMat";
		uniform_name_ = uniform_name;
		value_ = value;
	}
}