#pragma once

#include "glad/glad.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>


namespace OGE
{
#define SPtr(T)		std::shared_ptr<T>
#define SPCast(T)	std::static_pointer_cast<T>


	class Object
	{
	public:
		//获得名字
		std::string GetName() const { return name_; }

	protected:
		//防止外部创建对象
		Object() {}

	protected:
		std::string		name_;
	};
}