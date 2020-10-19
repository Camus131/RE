#include "ShaderSource.h"


namespace OGE
{
	ShaderSource::ShaderSource(SPtr(Program) program) :
		ContextObject()
	{
		name_ = OGE_ShaderSource;
		id_ = glCreateProgram();
		CreateProgram(program);
	}


	void ShaderSource::SetUniform(SPtr(Uniform) uniform)
	{
		if (uniform == nullptr)
			return;

		//判断uniform是否存在
		std::string uniform_name = uniform->GetUniformName();
		int location = QueryLocation(uniform_name);
		if (location == -1)
			return;

		//和当前值不等时才重新设置
		SPtr(Uniform) current_uniform = nullptr;
		auto iter = uniform_map_.find(location);
		if (iter != uniform_map_.end())
			current_uniform = iter->second;
		switch (uniform->GetName())
		{
		case OGE_UniformInt:
		{
			int value = SPtrCast(UniformInt, uniform)->GetValue();
			if (current_uniform != nullptr && value == SPtrCast(UniformInt, current_uniform)->GetValue())
				return;
			glUniform1i(location, value);
		}break;
		case OGE_UniformFloat:
		{
			float value = SPtrCast(UniformFloat, uniform)->GetValue();
			if (current_uniform != nullptr && value == SPtrCast(UniformFloat, current_uniform)->GetValue())
				return;
			glUniform1f(location, value);
		}break;
		case OGE_UniformVec2:
		{
			Vec2 value = SPtrCast(UniformVec2, uniform)->GetValue();
			if (current_uniform != nullptr && value == SPtrCast(UniformVec2, current_uniform)->GetValue())
				return;
			glUniform2fv(location, 1, value.Ptr());
		}break;
		case OGE_UniformVec3:
		{
			Vec3 value = SPtrCast(UniformVec3, uniform)->GetValue();
			if (current_uniform != nullptr && value == SPtrCast(UniformVec3, current_uniform)->GetValue())
				return;
			glUniform3fv(location, 1, value.Ptr());
		}break;
		case OGE_UniformVec4:
		{
			Vec4 value = SPtrCast(UniformVec4, uniform)->GetValue();
			if (current_uniform != nullptr && value == SPtrCast(UniformVec4, current_uniform)->GetValue())
				return;
			glUniform4fv(location, 1, value.Ptr());
		}break;
		case OGE_UniformMat:
		{
			Matrix value = SPtrCast(UniformMat, uniform)->GetValue();
			if (current_uniform != nullptr && value == SPtrCast(UniformMat, current_uniform)->GetValue())
				return;
			glUniformMatrix4fv(location, 1, GL_FALSE, value.Ptr());
		}break;
		}
		uniform_map_[location] = uniform;
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