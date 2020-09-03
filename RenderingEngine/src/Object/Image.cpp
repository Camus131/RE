#include "Image.h"

#include "../ThirdParty/stb_image.h"


namespace OGE
{
	Image::Image(const std::string& path, bool reverse_yaxis) :
		ExternalObject()
	{
		name_ = "Image";
		path_ = path;
		reverse_yaxis_ = reverse_yaxis;
		Load();
	}


	Image::~Image()
	{
		Uninst();
	}


	void Image::Reload(const std::string& path, bool reverse_yaxis)
	{
		Uninst();
		path_ = path;
		reverse_yaxis_ = reverse_yaxis;
		Load();
	}


	void Image::Load()
	{
		if (reverse_yaxis_)
			stbi_set_flip_vertically_on_load(true);
		data_ = stbi_load(path_.c_str(), &width_, &height_, &nr_channels_, 0);
	}


	void Image::Uninst()
	{
		if (data_)
		{
			stbi_image_free(data_);
			data_ = nullptr;
		}
		path_ = "";
		width_ = 0;
		height_ = 0;
		nr_channels_ = 0;
	}
}