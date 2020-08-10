#pragma once

#include <vector>
#include <map>

#include "DrawCallSet.h"


namespace OGE
{
	class DrawArrays :public DrawCallSet
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

		typedef std::vector<DrawSegment>	DrawSegments;
		typedef std::map<DrawSegment, bool>	DrawSegmentsMap;

		//����ʵ��
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

		//������л��ƶ�
		DrawSegmentsMap GetAllSegments() const { return segments_map_; }

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
		void SetSegmentsEnable(const DrawSegments& segments, bool enable);
		void SetAllSegmentsEnable(bool enable);

		//������ƶ�
		void InsertSegments(int first, int count, bool enable = true);
		void InsertSegments(const DrawSegment& segment, bool enable = true);
		void InsertSegments(const DrawSegments& segments, bool enable = true);

		//ɾ�����ƶ�
		void DeleteSegments(int first, int count);
		void DeleteSegments(const DrawSegment& segment);
		void DeleteSegments(const DrawSegments& segments);
		void DeleteAllSegments() { segments_map_.clear(); }

		//���Ƶ���
		//���ƶθ�������1ʱ�޷�ʵ������
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
		//���л��ƶμ�������״̬��ӳ���
		DrawSegmentsMap		segments_map_;
	};
}