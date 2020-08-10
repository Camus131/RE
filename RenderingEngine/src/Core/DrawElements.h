#pragma once

#include <vector>
#include <map>

#include "DrawCallSet.h"


namespace OGE
{
	class DrawElements :public DrawCallSet
	{
	public:
		//绘制段
		struct DrawSegment
		{
			//绘制起始位置
			int Offset;
			//绘制顶点个数
			int Count;
			//索引累加偏移值
			int BaseVertex;

			DrawSegment(int offset, int count, int basevertex) :
				Offset(offset), Count(count), BaseVertex(basevertex) {}

			bool operator < (const DrawSegment& segment) const { return Offset < segment.Offset; }
		};

		typedef std::vector<DrawSegment>	DrawSegments;
		typedef std::map<DrawSegment, bool>	DrawSegmentsMap;

		//获得所有绘制段
		DrawSegmentsMap GetAllSegments() const { return segments_map_; }

		//获得所有绘制段个数
		int NumOfAllSegments() const { return segments_map_.size(); }

		//获得启用绘制段个数
		int NumOfEnableSegments() const;

		//获得某个绘制段启用状态
		//1——启用，0——未启用，-1——获取失败
		int GetSegmentEnable(int offset, int count, int basevertex) const;
		int GetSegmentEnable(const DrawSegment& segment) const;

		//设置绘制段启用状态
		void SetSegmentsEnable(int offset, int count, int basevertex, bool enable);
		void SetSegmentsEnable(const DrawSegment& segment, bool enable);
		void SetSegmentsEnable(const DrawSegments& segments, bool enable);
		void SetAllSegmentsEnable(bool enable);

		//插入绘制段
		void InsertSegments(int offset, int count, int basevertex, bool enable = true);
		void InsertSegments(const DrawSegment& segment, bool enable = true);
		void InsertSegments(const DrawSegments& segments, bool enable = true);

		//删除绘制段
		void DeleteSegments(int offset, int count, int basevertex);
		void DeleteSegments(const DrawSegment& segment);
		void DeleteSegments(const DrawSegments& segments);
		void DeleteAllSegments() { segments_map_.clear(); }

	protected:
		DrawElements(Mode mode, int instanced_num = 1) :
			DrawCallSet(mode, instanced_num) {}

	protected:
		//所有绘制段及其启用状态的映射表
		DrawSegmentsMap		segments_map_;
	};


	class DrawElementsUByte :public DrawElements
	{
	public:
		//创建实例
		static SPtr(DrawElementsUByte) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUByte)(new DrawElementsUByte(mode, offset, count, basevertex, enable, instanced_num));
		}

		static SPtr(DrawElementsUByte) Create(Mode mode, const DrawSegment& segment, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUByte)(new DrawElementsUByte(mode, segment, enable, instanced_num));
		}

		static SPtr(DrawElementsUByte) Create(Mode mode, const DrawSegments& segments, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUByte)(new DrawElementsUByte(mode, segments, enable, instanced_num));
		}

		//绘制调用
		//绘制段个数大于1时无法实例绘制
		void Draw() const;

	private:
		DrawElementsUByte(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			segments_map_[DrawSegment(offset, count, basevertex)] = enable;
		}

		DrawElementsUByte(Mode mode, const DrawSegment& segment, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			segments_map_[segment] = enable;
		}

		DrawElementsUByte(Mode mode, const DrawSegments& segments, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			for (int i = 0; i < segments.size(); ++i)
				segments_map_[segments[i]] = enable;
		}
	};


	class DrawElementsUShort :public DrawElements
	{
	public:
		//创建实例
		static SPtr(DrawElementsUShort) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUShort)(new DrawElementsUShort(mode, offset, count, basevertex, enable, instanced_num));
		}

		static SPtr(DrawElementsUShort) Create(Mode mode, const DrawSegment& segment, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUShort)(new DrawElementsUShort(mode, segment, enable, instanced_num));
		}

		static SPtr(DrawElementsUShort) Create(Mode mode, const DrawSegments& segments, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUShort)(new DrawElementsUShort(mode, segments, enable, instanced_num));
		}

		//绘制调用
		//绘制段个数大于1时无法实例绘制
		void Draw() const;

	private:
		DrawElementsUShort(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			segments_map_[DrawSegment(offset, count, basevertex)] = enable;
		}

		DrawElementsUShort(Mode mode, const DrawSegment& segment, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			segments_map_[segment] = enable;
		}

		DrawElementsUShort(Mode mode, const DrawSegments& segments, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			for (int i = 0; i < segments.size(); ++i)
				segments_map_[segments[i]] = enable;
		}
	};


	class DrawElementsUInt :public DrawElements
	{
	public:
		//创建实例
		static SPtr(DrawElementsUInt) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUInt)(new DrawElementsUInt(mode, offset, count, basevertex, enable, instanced_num));
		}

		static SPtr(DrawElementsUInt) Create(Mode mode, const DrawSegment& segment, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUInt)(new DrawElementsUInt(mode, segment, enable, instanced_num));
		}

		static SPtr(DrawElementsUInt) Create(Mode mode, const DrawSegments& segments, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUInt)(new DrawElementsUInt(mode, segments, enable, instanced_num));
		}

		//绘制调用
		//绘制段个数大于1时无法实例绘制
		void Draw() const;

	private:
		DrawElementsUInt(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			segments_map_[DrawSegment(offset, count, basevertex)] = enable;
		}

		DrawElementsUInt(Mode mode, const DrawSegment& segment, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			segments_map_[segment] = enable;
		}

		DrawElementsUInt(Mode mode, const DrawSegments& segments, bool enable = true, int instanced_num = 1) :
			DrawElements(mode, instanced_num)
		{
			for (int i = 0; i < segments.size(); ++i)
				segments_map_[segments[i]] = enable;
		}
	};
}