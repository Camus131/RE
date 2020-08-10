#pragma once

#include <vector>
#include <map>

#include "DrawCallSet.h"


namespace OGE
{
	class DrawArrays :public DrawCallSet
	{
	public:
		//绘制段
		struct DrawSegment
		{
			//绘制起始索引
			int First;
			//绘制顶点个数
			int Count;

			DrawSegment(int first, int count) :
				First(first), Count(count) {}

			bool operator < (const DrawSegment& segment) const { return First < segment.First; }
		};

		typedef std::vector<DrawSegment>	DrawSegments;
		typedef std::map<DrawSegment, bool>	DrawSegmentsMap;

		//创建实例
		static SPtr(DrawArrays) Create(Mode mode, int first, int count, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawArrays)(new DrawArrays(mode, first, count, enable, instanced_num));
		}

		static SPtr(DrawArrays) Create(Mode mode, const DrawSegment& segment, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawArrays)(new DrawArrays(mode, segment, enable, instanced_num));
		}

		static SPtr(DrawArrays) Create(Mode mode, const DrawSegments& segments, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawArrays)(new DrawArrays(mode, segments, enable, instanced_num));
		}

		//获得所有绘制段
		DrawSegmentsMap GetAllSegments() const { return segments_map_; }

		//获得所有绘制段个数
		int NumOfAllSegments() const { return segments_map_.size(); }

		//获得启用绘制段个数
		int NumOfEnableSegments() const;

		//获得某个绘制段启用状态
		//1——启用，0——未启用，-1——获取失败
		int GetSegmentEnable(int first, int count) const;
		int GetSegmentEnable(const DrawSegment& segment) const;

		//设置绘制段启用状态
		void SetSegmentsEnable(int first, int count, bool enable);
		void SetSegmentsEnable(const DrawSegment& segment, bool enable);
		void SetSegmentsEnable(const DrawSegments& segments, bool enable);
		void SetAllSegmentsEnable(bool enable);

		//插入绘制段
		void InsertSegments(int first, int count, bool enable = true);
		void InsertSegments(const DrawSegment& segment, bool enable = true);
		void InsertSegments(const DrawSegments& segments, bool enable = true);

		//删除绘制段
		void DeleteSegments(int first, int count);
		void DeleteSegments(const DrawSegment& segment);
		void DeleteSegments(const DrawSegments& segments);
		void DeleteAllSegments() { segments_map_.clear(); }

		//绘制调用
		//绘制段个数大于1时无法实例绘制
		void Draw() const;

	private:
		DrawArrays(Mode mode, int first, int count, bool enable = true, int instanced_num = 1) :
			DrawCallSet(mode, instanced_num)
		{
			segments_map_[DrawSegment(first, count)] = enable;
		}

		DrawArrays(Mode mode, const DrawSegment& segment, bool enable = true, int instanced_num = 1) :
			DrawCallSet(mode, instanced_num)
		{
			segments_map_[segment] = enable;
		}

		DrawArrays(Mode mode, const DrawSegments& segments, bool enable = true, int instanced_num = 1) :
			DrawCallSet(mode, instanced_num)
		{
			for (int i = 0; i < segments.size(); ++i)
				segments_map_[segments[i]] = enable;
		}

	private:
		//所有绘制段及其启用状态的映射表
		DrawSegmentsMap		segments_map_;
	};
}