#pragma once

#include "Object.h"


namespace OGE
{
	class ExternalObject;

	class Visitor :public Object
	{
	public:
		//�����ⲿ����
		virtual void Visit(SPtr(ExternalObject) object) {}

	protected:
		Visitor() :
			Object() {}
	};
}