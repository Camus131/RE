#include "Transform.h"


namespace OGE
{
	void Transform::UpdateBox()
	{
		BoundingBox box;
		for (int i = 0; i < children_.size(); ++i)
			box.ExpandBy(children_[i]->bounding_box_);

		box.Transform(matrix_);

		if (bounding_box_ == box)
			return;

		bounding_box_ = box;
		for (int i = 0; i < parents_.size(); ++i)
			parents_[i]->UpdateBox();
	}
}