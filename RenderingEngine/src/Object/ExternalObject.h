#pragma once

#include "../Core/Visitor.h"


namespace OGE
{
	class ExternalObject :public Object
	{
	public:
		//½ÓÊÕ·ÃÎÊÆ÷
		virtual void Accept(SPtr(Visitor) visitor) { visitor->Visit(SPtr(ExternalObject)(this)); }

	protected:
		ExternalObject() :
			Object() {}
	};
}