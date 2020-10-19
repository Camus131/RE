#pragma once

#include "Object/Uniform.h"


namespace OGE
{
	class UniformList :public BaseObject
	{
	public:
		//创建实例
		static SPtr(UniformList) Create()
		{
			return SPtr(UniformList)(new UniformList);
		}

		//添加/删除/获得uniform
		void AddUniform(SPtr(Uniform) uniform);
		void RemoveUniform(SPtr(Uniform) uniform);
		void RemoveUniform(const std::string& name);
		SPtr(Uniform) GetUniform(const std::string& name) const;
		SPtr(Uniform) GetUniform(int index) const { return uniform_list_[index]; }

		//获得uniform个数
		int GetUniformNum() const { return uniform_list_.size(); }

		//清空
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