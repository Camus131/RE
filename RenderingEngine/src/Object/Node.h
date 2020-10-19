#pragma once

#include "State.h"
#include "Math/BoundingBoxf.h"


namespace OGE
{
	class Group;

	class Node :public Interviewee
	{
	public:
		friend class Group;
		friend class Transform;
		friend class NodeVisitor;

		//��ð�Χ��
		BoundingBox GetBoundingBox() const { return bounding_box_; }

		//���/������Ⱦ״̬
		SPtr(State) GetState() const { return state_; }
		void SetState(SPtr(State) state) { state_ = state; }

		//��ø��ڵ���Ϣ
		unsigned int GetParentsNum() const { return parents_.size(); }
		SPtr(Group) GetParent(unsigned int i) const { return parents_[i]; }

	protected:
		Node() :
			Interviewee(),
			mask_(0) {}

		//���°�Χ��
		virtual void UpdateBox() = 0;

	protected:
		//�ڵ��Χ��
		BoundingBox		bounding_box_;

		//�ڵ���Ⱦ״̬
		SPtr(State)		state_;

		typedef std::vector<SPtr(Group)> ParentsList;
		//���ڵ��б�
		ParentsList		parents_;

		//���
		int				mask_;
		Matrix			transfer_;
	};
}