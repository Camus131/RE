#pragma once

#include "Node.h"


namespace OGE
{
	class Group :public Node
	{
	public:
		friend class Cube;
		friend class Mesh;
		friend class Transform;
		friend class NodeVisitor;

		//创建实例
		static SPtr(Group) Create()
		{
			return SPtr(Group)(new Group);
		}

		//获得子节点信息
		unsigned int GetChildrenNum() const { return children_.size(); }
		SPtr(Node) GetChild(unsigned int i) const { return children_[i]; }

		//添加子节点
		void AddChild(SPtr(Node) child);

		//删除子节点
		void RemoveChild(SPtr(Node) child);

	protected:
		Group() :
			Node()
		{
			name_ = OGE_Group;
		}

		virtual void UpdateBox();

	protected:
		typedef std::vector<SPtr(Node)> ChildrenList;
		//子节点列表
		ChildrenList	children_;
	};
}