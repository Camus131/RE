#pragma once

#include "../Core/Visitor.h"


namespace OGE
{
	class ExternalObject :public Object
	{
	public:
		//���շ�����
		virtual void Accept(SPtr(Visitor) visitor) { visitor->Visit(SPtr(ExternalObject)(this)); }

	protected:
		ExternalObject() :
			Object() {}
	};
}