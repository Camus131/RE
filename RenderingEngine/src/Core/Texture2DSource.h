#pragma once

#include "ContextObject.h"

#include "../Object/Texture2D.h"


namespace OGE
{
	class Texture2DSource :public ContextObject
	{
	public:
		//创建实例
		static SPtr(Texture2DSource) Create(SPtr(Texture2D) texture)
		{
			return SPtr(Texture2DSource)(new Texture2DSource(texture));
		}

		~Texture2DSource() { glDeleteTextures(1, &id_); }

		void Bind() const 
		{ 
			glActiveTexture(Texture::Unit::TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, id_); 
		}

		void Bind(int unit) const
		{
			glActiveTexture(Texture::Unit::TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, id_);
		}

		void UnBind() const { glBindTexture(GL_TEXTURE_2D, 0); }

		//获得Texture2D
		SPtr(Texture2D) GetTexture2D() const { return texture_; }

	protected:
		Texture2DSource(SPtr(Texture2D) texture);

		void CreateTexture2D(SPtr(Texture2D) texture);

	protected:
		SPtr(Texture2D)		texture_;
	};
}