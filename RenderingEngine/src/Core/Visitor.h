#pragma once

#include "BaseObject.h"


namespace OGE
{
	class Interviewee;

	class Visitor :public BaseObject
	{
	public:
		//���ʶ���
		virtual void Visit(SPtr(Interviewee) object) {}

	protected:
		Visitor() :
			BaseObject() {}
	};
}