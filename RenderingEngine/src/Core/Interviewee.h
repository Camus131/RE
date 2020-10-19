#pragma once

#include "Visitor.h"


namespace OGE
{
	class Interviewee :public BaseObject
	{
	public:
		//接收访问者
		virtual void Accept(SPtr(Visitor) visitor) { visitor->Visit(SPtrCast(Interviewee, Self())); }

	protected:
		Interviewee() :
			BaseObject() {}
	};
}