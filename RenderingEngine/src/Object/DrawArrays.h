#pragma once

#include "DrawingSet.h"


namespace OGE
{
	class DrawArrays :public DrawingSet
	{
	public:
		//���ƶ�
		struct DrawSegment
		{
			//������ʼ����
			int First;
			//���ƶ������
			int Count;

			DrawSegment(int first, int count) :
				First(first), Count(count) {}

			bool operator < (const DrawSegment& segment) const { return First < segment.First; }
		};
		typedef std::map<DrawSegment, bool>	DrawSegments;

		//����ʵ��
		static SPtr(DrawArrays) Create(Mode mode,int instanced_num = 1)
		{
			return SPtr(DrawArrays)(new DrawArrays(mode, instanced_num));
		}
		static SPtr(DrawArrays) Create(Mode mode, int first, int count, bool enable = true, int instanced_num = 1)
		{
			return SPtr(DrawArrays)(new DrawArrays(mode, first, count, enable, instanced_num));
		}

		SPtr(DrawArrays) Copy() const;

		//������л��ƶ�
		DrawSegments GetAllSegments() const { return segments_map_; }

		//������л��ƶθ���
		int NumOfAllSegments() const { return segments_map_.size(); }

		//������û��ƶθ���
		int NumOfEnableSegments() const;

		//���ĳ�����ƶ�����״̬
		//1�������ã�0����δ���ã�-1������ȡʧ��
		int GetSegmentEnable(int first, int count) const;
		int GetSegmentEnable(const DrawSegment& segment) const;

		//���û��ƶ�����״̬
		void SetSegmentsEnable(int first, int count, bool enable);
		void SetSegmentsEnable(const DrawSegment& segment, bool enable);
		void SetAllSegmentsEnable(bool enable);

		//��ӻ��ƶ�
		void AddSegments(int first, int count, bool enable = true);
		void AddSegments(const DrawSegment& segment, bool enable = true);

		//ɾ�����ƶ�
		void RemoveSegments(int first, int count);
		void RemoveSegments(const DrawSegment& segment);
		void RemoveAllSegments() { segments_map_.clear(); }

	protected:
		DrawArrays(Mode mode, int instanced_num = 1);
		DrawArrays(Mode mode, int first, int count, bool enable = true, int instanced_num = 1);

	protected:
		//���л��ƶμ�������״̬��ӳ���
		DrawSegments		segments_map_;
	};
}