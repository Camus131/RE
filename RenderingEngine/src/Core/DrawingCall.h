#pragma once

#include "../Object/DrawArrays.h"
#include "../Object/DrawElements.h"


namespace OGE
{
	class DrawingCall :public Object
	{
	public:
		//����ʵ��
		static SPtr(DrawingCall) Create(SPtr(DrawingSet) drawing_set)
		{
			return SPtr(DrawingCall)(new DrawingCall(drawing_set));
		}

		void Draw() const;

		//���/����drawing set
		SPtr(DrawingSet) GetDrawingSet() { return drawing_set_; }
		void SetDrawingSet(SPtr(DrawingSet) drawing_set) { drawing_set_ = drawing_set; }

	protected:
		DrawingCall(SPtr(DrawingSet) drawing_set);

	protected:
		SPtr(DrawingSet)		drawing_set_;
	};
}