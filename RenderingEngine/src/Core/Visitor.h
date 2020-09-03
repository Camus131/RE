#pragma once

#include "Object.h"


namespace OGE
{
	class ExternalObject;

	class Visitor :public Object
	{
	public:
		//访问外部对象
		virtual void Visit(SPtr(ExternalObject) object) {}

	protected:
		Visitor() :
			Object() {}
	};
}