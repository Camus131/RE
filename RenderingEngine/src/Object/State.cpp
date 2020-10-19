#include "State.h"


namespace OGE
{
	SPtr(PhongState) PhongState::Copy() const
	{
		SPtr(PhongState) state = SPtr(PhongState)(new PhongState);
		state->material_ = material_;
		return state;
	}


	SPtr(CustomState) CustomState::Copy() const
	{
		SPtr(CustomState) state = SPtr(CustomState)(new CustomState);
		state->program_ = program_;
		state->uniform_list_ = uniform_list_;
		return state;
	}


	void CustomState::AddUniform(SPtr(Uniform) uniform)
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


	void CustomState::RemoveUniform(SPtr(Uniform) uniform)
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


	void CustomState::RemoveUniform(const std::string& name)
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


	SPtr(Uniform) CustomState::GetUniform(const std::string& name) const
	{
		for (auto iter = uniform_list_.begin(); iter != uniform_list_.end(); ++iter)
		{
			if ((*iter)->GetUniformName() == name)
				return *iter;
		}
		return nullptr;
	}
}