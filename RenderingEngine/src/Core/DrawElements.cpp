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


	void DrawElements::SetSegmentsEnable(const DrawSegments& segments, bool enable)
	{
		for (int i = 0; i < segments.size(); ++i)
		{
			auto iter = segments_map_.find(segments[i]);
			if (iter != segments_map_.end())
				iter->second = enable;
		}
	}


	void DrawElements::SetAllSegmentsEnable(bool enable)
	{
		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
			iter->second = enable;
	}


	void DrawElements::InsertSegments(int offset, int count, int basevertex, bool enable)
	{
		auto iter = segments_map_.find(DrawSegment(offset, count, basevertex));
		if (iter == segments_map_.end())
			segments_map_[DrawSegment(offset, count, basevertex)] = enable;
	}


	void DrawElements::InsertSegments(const DrawSegment& segment, bool enable)
	{
		auto iter = segments_map_.find(segment);
		if (iter == segments_map_.end())
			segments_map_[segment] = enable;
	}


	void DrawElements::InsertSegments(const DrawSegments& segments, bool enable)
	{
		for (int i = 0; i < segments.size(); ++i)
		{
			auto iter = segments_map_.find(segments[i]);
			if (iter == segments_map_.end())
				segments_map_[segments[i]] = enable;
		}
	}


	void DrawElements::DeleteSegments(int offset, int count, int basevertex)
	{
		auto iter = segments_map_.find(DrawSegment(offset, count, basevertex));
		if (iter != segments_map_.end())
			segments_map_.erase(iter);
	}


	void DrawElements::DeleteSegments(const DrawSegment& segment)
	{
		auto iter = segments_map_.find(segment);
		if (iter != segments_map_.end())
			segments_map_.erase(iter);
	}


	void DrawElements::DeleteSegments(const DrawSegments& segments)
	{
		for (int i = 0; i < segments.size(); ++i)
		{
			auto iter = segments_map_.find(segments[i]);
			if (iter != segments_map_.end())
				segments_map_.erase(iter);
		}
	}


	void DrawElementsUByte::Draw() const
	{
		//筛选出启用的绘制段
		std::vector<void*> offset_array;
		std::vector<int> count_array, basevertex_array;

		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
		{
			if (iter->second == true)
			{
				offset_array.emplace_back((void*)(iter->first.Offset * sizeof(unsigned char)));
				count_array.emplace_back(iter->first.Count);
				basevertex_array.emplace_back(iter->first.BaseVertex);
			}
		}

		//无启用的则返回
		int draw_count = count_array.size();
		if (!draw_count)
			return;

		//应用不同的绘制调用
		if (segments_map_.size() > 1)
		{
			if (draw_count > 1)
				glMultiDrawElementsBaseVertex(mode_, &count_array[0], GL_UNSIGNED_BYTE, &offset_array[0], draw_count, &basevertex_array[0]);
			else
				glDrawElementsBaseVertex(mode_, count_array[0], GL_UNSIGNED_BYTE, offset_array[0], basevertex_array[0]);
		}
		else
		{
			if (instanced_num_ > 1)
				glDrawElementsInstancedBaseVertex(mode_, count_array[0], GL_UNSIGNED_BYTE, offset_array[0], instanced_num_, basevertex_array[0]);
			else
				glDrawElementsBaseVertex(mode_, count_array[0], GL_UNSIGNED_BYTE, offset_array[0], basevertex_array[0]);
		}
	}


	void DrawElementsUShort::Draw() const
	{
		//筛选出启用的绘制段
		std::vector<void*> offset_array;
		std::vector<int> count_array, basevertex_array;

		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
		{
			if (iter->second == true)
			{
				offset_array.emplace_back((void*)(iter->first.Offset * sizeof(unsigned short)));
				count_array.emplace_back(iter->first.Count);
				basevertex_array.emplace_back(iter->first.BaseVertex);
			}
		}

		//无启用的则返回
		int draw_count = count_array.size();
		if (!draw_count)
			return;

		//应用不同的绘制调用
		if (segments_map_.size() > 1)
		{
			if (draw_count > 1)
				glMultiDrawElementsBaseVertex(mode_, &count_array[0], GL_UNSIGNED_SHORT, &offset_array[0], draw_count, &basevertex_array[0]);
			else
				glDrawElementsBaseVertex(mode_, count_array[0], GL_UNSIGNED_SHORT, offset_array[0], basevertex_array[0]);
		}
		else
		{
			if (instanced_num_ > 1)
				glDrawElementsInstancedBaseVertex(mode_, count_array[0], GL_UNSIGNED_SHORT, offset_array[0], instanced_num_, basevertex_array[0]);
			else
				glDrawElementsBaseVertex(mode_, count_array[0], GL_UNSIGNED_SHORT, offset_array[0], basevertex_array[0]);
		}
	}


	void DrawElementsUInt::Draw() const
	{
		//筛选出启用的绘制段
		std::vector<void*> offset_array;
		std::vector<int> count_array, basevertex_array;

		for (auto iter = segments_map_.begin(); iter != segments_map_.end(); ++iter)
		{
			if (iter->second == true)
			{
				offset_array.emplace_back((void*)(iter->first.Offset * sizeof(unsigned int)));
				count_array.emplace_back(iter->first.Count);
				basevertex_array.emplace_back(iter->first.BaseVertex);
			}
		}

		//无启用的则返回
		int draw_count = count_array.size();
		if (!draw_count)
			return;

		//应用不同的绘制调用
		if (segments_map_.size() > 1)
		{
			if (draw_count > 1)
				glMultiDrawElementsBaseVertex(mode_, &count_array[0], GL_UNSIGNED_INT, &offset_array[0], draw_count, &basevertex_array[0]);
			else
				glDrawElementsBaseVertex(mode_, count_array[0], GL_UNSIGNED_INT, offset_array[0], basevertex_array[0]);
		}
		else
		{
			if (instanced_num_ > 1)
				glDrawElementsInstancedBaseVertex(mode_, count_array[0], GL_UNSIGNED_INT, offset_array[0], instanced_num_, basevertex_array[0]);
			else
				glDrawElementsBaseVertex(mode_, count_array[0], GL_UNSIGNED_INT, offset_array[0], basevertex_array[0]);
		}
	}
}