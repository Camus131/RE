#include "DrawArrays.h"


namespace OGE
{
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


	void DrawArrays::SetSegmentsEnable(const DrawSegments& segments, bool enable)
	{
		for (int i = 0; i < segments.size(); ++i)
		{
			auto iter = segments_map_.find(segments[i]);
			if (iter != segments_map_.end())
				iter->second = enable;
		}
	}


	void DrawArrays::SetAllSegmentsEnable(bool enable)
	{
		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
			iter->second = enable;
	}


	void DrawArrays::InsertSegments(int first, int count, bool enable)
	{
		auto iter = segments_map_.find(DrawSegment(first, count));
		if (iter == segments_map_.end())
			segments_map_[DrawSegment(first, count)] = enable;
	}


	void DrawArrays::InsertSegments(const DrawSegment& segment, bool enable)
	{
		auto iter = segments_map_.find(segment);
		if (iter == segments_map_.end())
			segments_map_[segment] = enable;
	}


	void DrawArrays::InsertSegments(const DrawSegments& segments, bool enable)
	{
		for (int i = 0; i < segments.size(); ++i)
		{
			auto iter = segments_map_.find(segments[i]);
			if (iter == segments_map_.end())
				segments_map_[segments[i]] = enable;
		}
	}


	void DrawArrays::DeleteSegments(int first, int count)
	{
		auto iter = segments_map_.find(DrawSegment(first, count));
		if (iter != segments_map_.end())
			segments_map_.erase(iter);
	}


	void DrawArrays::DeleteSegments(const DrawSegment& segment)
	{
		auto iter = segments_map_.find(segment);
		if (iter != segments_map_.end())
			segments_map_.erase(iter);
	}


	void DrawArrays::DeleteSegments(const DrawSegments& segments)
	{
		for (int i = 0; i < segments.size(); ++i)
		{
			auto iter = segments_map_.find(segments[i]);
			if (iter != segments_map_.end())
				segments_map_.erase(iter);
		}
	}


	void DrawArrays::Draw() const
	{
		//筛选出启用的绘制段
		std::vector<int> first_array, count_array;
		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
		{
			if (iter->second == true)
			{
				first_array.emplace_back(iter->first.First);
				count_array.emplace_back(iter->first.Count);
			}
		}

		//无启用的则返回
		int draw_count = first_array.size();
		if (!draw_count)
			return;

		//应用不同的绘制调用
		if (segments_map_.size() > 1)
		{
			if (draw_count > 1)
				glMultiDrawArrays(mode_, &first_array[0], &count_array[0], draw_count);
			else
				glDrawArrays(mode_, first_array[0], count_array[0]);
		}
		else
		{
			if (instanced_num_ > 1)
				glDrawArraysInstanced(mode_, first_array[0], count_array[0], instanced_num_);
			else
				glDrawArrays(mode_, first_array[0], count_array[0]);
		}
	}
}