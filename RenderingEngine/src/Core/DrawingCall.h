#pragma once

#include "Object/DrawingSet.h"


namespace OGE
{
	class DrawingCall :public BaseObject
	{
	public:
		//创建实例
		static SPtr(DrawingCall) Create(SPtr(DrawingSet) drawing_set)
		{
			return SPtr(DrawingCall)(new DrawingCall(drawing_set));
		}

		void Draw() const;

		//获得/设置drawing set
		SPtr(DrawingSet) GetDrawingSet() { return drawing_set_; }
		void SetDrawingSet(SPtr(DrawingSet) drawing_set) { drawing_set_ = drawing_set; }

	protected:
		DrawingCall(SPtr(DrawingSet) drawing_set):
			BaseObject(),
			drawing_set_(drawing_set)
		{
			name_ = OGE_DrawingCall;
		}

	protected:
		SPtr(DrawingSet)		drawing_set_;
	};
}