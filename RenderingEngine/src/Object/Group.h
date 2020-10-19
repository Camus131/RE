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

		//����ʵ��
		static SPtr(Group) Create()
		{
			return SPtr(Group)(new Group);
		}

		//����ӽڵ���Ϣ
		unsigned int GetChildrenNum() const { return children_.size(); }
		SPtr(Node) GetChild(unsigned int i) const { return children_[i]; }

		//����ӽڵ�
		void AddChild(SPtr(Node) child);

		//ɾ���ӽڵ�
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
		//�ӽڵ��б�
		ChildrenList	children_;
	};
}