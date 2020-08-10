#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>


namespace OGE
{
	Shader::Shader(const std::string& vs, const std::string& fs, Type type) :
		GLObject()
	{
		unsigned int vs_id = 0, fs_id = 0;

		switch (type)
		{
		case CODE_READ:
		{
			//����������shader
			CreateAndCheckShader(vs_id, vs.c_str(), 0);
			CreateAndCheckShader(fs_id, fs.c_str(), 1);
		}break;
		case FILE_READ:
		{
			//shader����
			std::string vs_code, fs_code;
			ReadAndCheckShaderFile(vs, vs_code, 0);
			ReadAndCheckShaderFile(fs, fs_code, 1);

			//����������shader
			CreateAndCheckShader(vs_id, vs_code.c_str(), 0);
			CreateAndCheckShader(fs_id, fs_code.c_str(), 1);
		}break;
		}

		//����������program
		id_ = glCreateProgram();
		glAttachShader(id_, vs_id);
		glAttachShader(id_, fs_id);
		glLinkProgram(id_);
		CheckProgram();

		//ɾ��shader
		glDeleteShader(vs_id);
		glDeleteShader(fs_id);
	}


	Shader::Shader(const std::string& vs, const std::string& fs, const std::string& gs, Type type) :
		GLObject()
	{
		unsigned int vs_id = 0, fs_id = 0, gs_id = 0;

		switch (type)
		{
		case CODE_READ:
		{
			//����������shader
			CreateAndCheckShader(vs_id, vs.c_str(), 0);
			CreateAndCheckShader(fs_id, fs.c_str(), 1);
			CreateAndCheckShader(gs_id, gs.c_str(), 2);
		}break;
		case FILE_READ:
		{
			//shader����
			std::string vs_code, fs_code, gs_code;
			ReadAndCheckShaderFile(vs, vs_code, 0);
			ReadAndCheckShaderFile(fs, fs_code, 1);
			ReadAndCheckShaderFile(gs, gs_code, 2);

			//����������shader
			CreateAndCheckShader(vs_id, vs_code.c_str(), 0);
			CreateAndCheckShader(fs_id, fs_code.c_str(), 1);
			CreateAndCheckShader(gs_id, gs_code.c_str(), 2);
		}break;
		}

		//����������program
		id_ = glCreateProgram();
		glAttachShader(id_, vs_id);
		glAttachShader(id_, fs_id);
		glAttachShader(id_, gs_id);
		glLinkProgram(id_);
		CheckProgram();

		//ɾ��shader
		glDeleteShader(vs_id);
		glDeleteShader(fs_id);
		glDeleteShader(gs_id);
	}


	void Shader::SetUniform(const std::string& name, float value)
	{
		glUniform1f(QueryLocation(name), value);
	}


	void Shader::SetUniform(const std::string& name, int value)
	{
		glUniform1i(QueryLocation(name), value);
	}


	void Shader::SetUniform(const std::string& name, const Vec2f& value)
	{
		glUniform2fv(QueryLocation(name), 1, value.Ptr());
	}


	void Shader::SetUniform(const std::string& name, const Vec3f& value)
	{
		glUniform3fv(QueryLocation(name), 1, value.Ptr());
	}


	void Shader::SetUniform(const std::string& name, const Vec4f& value)
	{
		glUniform4fv(QueryLocation(name), 1, value.Ptr());
	}


	void Shader::SetUniform(const std::string& name, const Matrixf& value)
	{
		glUniformMatrix4fv(QueryLocation(name), 1, GL_FALSE, value.Ptr());
	}


	int Shader::QueryLocation(const std::string& name)
	{
		//���ұ���map���Ƿ���ڣ�������ֱ�ӷ��أ���ʡOpenGL API���ÿ���
		auto iter = location_map_.find(name);
		if (iter != location_map_.end())
			return iter->second;

		//�������򽫽�����������map
		int location = glGetUniformLocation(id_, name.c_str());
		if (location != -1)
			location_map_[name] = location;

		return location;
	}


	void Shader::ReadAndCheckShaderFile(const std::string& filepath, std::string& code, int type)
	{
		//�ļ��������ÿ��Բ����쳣
		std::ifstream shader_file;
		std::stringstream shader_stream;
		shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			shader_file.open(filepath);
			shader_stream << shader_file.rdbuf();
			shader_file.close();
			code = shader_stream.str();
		}
		catch (std::ifstream::failure&)
		{
			switch (type)
			{
			case 0:
				std::cout << "������ɫ���ļ���ȡʧ�ܣ�" << std::endl; 
				break;
			case 1:
				std::cout << "ƬԪ��ɫ���ļ���ȡʧ�ܣ�" << std::endl;
				break;
			case 2:
				std::cout << "������ɫ���ļ���ȡʧ�ܣ�" << std::endl;
				break;
			}
		}
	}


	void Shader::CreateAndCheckShader(unsigned int& id, const char* code, int type)
	{
		int success = 0;
		char info_log[512];

		switch (type)
		{
		//������ɫ��
		case 0:
		{
			id = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(id, 1, &code, nullptr);
			glCompileShader(id);
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(id, 512, nullptr, info_log);
				std::cout << "������ɫ������ʧ�ܣ�\n" << info_log << std::endl;
			}
		}break;
		//ƬԪ��ɫ��
		case 1:
		{
			id = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(id, 1, &code, nullptr);
			glCompileShader(id);
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(id, 512, nullptr, info_log);
				std::cout << "ƬԪ��ɫ������ʧ�ܣ�\n" << info_log << std::endl;
			}
		}break;
		//������ɫ��
		case 2:
		{
			id = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(id, 1, &code, nullptr);
			glCompileShader(id);
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(id, 512, nullptr, info_log);
				std::cout << "������ɫ������ʧ�ܣ�\n" << info_log << std::endl;
			}
		}break;
		}
	}


	void Shader::CheckProgram()
	{
		int success = 0;
		char info_log[512];
		glGetProgramiv(id_, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id_, 512, nullptr, info_log);
			std::cout << "��ɫ��������ʧ�ܣ�\n" << info_log << std::endl;
		}
	}
}