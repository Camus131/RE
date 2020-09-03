#include "ShaderSource.h"

#include <iostream>


namespace OGE
{
	ShaderSource::ShaderSource(SPtr(Program) program) :
		ContextObject()
	{
		name_ = "ShaderSource";
		id_ = glCreateProgram();
		CreateProgram(program);
	}


	void ShaderSource::SetUniform(SPtr(Uniform) uniform)
	{
		if (uniform == nullptr)
			return;

		std::string uniform_name = uniform->GetUniformName();
		int location = QueryLocation(uniform_name);
		if (location == -1)
			return;

		std::string name = uniform->GetName();
		if (name == "UniformInt")
		{
			int value = SPCast(UniformInt)(uniform)->GetValue();
			//if (value == SPCast(UniformInt)(QueryUniform(location, uniform))->GetValue())
			//	return;
			glUniform1i(location, value);
		}
		else if (name == "UniformFloat")
		{
			float value = SPCast(UniformFloat)(uniform)->GetValue();
			//if (value == SPCast(UniformFloat)(QueryUniform(location, uniform))->GetValue())
			//	return;
			glUniform1f(location, value);
		}
		else if (name == "UniformVec2")
		{
			Vec2 value = SPCast(UniformVec2)(uniform)->GetValue();
			//if (value == SPCast(UniformVec2)(QueryUniform(location, uniform))->GetValue())
			//	return;
			glUniform2fv(location, 1, value.Ptr());
		}
		else if (name == "UniformVec3")
		{
			Vec3 value = SPCast(UniformVec3)(uniform)->GetValue();
			//if (value == SPCast(UniformVec3)(QueryUniform(location, uniform))->GetValue())
			//	return;
			glUniform3fv(location, 1, value.Ptr());
		}
		else if (name == "UniformVec4")
		{
			Vec4 value = SPCast(UniformVec4)(uniform)->GetValue();
			//if (value == SPCast(UniformVec4)(QueryUniform(location, uniform))->GetValue())
			//	return;
			glUniform4fv(location, 1, value.Ptr());
		}
		else if (name == "UniformMat")
		{
			Matrix value = SPCast(UniformMat)(uniform)->GetValue();
			//if (value == SPCast(UniformMat)(QueryUniform(location, uniform))->GetValue())
			//	return;
			glUniformMatrix4fv(location, 1, GL_FALSE, value.Ptr());
		}
	}


	int ShaderSource::QueryLocation(const std::string& name)
	{
		//查找本地map中是否存在，存在则直接返回
		auto iter = location_map_.find(name);
		if (iter != location_map_.end())
			return iter->second;

		//不存在则将结果添加至本地map
		int location = glGetUniformLocation(id_, name.c_str());
		if (location != -1)
			location_map_[name] = location;

		return location;
	}


	SPtr(Uniform) ShaderSource::QueryUniform(int location, SPtr(Uniform) uniform)
	{
		auto iter = uniform_map_.find(location);
		if (iter != uniform_map_.end())
			return iter->second;

		uniform_map_[location] = uniform;
		return uniform;
	}


	void ShaderSource::CreateProgram(SPtr(Program) program)
	{
		if (program == nullptr ||
			program->GetShader(Shader::Type::VERTEX_SHADER) == nullptr ||
			program->GetShader(Shader::Type::FRAGMENT_SHADER) == nullptr)
			return;

		program_ = program;

		unsigned int vs = 0, fs = 0, gs = 0;

		CreateShader(program_->GetShader(Shader::Type::VERTEX_SHADER), vs);
		CreateShader(program_->GetShader(Shader::Type::FRAGMENT_SHADER), fs);
		if(program_->GetShader(Shader::Type::GEOMETRY_SHADER)!=nullptr)
			CreateShader(program_->GetShader(Shader::Type::GEOMETRY_SHADER), gs);

		glAttachShader(id_, vs);
		glAttachShader(id_, fs);
		if (gs > 0)
			glAttachShader(id_, gs);
		glLinkProgram(id_);
		
		int success = 0;
		char info_log[512];
		glGetProgramiv(id_, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id_, 512, nullptr, info_log);
			std::cout << "着色程序链接失败！\n" << info_log << std::endl;
		}

		glDeleteShader(vs);
		glDeleteShader(fs);
		if (gs > 0)
			glDeleteShader(gs);
	}



	void ShaderSource::CreateShader(SPtr(Shader) shader, unsigned int& id)
	{
		Shader::Type type = shader->GetType();
		std::string shader_code = shader->GetCode();
		const char* code = shader_code.c_str();

		int success = 0;
		char info_log[512];

		id = glCreateShader(type);
		glShaderSource(id, 1, &code, nullptr);
		glCompileShader(id);
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 512, nullptr, info_log);
			switch (type)
			{
			case Shader::Type::VERTEX_SHADER:
				std::cout << "顶点着色器编译失败！" << std::endl;
				break;
			case Shader::Type::FRAGMENT_SHADER:
				std::cout << "片元着色器编译失败！" << std::endl;
				break;
			case Shader::Type::GEOMETRY_SHADER:
				std::cout << "几何着色器编译失败！" << std::endl;
				break;
			}
		}
	}
}