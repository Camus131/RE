#pragma once

#include "ContextObject.h"

#include "Object/Program.h"
#include "Object/Uniform.h"


namespace OGE
{
	class ShaderSource :public ContextObject
	{
	public:
		//����ʵ��
		static SPtr(ShaderSource) Create(SPtr(Program) program)
		{
			return SPtr(ShaderSource)(new ShaderSource(program));
		}

		~ShaderSource() { glDeleteProgram(id_); }

		virtual void Bind() const { glUseProgram(id_); }
		virtual void UnBind() const { glUseProgram(0); }

		//���Program
		SPtr(Program) GetProgram() const { return program_; }

		//����uniform������ֵ
		void SetUniform(SPtr(Uniform) uniform);

	protected:
		ShaderSource(SPtr(Program) program);

		//��ʼ��
		void CreateProgram(SPtr(Program) program);
		void CreateShader(SPtr(Shader) shader, unsigned int& id);

		//��ѯuniform������location
		int QueryLocation(const std::string& name);

	protected:
		SPtr(Program)		program_;

		typedef std::unordered_map<std::string, int>	LocationMap;
		//uniform����������location��ӳ���
		LocationMap			location_map_;

		typedef std::unordered_map<int, SPtr(Uniform)>	UniformMap;
		//�����е�uniformӳ���
		UniformMap			uniform_map_;
	};
}