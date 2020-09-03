#pragma once

#include "ContextObject.h"

#include "../Object/Program.h"
#include "../Object/Uniform.h"


namespace OGE
{
	class ShaderSource :public ContextObject
	{
	public:
		//创建实例
		static SPtr(ShaderSource) Create(SPtr(Program) program)
		{
			return SPtr(ShaderSource)(new ShaderSource(program));
		}

		~ShaderSource() { glDeleteProgram(id_); }

		void Bind() const { glUseProgram(id_); }
		void UnBind() const { glUseProgram(0); }

		//获得Program
		SPtr(Program) GetProgram() const { return program_; }

		//设置uniform变量的值
		void SetUniform(SPtr(Uniform) uniform);

	protected:
		ShaderSource(SPtr(Program) program);

		void CreateProgram(SPtr(Program) program);

		void CreateShader(SPtr(Shader) shader, unsigned int& id);

		//查询uniform变量的location
		int QueryLocation(const std::string& name);

		//查询uniform变量的当前值
		SPtr(Uniform) QueryUniform(int location, SPtr(Uniform) uniform);

	protected:
		SPtr(Program)		program_;

		typedef std::unordered_map<std::string, int>	LocationMap;
		//uniform变量名及其location的映射表
		LocationMap			location_map_;

		typedef std::unordered_map<int, SPtr(Uniform)>	UniformMap;
		//启用uniform映射表
		UniformMap			uniform_map_;
	};
}