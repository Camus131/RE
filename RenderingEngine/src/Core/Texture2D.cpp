#include "Texture2D.h"


namespace OGE
{
	void Texture2D::Update()
	{
		glBindTexture(GL_TEXTURE_2D, id_);

		glTexParameteri(GL_TEXTURE_2D, WrapDir::WRAP_S, update_parameter_list_.s_wrap_);
		parameter_list_.s_wrap_ = update_parameter_list_.s_wrap_;

		glTexParameteri(GL_TEXTURE_2D, WrapDir::WRAP_T, update_parameter_list_.t_wrap_);
		parameter_list_.t_wrap_ = update_parameter_list_.t_wrap_;

		glTexParameteri(GL_TEXTURE_2D, FilterChance::MIN_FILTER, update_parameter_list_.min_filter_);
		parameter_list_.min_filter_ = update_parameter_list_.min_filter_;

		glTexParameteri(GL_TEXTURE_2D, FilterChance::MAG_FILTER, update_parameter_list_.mag_filter_);
		parameter_list_.mag_filter_ = update_parameter_list_.mag_filter_;

		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void Texture2D::Update(SPtr(Image) image)
	{
		if (!image->IsActive())
			return;

		switch (image->NrChannels())
		{
		case 1:
			update_parameter_list_.format_ = Format::RED;
			break;
		case 2:
			update_parameter_list_.format_ = Format::RG;
			break;
		case 3:
			update_parameter_list_.format_ = Format::RGB;
			break;
		case 4:
			update_parameter_list_.format_ = Format::RGBA;
			break;
		}

		update_parameter_list_.type_ = Type::UNSIGNED_BYTE;
		update_parameter_list_.width_ = image->Width();
		update_parameter_list_.height_ = image->Height();

		Update(image->Data());
	}


	void Texture2D::Update(const unsigned char* const data)
	{
		glBindTexture(GL_TEXTURE_2D, id_);

		glTexParameteri(GL_TEXTURE_2D, WrapDir::WRAP_S, update_parameter_list_.s_wrap_);
		parameter_list_.s_wrap_ = update_parameter_list_.s_wrap_;

		glTexParameteri(GL_TEXTURE_2D, WrapDir::WRAP_T, update_parameter_list_.t_wrap_);
		parameter_list_.t_wrap_ = update_parameter_list_.t_wrap_;

		glTexParameteri(GL_TEXTURE_2D, FilterChance::MIN_FILTER, update_parameter_list_.min_filter_);
		parameter_list_.min_filter_ = update_parameter_list_.min_filter_;

		glTexParameteri(GL_TEXTURE_2D, FilterChance::MAG_FILTER, update_parameter_list_.mag_filter_);
		parameter_list_.mag_filter_ = update_parameter_list_.mag_filter_;

		glTexImage2D(GL_TEXTURE_2D, update_parameter_list_.level_, update_parameter_list_.internal_format_,
			update_parameter_list_.width_, update_parameter_list_.height_, 0,
			update_parameter_list_.format_, update_parameter_list_.type_, data);
		parameter_list_.level_ = update_parameter_list_.level_;
		parameter_list_.internal_format_ = update_parameter_list_.internal_format_;
		parameter_list_.width_ = update_parameter_list_.width_;
		parameter_list_.height_ = update_parameter_list_.height_;
		parameter_list_.format_ = update_parameter_list_.format_;
		parameter_list_.type_ = update_parameter_list_.type_;

		if (update_parameter_list_.is_enable_mipmap_)
			glGenerateMipmap(GL_TEXTURE_2D);
		parameter_list_.is_enable_mipmap_ = update_parameter_list_.is_enable_mipmap_;

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}