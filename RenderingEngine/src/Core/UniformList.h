#pragma once

#include "Object/Uniform.h"


namespace OGE
{
	class UniformList :public BaseObject
	{
	public:
		//����ʵ��
		static SPtr(UniformList) Create()
		{
			return SPtr(UniformList)(new UniformList);
		}

		//���/ɾ��/���uniform
		void AddUniform(SPtr(Uniform) uniform);
		void RemoveUniform(SPtr(Uniform) uniform);
		void RemoveUniform(const std::string& name);
		SPtr(Uniform) GetUniform(const std::string& name) const;
		SPtr(Uniform) GetUniform(int index) const { return uniform_list_[index]; }

		//���uniform����
		int GetUniformNum() const { return uniform_list_.size(); }

		//���
		void Clear() { uniform_list_.clear(); }

	protected:
		UniformList() :
			BaseObject()
		{
			name_ = OGE_UniformList;
		}

	protected:
		std::vector<SPtr(Uniform)>		uniform_list_;
	};
}