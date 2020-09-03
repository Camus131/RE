#pragma once

#include "Shader.h"


namespace OGE
{
	class Program :public ExternalObject
	{
	public:
		//����ʵ��
		static SPtr(Program) Create()
		{
			return SPtr(Program)(new Program);
		}

		SPtr(Program) Copy() const;

		//���/ɾ��/�����ɫ��
		void AddShader(SPtr(Shader) shader);
		void RemoveShader(SPtr(Shader) shader);
		void RemoveShader(Shader::Type type);
		SPtr(Shader) GetShader(Shader::Type type) const;

		//�����ɫ������
		int GetShaderNum() const { return shader_list_.size(); }

		//���
		void Clear() { shader_list_.clear(); }

	protected:
		Program();

	protected:
		typedef std::vector<SPtr(Shader)> ShaderList;
		//��ɫ���б�
		ShaderList		shader_list_;
	};
}