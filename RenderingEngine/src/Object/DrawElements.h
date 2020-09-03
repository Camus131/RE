#pragma once

#include "DrawingSet.h"


namespace OGE
{
	class DrawElements :public DrawingSet
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
		typedef std::map<DrawSegment, bool>	DrawSegments;

		//������л��ƶ�
		DrawSegments GetAllSegments() const { return segments_map_; }

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
		void SetAllSegmentsEnable(bool enable);

		//������ƶ�
		void AddSegments(int offset, int count, int basevertex, bool enable = true);
		void AddSegments(const DrawSegment& segment, bool enable = true);

		//ɾ�����ƶ�
		void RemoveSegments(int offset, int count, int basevertex);
		void RemoveSegments(const DrawSegment& segment);
		void RemoveAllSegments() { segments_map_.clear(); }

	protected:
		DrawElements(Mode mode = POINTS, int instanced_num = 1) :
			DrawingSet(mode, instanced_num) {}

	protected:
		//���л��ƶμ�������״̬��ӳ���
		DrawSegments		segments_map_;
	};


	class DrawElementsUByte :public DrawElements
	{
	public:
		typedef unsigned char value_type;

		//����ʵ��
		static SPtr(DrawElementsUByte) Create(Mode mode, int instanced_num = 1)
		{
			return SPtr(DrawElementsUByte)(new DrawElementsUByte(mode, instanced_num));
		}
		static SPtr(DrawElementsUByte) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUByte)(new DrawElementsUByte(mode, offset, count, basevertex, enable, instanced_num));
		}

		SPtr(DrawElementsUByte) Copy() const;

		//���/������������
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

		//����ʵ��
		static SPtr(DrawElementsUShort) Create(Mode mode, int instanced_num = 1)
		{
			return SPtr(DrawElementsUShort)(new DrawElementsUShort(mode, instanced_num));
		}
		static SPtr(DrawElementsUShort) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUShort)(new DrawElementsUShort(mode, offset, count, basevertex, enable, instanced_num));
		}

		SPtr(DrawElementsUShort) Copy() const;

		//���/������������
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

		//����ʵ��
		static SPtr(DrawElementsUInt) Create(Mode mode, int instanced_num = 1)
		{
			return SPtr(DrawElementsUInt)(new DrawElementsUInt(mode, instanced_num));
		}
		static SPtr(DrawElementsUInt) Create(Mode mode, int offset, int count, int basevertex = 0, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawElementsUInt)(new DrawElementsUInt(mode, offset, count, basevertex, enable, instanced_num));
		}

		SPtr(DrawElementsUInt) Copy() const;

		//���/������������
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