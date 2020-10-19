#include "Texture2D.h"


namespace OGE
{
	Texture2D::Texture2D(SPtr(Image) image) :
		Texture()
	{
		name_ = OGE_Texture2D;
		image_list_.emplace_back(nullptr);
		SetImage(image);
	}


	SPtr(Texture2D) Texture2D::Copy() const
	{
		SPtr(Texture2D) tex2d = SPtr(Texture2D)(new Texture2D);
		tex2d->parameter_list_.s_wrap_ = parameter_list_.s_wrap_;
		tex2d->parameter_list_.t_wrap_ = parameter_list_.t_wrap_;
		tex2d->parameter_list_.r_wrap_ = parameter_list_.r_wrap_;
		tex2d->parameter_list_.min_filter_ = parameter_list_.min_filter_;
		tex2d->parameter_list_.mag_filter_ = parameter_list_.mag_filter_;
		tex2d->parameter_list_.mipmap_enable_ = parameter_list_.mipmap_enable_;
		tex2d->parameter_list_.mipmap_level_ = parameter_list_.mipmap_level_;
		tex2d->parameter_list_.internal_format_ = parameter_list_.internal_format_;
		tex2d->parameter_list_.format_ = parameter_list_.format_;
		tex2d->parameter_list_.type_ = parameter_list_.type_;
		tex2d->parameter_list_.width_ = parameter_list_.width_;
		tex2d->parameter_list_.height_ = parameter_list_.height_;
		tex2d->image_list_ = image_list_;
		return tex2d;
	}


	void Texture2D::SetImage(SPtr(Image) image)
	{
		if (image == nullptr || image->Data() == nullptr)
			return;

		image_list_[0] = image;

		switch (image_list_[0]->NrChannels())
		{
		case 1:
			parameter_list_.format_ = Format::RED;
			break;
		case 2:
			parameter_list_.format_ = Format::RG;
			break;
		case 3:
			parameter_list_.format_ = Format::RGB;
			break;
		case 4:
			parameter_list_.format_ = Format::RGBA;
			break;
		}
		parameter_list_.type_ = Type::UNSIGNED_BYTE;
		parameter_list_.width_ = image_list_[0]->Width();
		parameter_list_.height_ = image_list_[0]->Height();
	}
}