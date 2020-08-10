#pragma once

#include "Texture.h"
#include "Image.h"


namespace OGE
{
	class Texture2D :public Texture
	{
	public:
		//创建实例
		static SPtr(Texture2D) Create()
		{
			return SPtr(Texture2D)(new Texture2D);
		}

		~Texture2D() { glDeleteTextures(1, &id_); }

		void Bind() const 
		{ 
			glActiveTexture(Unit::TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, id_); 
		}

		void Bind(int unit) const
		{
			glActiveTexture(Unit::TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, id_);
		}

		void UnBind() const { glBindTexture(GL_TEXTURE_2D, 0); }

		//更新纹理
		void Update();
		void Update(SPtr(Image) image);
		void Update(const unsigned char* const data);

	private:
		Texture2D() :
			Texture()
		{
			glGenTextures(1, &id_);
		};
	};
}