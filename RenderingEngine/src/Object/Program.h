#pragma once

#include "Shader.h"


namespace OGE
{
	class Program :public ExternalObject
	{
	public:
		//创建实例
		static SPtr(Program) Create()
		{
			return SPtr(Program)(new Program);
		}

		SPtr(Program) Copy() const;

		//添加/删除/获得着色器
		void AddShader(SPtr(Shader) shader);
		void RemoveShader(SPtr(Shader) shader);
		void RemoveShader(Shader::Type type);
		SPtr(Shader) GetShader(Shader::Type type) const;

		//获得着色器个数
		int GetShaderNum() const { return shader_list_.size(); }

		//清空
		void Clear() { shader_list_.clear(); }

	protected:
		Program();

	protected:
		typedef std::vector<SPtr(Shader)> ShaderList;
		//着色器列表
		ShaderList		shader_list_;
	};
}