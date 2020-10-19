#include "DrawArrays.h"


namespace OGE
{
	SPtr(DrawArrays) DrawArrays::Copy() const
	{
		SPtr(DrawArrays) drawcall = SPtr(DrawArrays)(new DrawArrays(mode_, instanced_num_));
		drawcall->segments_map_ = segments_map_;
		return drawcall;
	}


	int DrawArrays::NumOfEnableSegments() const
	{
		int num = 0;
		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
		{
			if (iter->second == true)
				++num;
		}
		return num;
	}


	int DrawArrays::GetSegmentEnable(int first, int count) const
	{
		auto iter = segments_map_.find(DrawSegment(first, count));
		if (iter == segments_map_.end())
			return -1;

		return iter->second;
	}


	int DrawArrays::GetSegmentEnable(const DrawSegment& segment) const
	{
		auto iter = segments_map_.find(segment);
		if (iter == segments_map_.end())
			return -1;

		return iter->second;
	}


	void DrawArrays::SetSegmentsEnable(int first, int count, bool enable)
	{
		auto iter = segments_map_.find(DrawSegment(first, count));
		if (iter != segments_map_.end())
			iter->second = enable;
	}


	void DrawArrays::SetSegmentsEnable(const DrawSegment& segment, bool enable)
	{
		auto iter = segments_map_.find(segment);
		if (iter != segments_map_.end())
			iter->second = enable;
	}


	void DrawArrays::SetAllSegmentsEnable(bool enable)
	{
		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
			iter->second = enable;
	}


	void DrawArrays::AddSegments(int first, int count, bool enable)
	{
		auto iter = segments_map_.find(DrawSegment(first, count));
		if (iter == segments_map_.end())
			segments_map_[DrawSegment(first, count)] = enable;
	}


	void DrawArrays::AddSegments(const DrawSegment& segment, bool enable)
	{
		auto iter = segments_map_.find(segment);
		if (iter == segments_map_.end())
			segments_map_[segment] = enable;
	}


	void DrawArrays::RemoveSegments(int first, int count)
	{
		auto iter = segments_map_.find(DrawSegment(first, count));
		if (iter != segments_map_.end())
			segments_map_.erase(iter);
	}


	void DrawArrays::RemoveSegments(const DrawSegment& segment)
	{
		auto iter = segments_map_.find(segment);
		if (iter != segments_map_.end())
			segments_map_.erase(iter);
	}
}