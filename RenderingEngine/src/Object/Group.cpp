#include "Group.h"


namespace OGE
{
	void Group::AddChild(SPtr(Node) child)
	{
		for (int i = 0; i < children_.size(); ++i)
		{
			if (children_[i] == child)
				return;
		}
		child->parents_.emplace_back(SPtrCast(Group, Self()));
		children_.emplace_back(child);
		UpdateBox();
	}


	void Group::RemoveChild(SPtr(Node) child)
	{
		for (auto iter_child = children_.begin(); iter_child != children_.end(); ++iter_child)
		{
			if (*iter_child == child)
			{
				for (auto iter_parent = child->parents_.begin(); iter_parent != child->parents_.end(); ++iter_parent)
				{
					if (*iter_parent == SPtrCast(Group, Self()))
					{
						child->parents_.erase(iter_parent);
						break;
					}
				}
				children_.erase(iter_child);
				UpdateBox();
				return;
			}
		}
	}


	void Group::UpdateBox()
	{
		BoundingBox box;
		for (int i = 0; i < children_.size(); ++i)
			box.ExpandBy(children_[i]->bounding_box_);

		if (bounding_box_ == box)
			return;

		bounding_box_ = box;
		for (int i = 0; i < parents_.size(); ++i)
			parents_[i]->UpdateBox();
	}
}