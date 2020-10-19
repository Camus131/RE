#include "Cube.h"
#include "Group.h"


namespace OGE
{
	Cube::Cube(const Vec3& center, value_type x, value_type y, value_type z, bool uv_enable) :
		Leaf(),
		center_(center),
		x_(x),
		y_(y),
		z_(z),
		uv_enable_(uv_enable)
	{
		name_ = OGE_Cube;
		UpdateBox();
	}


	void Cube::SetCenter(const Vec3& center)
	{
		if (center_ == center)
			return;

		center_ = center;
		UpdateBox();
	}


	void Cube::SetX(value_type x)
	{
		if (x_ == x)
			return;

		x_ = x;
		UpdateBox();
	}


	void Cube::SetY(value_type y)
	{
		if (y_ == y)
			return;

		y_ = y;
		UpdateBox();
	}


	void Cube::SetZ(value_type z)
	{
		if (z_ == z)
			return;

		z_ = z;
		UpdateBox();
	}


	void Cube::UpdateBox()
	{
		BoundingBox box;
		Vec3 half_diagonal(x_ * 0.5f, y_ * 0.5f, z_ * 0.5f);
		box.Set(center_ - half_diagonal, center_ + half_diagonal);

		if (bounding_box_ == box)
			return;

		bounding_box_ = box;
		for (int i = 0; i < parents_.size(); ++i)
			parents_[i]->UpdateBox();
	}
}