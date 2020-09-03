#include "Texture2DSource.h"


namespace OGE
{
	Texture2DSource::Texture2DSource(SPtr(Texture2D) texture) :
		ContextObject()
	{
		name_ = "Texture2DSource";
		glGenTextures(1, &id_);
		CreateTexture2D(texture);
	}


	void Texture2DSource::CreateTexture2D(SPtr(Texture2D) texture)
	{
		if (texture == nullptr || texture->GetImage() == nullptr || texture->GetImage()->Data() == nullptr)
			return;

		texture_ = texture;

		glBindTexture(GL_TEXTURE_2D, id_);
		glTexParameteri(GL_TEXTURE_2D, Texture::WrapDir::WRAP_S, texture_->GetWrapMode(Texture::WrapDir::WRAP_S));
		glTexParameteri(GL_TEXTURE_2D, Texture::WrapDir::WRAP_T, texture_->GetWrapMode(Texture::WrapDir::WRAP_T));
		glTexParameteri(GL_TEXTURE_2D, Texture::FilterChance::MIN_FILTER, texture_->GetFilterMode(Texture::FilterChance::MIN_FILTER));
		glTexParameteri(GL_TEXTURE_2D, Texture::FilterChance::MAG_FILTER, texture_->GetFilterMode(Texture::FilterChance::MAG_FILTER));
		glTexImage2D(GL_TEXTURE_2D, texture_->GetMipMapLevel(), texture_->GetInternalFormat(),
			texture_->GetWidth(), texture_->GetHeight(), 0,
			texture_->GetFormat(), texture_->GetType(), texture_->GetImage()->Data());
		if (texture_->GetMipMapEnable())
			glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}