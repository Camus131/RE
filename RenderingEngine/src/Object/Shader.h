#pragma once

#include "ExternalObject.h"


namespace OGE
{
	class Shader :public ExternalObject
	{
	public:
		//着色器类型
		enum Type
		{
			VERTEX_SHADER = GL_VERTEX_SHADER,
			FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
			GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		};

		//接收字符串类型,代码或文件路径
		enum StrType
		{
			CODE,
			FILE,
		};

		//创建实例
		static SPtr(Shader) Create(Type type, const std::string& code, StrType str_type = CODE)
		{
			return SPtr(Shader)(new Shader(type, code, str_type));
		}

		SPtr(Shader) Copy() const { return SPtr(Shader)(new Shader(type_, code_)); }

		//获得/设置着色器代码
		std::string GetCode() const { return code_; }
		void SetCode(const std::string& code, StrType str_type = CODE);

		//获得/设置着色器类型
		Type GetType() const { return type_; }
		void SetType(Type type) { type_ = type; }

		bool operator == (const Shader& shader) const { return type_ == shader.type_ && code_ == shader.code_; }

	protected:
		Shader(Type type, const std::string& code, StrType str_type = CODE);

		//读取shader文件并检错
		void ReadShaderFile(const std::string& filepath);

	protected:
		//着色器类型
		Type			type_;

		//着色器代码
		std::string		code_;
	};
}
