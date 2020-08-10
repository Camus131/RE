#include "Image.h"

#include "../ThirdParty/stb_image.h"


namespace OGE
{
	Image::Image(const std::string& path, bool reverse_yaxis) :
		Object()
	{
		if (reverse_yaxis)
			stbi_set_flip_vertically_on_load(true);
		path_ = path;
		data_ = stbi_load(path.c_str(), &width_, &height_, &nr_channels_, 0);
	}


	Image::~Image()
	{
		Delete();
	}


	void Image::Reload(const std::string& path, bool reverse_yaxis)
	{
		Delete();
		if (reverse_yaxis)
			stbi_set_flip_vertically_on_load(true);
		path_ = path;
		data_ = stbi_load(path.c_str(), &width_, &height_, &nr_channels_, 0);
	}


	void Image::Delete()
	{
		if (data_)
		{
			stbi_image_free(data_);
			data_ = nullptr;
			path_ = "";
			width_ = 0;
			height_ = 0;
			nr_channels_ = 0;
		}
	}
}