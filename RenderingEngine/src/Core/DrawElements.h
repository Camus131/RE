#pragma once

#include <vector>
#include <map>

#include "DrawCallSet.h"


namespace OGE
{
	class DrawElements :public DrawCallSet
	{
	public:
		//���ƶ�
		struct DrawSegment
		{
			//������ʼλ��
			int Offset;
			//���ƶ������
			int Count;
			//�����ۼ�ƫ��ֵ
			int BaseVertex;

			DrawSegment(int offset, int count, int basevertex) :
				Offset(offset), Count(count), BaseVertex(basevertex) {}

			bool operator < (const DrawSegment& segment) const { return Offset < segment.Offset; }
		};

		typedef std::vector<DrawSegment>	DrawSegments;
		typedef std::map<DrawSegment, bool>	DrawSegmentsMap;

		//������л��ƶ�
		DrawSegmentsMap GetAllSegments() const { return segments_map_; }

		//������л��ƶθ���
		int NumOfAllSegments() const { return segments_map_.size(); }

		//������û��ƶθ���
		int NumOfEnableSegments() const;

		//���ĳ�����ƶ�����״̬
		//1�������ã�0����δ���ã�-1������ȡʧ��
		int GetSegmentEnable(int offset, int count, int basevertex) const;
		int GetSegmentEnable(const DrawSegment& segment) const;

		//���û��ƶ�����״̬
		void SetSegmentsEnable(int offset, int count, int basevertex, bool enable);
		void SetSegmentsEnable(const DrawSegment& segment, bool enable);
		void SetSegmentsEnable(const DrawSegments& segments, bool enable);
		void SetAllSegmentsEnable(bool enable);

		//������ƶ�
		void InsertSegments(int offset, int count, int basevertex, bool enable = true);
		void InsertSegments(const DrawSegment& segment, bool enable = true);
		void InsertSegments(const DrawSegments& segments, bool enable = true);

		//ɾ�����ƶ�
		void DeleteSegments(int offset, int count, int basevertex);
		void DeleteSegments(const DrawSegment& segment);
		void DeleteSegments(const DrawSegments& segments);
		void DeleteAllSegments() { segments_map_.clear(); }

	protected:
		DrawElements(Mode mode, int instanced_num = 1) :
			DrawCallSet(mode, instanced_num) {}

	protected:
		//���л��ƶμ�������״̬��ӳ���
		DrawSegmentsMap		segments_map_;
	};


	class DrawElementsUByte :public DrawElements
	{
	public:
		//����ʵ��
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

		//���Ƶ���
		//���ƶθ�������1ʱ�޷�ʵ������
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
		//����ʵ��
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

		//���Ƶ���
		//���ƶθ�������1ʱ�޷�ʵ������
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
		//����ʵ��
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

		//���Ƶ���
		//���ƶθ�������1ʱ�޷�ʵ������
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