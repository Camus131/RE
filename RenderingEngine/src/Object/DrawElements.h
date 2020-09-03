#pragma once

#include "DrawingSet.h"


namespace OGE
{
	class DrawElements :public DrawingSet
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
		typedef std::map<DrawSegment, bool>	DrawSegments;

		//获得所有绘制段
		DrawSegments GetAllSegments() const { return segments_map_; }

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
		void SetAllSegmentsEnable(bool enable);

		//插入绘制段
		void AddSegments(int offset, int count, int basevertex, bool enable = true);
		void AddSegments(const DrawSegment& segment, bool enable = true);

		//删除绘制段
		void RemoveSegments(int offset, int count, int basevertex);
		void RemoveSegments(const DrawSegment& segment);
		void RemoveAllSegments() { segments_map_.clear(); }

	protected:
		DrawElements(Mode mode = POINTS, int instanced_num = 1) :
			DrawingSet(mode, instanced_num) {}

	protected:
		//所有绘制段及其启用状态的映射表
		DrawSegments		segments_map_;
	};


	class DrawElementsUByte :public DrawElements
	{
	public:
		typedef unsigned char value_type;

		//创建实例
		static SPtr(DrawElementsUByte) Create(Mode mode, int instanced_num = 1)
		{
			return SPtr(DrawElementsUByte)(new DrawElementsUByte(mode, instanced_num));
		}
		static SPtr(DrawElementsUByte) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUByte)(new DrawElementsUByte(mode, offset, count, basevertex, enable, instanced_num));
		}

		SPtr(DrawElementsUByte) Copy() const;

		//获得/设置索引数组
		std::vector<value_type>& GetIndices() { return indices_; }
		std::vector<value_type> GetIndices() const { return indices_; }
		void SetIndices(const std::vector<value_type>& indices) { indices_ = indices; }

	protected:
		DrawElementsUByte(Mode mode, int instanced_num = 1);
		DrawElementsUByte(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1);

	protected:
		std::vector<value_type>		indices_;
	};


	class DrawElementsUShort :public DrawElements
	{
	public:
		typedef unsigned short value_type;

		//创建实例
		static SPtr(DrawElementsUShort) Create(Mode mode, int instanced_num = 1)
		{
			return SPtr(DrawElementsUShort)(new DrawElementsUShort(mode, instanced_num));
		}
		static SPtr(DrawElementsUShort) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUShort)(new DrawElementsUShort(mode, offset, count, basevertex, enable, instanced_num));
		}

		SPtr(DrawElementsUShort) Copy() const;

		//获得/设置索引数组
		std::vector<value_type>& GetIndices() { return indices_; }
		std::vector<value_type> GetIndices() const { return indices_; }
		void SetIndices(const std::vector<value_type>& indices) { indices_ = indices; }

	protected:
		DrawElementsUShort(Mode mode, int instanced_num = 1);
		DrawElementsUShort(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1);

	protected:
		std::vector<value_type>		indices_;
	};


	class DrawElementsUInt :public DrawElements
	{
	public:
		typedef unsigned int value_type;

		//创建实例
		static SPtr(DrawElementsUInt) Create(Mode mode, int instanced_num = 1)
		{
			return SPtr(DrawElementsUInt)(new DrawElementsUInt(mode, instanced_num));
		}
		static SPtr(DrawElementsUInt) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUInt)(new DrawElementsUInt(mode, offset, count, basevertex, enable, instanced_num));
		}

		SPtr(DrawElementsUInt) Copy() const;

		//获得/设置索引数组
		std::vector<value_type>& GetIndices() { return indices_; }
		std::vector<value_type> GetIndices() const { return indices_; }
		void SetIndices(const std::vector<value_type>& indices) { indices_ = indices; }

	protected:
		DrawElementsUInt(Mode mode, int instanced_num = 1);
		DrawElementsUInt(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1);

	protected:
		std::vector<value_type>		indices_;
	};
}