#include "Mesh.h"
#include "Group.h"


namespace OGE
{
	void Mesh::SetPosArray(const Vec3Array& array)
	{
		position_array_ = array;
		UpdateBox();
	}


	void Mesh::UpdateBox()
	{
		BoundingBox box;
		for (int i = 0; i < position_array_.size(); ++i)
			box.ExpandBy(position_array_[i]);

		if (bounding_box_ == box)
			return;

		bounding_box_ = box;
		for (int i = 0; i < parents_.size(); ++i)
			parents_[i]->UpdateBox();
	}
}