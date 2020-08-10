#pragma once

#include <unordered_map>

#include "GLObject.h"
#include "../Math/Vec2f.h"
#include "../Math/Vec4f.h"
#include "../Math/Matrixf.h"


namespace OGE
{
	class Shader :public GLObject
	{
	public:
		typedef std::unordered_map<std::string, int>	UniformLocationMap;

		//�����ַ�������,������ļ�·��
		enum Type
		{
			FILE_READ,
			CODE_READ,
		};

		//����ʵ��
		static SPtr(Shader) Create(const std::string& vs, const std::string& fs, Type type = FILE_READ)
		{
			return SPtr(Shader)(new Shader(vs, fs, type));
		}

		static SPtr(Shader) Create(const std::string& vs, const std::string& fs, const std::string& gs, Type type = FILE_READ)
		{
			return SPtr(Shader)(new Shader(vs, fs, gs, type));
		}

		~Shader() { glDeleteProgram(id_); }

		void Bind() const { glUseProgram(id_); }
		void UnBind() const { glUseProgram(0); }

		//����uniform������ֵ
		//ʹ��ǰ�����Bind()
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, const Vec2f& value);
		void SetUniform(const std::string& name, const Vec3f& value);
		void SetUniform(const std::string& name, const Vec4f& value);
		void SetUniform(const std::string& name, const Matrixf& value);

	private:
		Shader(const std::string& vs, const std::string& fs, Type type = FILE_READ);
		Shader(const std::string& vs, const std::string& fs, const std::string& gs, Type type = FILE_READ);

		//��ѯuniform������location
		int QueryLocation(const std::string& name);

		//��ȡshader�ļ������
		void ReadAndCheckShaderFile(const std::string& filepath, std::string& code, int type);

		//����shader�����
		void CreateAndCheckShader(unsigned int& id, const char* code, int type);

		//program���
		void CheckProgram();

	private:
		//uniform����������location��ӳ���
		UniformLocationMap		location_map_;
	};
}