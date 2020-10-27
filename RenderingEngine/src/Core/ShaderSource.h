#pragma once

#include "ContextObject.h"
#include "UniformList.h"

#include "Object/Program.h"


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
		void SetUniforms(SPtr(UniformList) uniforms);

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
	};
}