#include "Shader.h"

#include <fstream>
#include <sstream>


namespace OGE
{
	Shader::Shader(Type type, const std::string& code, StrType str_type) :
		Interviewee(),
		type_(type)
	{
		name_ = OGE_Shader;
		SetCode(code, str_type);
	}


	void Shader::SetCode(const std::string& code, StrType str_type)
	{
		if (str_type == CODE)
			code_ = code;
		else
			ReadShaderFile(code);
	}


	void Shader::ReadShaderFile(const std::string& filepath)
	{
		//文件流，设置可以捕获异常
		std::ifstream shader_file;
		std::stringstream shader_stream;
		shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			shader_file.open(filepath);
			shader_stream << shader_file.rdbuf();
			shader_file.close();
			code_ = shader_stream.str();
		}
		catch (std::ifstream::failure&)
		{
			switch (type_)
			{
			case VERTEX_SHADER:
				std::cout << "顶点着色器文件读取失败！" << std::endl;
				break;
			case FRAGMENT_SHADER:
				std::cout << "片元着色器文件读取失败！" << std::endl;
				break;
			case GEOMETRY_SHADER:
				std::cout << "几何着色器文件读取失败！" << std::endl;
				break;
			}
		}
	}
}