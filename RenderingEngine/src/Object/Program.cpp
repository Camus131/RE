#include "Program.h"


namespace OGE
{
	SPtr(Program) Program::Copy() const
	{
		SPtr(Program) program = SPtr(Program)(new Program);
		program->shader_list_ = shader_list_;
		return program;
	}


	void Program::AddShader(SPtr(Shader) shader)
	{
		for (auto iter = shader_list_.begin(); iter != shader_list_.end(); ++iter)
		{
			if ((*iter)->GetType() == shader->GetType())
			{
				shader_list_.erase(iter);
				shader_list_.emplace_back(shader);
				return;
			}
		}
		shader_list_.emplace_back(shader);
	}


	void Program::RemoveShader(SPtr(Shader) shader)
	{
		for (auto iter = shader_list_.begin(); iter != shader_list_.end(); ++iter)
		{
			if (*iter == shader)
			{
				shader_list_.erase(iter);
				return;
			}
		}
	}


	void Program::RemoveShader(Shader::Type type)
	{
		for (auto iter = shader_list_.begin(); iter != shader_list_.end(); ++iter)
		{
			if ((*iter)->GetType() == type)
			{
				shader_list_.erase(iter);
				break;
			}
		}
	}


	SPtr(Shader) Program::GetShader(Shader::Type type) const
	{
		for (auto iter = shader_list_.begin(); iter != shader_list_.end(); ++iter)
		{
			if ((*iter)->GetType() == type)
				return *iter;
		}
		return nullptr;
	}
}