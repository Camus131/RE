#pragma once

#include "Visitor.h"


namespace OGE
{
	class Interviewee :public BaseObject
	{
	public:
		//���շ�����
		virtual void Accept(SPtr(Visitor) visitor) { visitor->Visit(SPtrCast(Interviewee, Self())); }

	protected:
		Interviewee() :
			BaseObject() {}
	};
}