#include "DrawElements.h"


namespace OGE
{
	int DrawElements::NumOfEnableSegments() const
	{
		int num = 0;
		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
		{
			if (iter->second == true)
				++num;
		}
		return num;
	}


	int DrawElements::GetSegmentEnable(int offset, int count, int basevertex) const
	{
		auto iter = segments_map_.find(DrawSegment(offset, count, basevertex));
		if (iter == segments_map_.end())
			return -1;

		return iter->second;
	}


	int DrawElements::GetSegmentEnable(const DrawSegment& segment) const
	{
		auto iter = segments_map_.find(segment);
		if (iter == segments_map_.end())
			return -1;

		return iter->second;
	}


	void DrawElements::SetSegmentsEnable(int offset, int count, int basevertex, bool enable)
	{
		auto iter = segments_map_.find(DrawSegment(offset, count, basevertex));
		if (iter != segments_map_.end())
			iter->second = enable;
	}


	void DrawElements::SetSegmentsEnable(const DrawSegment& segment, bool enable)
	{
		auto iter = segments_map_.find(segment);
		if (iter != segments_map_.end())
			iter->second = enable;
	}


	void DrawElements::SetAllSegmentsEnable(bool enable)
	{
		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
			iter->second = enable;
	}


	void DrawElements::AddSegments(int offset, int count, int basevertex, bool enable)
	{
		auto iter = segments_map_.find(DrawSegment(offset, count, basevertex));
		if (iter == segments_map_.end())
			segments_map_[DrawSegment(offset, count, basevertex)] = enable;
	}


	void DrawElements::AddSegments(const DrawSegment& segment, bool enable)
	{
		auto iter = segments_map_.find(segment);
		if (iter == segments_map_.end())
			segments_map_[segment] = enable;
	}


	void DrawElements::RemoveSegments(int offset, int count, int basevertex)
	{
		auto iter = segments_map_.find(DrawSegment(offset, count, basevertex));
		if (iter != segments_map_.end())
			segments_map_.erase(iter);
	}


	void DrawElements::RemoveSegments(const DrawSegment& segment)
	{
		auto iter = segments_map_.find(segment);
		if (iter != segments_map_.end())
			segments_map_.erase(iter);
	}


	DrawElementsUByte::DrawElementsUByte(Mode mode, int instanced_num) :
		DrawElements(mode, instanced_num)
	{
		name_ = "DrawElementsUByte";
	}


	DrawElementsUByte::DrawElementsUByte(Mode mode, int offset, int count, int basevertex, bool enable, int instanced_num) :
		DrawElements(mode, instanced_num)
	{
		name_ = "DrawElementsUByte";
		segments_map_[DrawSegment(offset, count, basevertex)] = enable;
	}


	SPtr(DrawElementsUByte) DrawElementsUByte::Copy() const
	{
		SPtr(DrawElementsUByte) drawcall = SPtr(DrawElementsUByte)(new DrawElementsUByte(mode_, instanced_num_));
		drawcall->segments_map_ = segments_map_;
		return drawcall;
	}


	DrawElementsUShort::DrawElementsUShort(Mode mode, int instanced_num) :
		DrawElements(mode, instanced_num)
	{
		name_ = "DrawElementsUShort";
	}


	DrawElementsUShort::DrawElementsUShort(Mode mode, int offset, int count, int basevertex, bool enable, int instanced_num) :
		DrawElements(mode, instanced_num)
	{
		name_ = "DrawElementsUShort";
		segments_map_[DrawSegment(offset, count, basevertex)] = enable;
	}


	SPtr(DrawElementsUShort) DrawElementsUShort::Copy() const
	{
		SPtr(DrawElementsUShort) drawcall = SPtr(DrawElementsUShort)(new DrawElementsUShort(mode_, instanced_num_));
		drawcall->segments_map_ = segments_map_;
		return drawcall;
	}


	DrawElementsUInt::DrawElementsUInt(Mode mode, int instanced_num) :
		DrawElements(mode, instanced_num)
	{
		name_ = "DrawElementsUInt";
	}


	DrawElementsUInt::DrawElementsUInt(Mode mode, int offset, int count, int basevertex, bool enable, int instanced_num) :
		DrawElements(mode, instanced_num)
	{
		name_ = "DrawElementsUInt";
		segments_map_[DrawSegment(offset, count, basevertex)] = enable;
	}


	SPtr(DrawElementsUInt) DrawElementsUInt::Copy() const
	{
		SPtr(DrawElementsUInt) drawcall = SPtr(DrawElementsUInt)(new DrawElementsUInt(mode_, instanced_num_));
		drawcall->segments_map_ = segments_map_;
		return drawcall;
	}
}