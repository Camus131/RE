#pragma once

#include "DrawingSet.h"


namespace OGE
{
	class DrawArrays :public DrawingSet
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
		typedef std::map<DrawSegment, bool>	DrawSegments;

		//创建实例
		static SPtr(DrawArrays) Create(Mode mode,int instanced_num = 1)
		{
			return SPtr(DrawArrays)(new DrawArrays(mode, instanced_num));
		}
		static SPtr(DrawArrays) Create(Mode mode, int first, int count, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawArrays)(new DrawArrays(mode, first, count, enable, instanced_num));
		}

		SPtr(DrawArrays) Copy() const;

		//获得所有绘制段
		DrawSegments GetAllSegments() const { return segments_map_; }

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
		void SetAllSegmentsEnable(bool enable);

		//添加绘制段
		void AddSegments(int first, int count, bool enable = true);
		void AddSegments(const DrawSegment& segment, bool enable = true);

		//删除绘制段
		void RemoveSegments(int first, int count);
		void RemoveSegments(const DrawSegment& segment);
		void RemoveAllSegments() { segments_map_.clear(); }

	protected:
		DrawArrays(Mode mode, int instanced_num = 1);
		DrawArrays(Mode mode, int first, int count, bool enable = true, int instanced_num = 1);

	protected:
		//所有绘制段及其启用状态的映射表
		DrawSegments		segments_map_;
	};
}