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

		//获得包围盒
		BoundingBox GetBoundingBox() const { return bounding_box_; }

		//获得/设置渲染状态
		SPtr(State) GetState() const { return state_; }
		void SetState(SPtr(State) state) { state_ = state; }

		//获得父节点信息
		unsigned int GetParentsNum() const { return parents_.size(); }
		SPtr(Group) GetParent(unsigned int i) const { return parents_[i]; }

	protected:
		Node() :
			Interviewee(),
			mask_(0) {}

		//更新包围盒
		virtual void UpdateBox() = 0;

	protected:
		//节点包围盒
		BoundingBox		bounding_box_;

		//节点渲染状态
		SPtr(State)		state_;

		typedef std::vector<SPtr(Group)> ParentsList;
		//父节点列表
		ParentsList		parents_;

		//标记
		int				mask_;
		Matrix			transfer_;
	};
}