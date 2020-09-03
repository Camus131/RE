#include "UniformList.h"


namespace OGE
{
	UniformList::UniformList() :
		Object()
	{
		name_ = "UniformList";
	}


	void UniformList::AddUniform(SPtr(Uniform) uniform)
	{
		for (auto iter = uniform_list_.begin(); iter != uniform_list_.end(); ++iter)
		{
			if ((*iter)->GetUniformName() == uniform->GetUniformName())
			{
				uniform_list_.erase(iter);
				uniform_list_.emplace_back(uniform);
				return;
			}
		}
		uniform_list_.emplace_back(uniform);
	}


	void UniformList::RemoveUniform(SPtr(Uniform) uniform)
	{
		for (auto iter = uniform_list_.begin(); iter != uniform_list_.end(); ++iter)
		{
			if (*iter == uniform)
			{
				uniform_list_.erase(iter);
				return;
			}
		}
	}


	void UniformList::RemoveUniform(const std::string& name)
	{
		for (auto iter = uniform_list_.begin(); iter != uniform_list_.end(); ++iter)
		{
			if ((*iter)->GetUniformName() == name)
			{
				uniform_list_.erase(iter);
				break;
			}
		}
	}


	SPtr(Uniform) UniformList::GetUniform(const std::string& name) const
	{
		for (auto iter = uniform_list_.begin(); iter != uniform_list_.end(); ++iter)
		{
			if ((*iter)->GetUniformName() == name)
				return *iter;
		}
		return nullptr;
	}
}