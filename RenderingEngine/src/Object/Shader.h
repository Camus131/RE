#pragma once

#include "ExternalObject.h"


namespace OGE
{
	class Shader :public ExternalObject
	{
	public:
		//��ɫ������
		enum Type
		{
			VERTEX_SHADER = GL_VERTEX_SHADER,
			FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
			GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		};

		//�����ַ�������,������ļ�·��
		enum StrType
		{
			CODE,
			FILE,
		};

		//����ʵ��
		static SPtr(Shader) Create(Type type, const std::string& code, StrType str_type = CODE)
		{
			return SPtr(Shader)(new Shader(type, code, str_type));
		}

		SPtr(Shader) Copy() const { return SPtr(Shader)(new Shader(type_, code_)); }

		//���/������ɫ������
		std::string GetCode() const { return code_; }
		void SetCode(const std::string& code, StrType str_type = CODE);

		//���/������ɫ������
		Type GetType() const { return type_; }
		void SetType(Type type) { type_ = type; }

		bool operator == (const Shader& shader) const { return type_ == shader.type_ && code_ == shader.code_; }

	protected:
		Shader(Type type, const std::string& code, StrType str_type = CODE);

		//��ȡshader�ļ������
		void ReadShaderFile(const std::string& filepath);

	protected:
		//��ɫ������
		Type			type_;

		//��ɫ������
		std::string		code_;
	};
}
