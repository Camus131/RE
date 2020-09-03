#pragma once

#include "Texture.h"


namespace OGE
{
	class Texture2D :public Texture
	{
	public:
		//创建实例
		static SPtr(Texture2D) Create(SPtr(Image) image = nullptr)
		{
			return SPtr(Texture2D)(new Texture2D(image));
		}

		SPtr(Texture2D) Copy() const;

		//获得/设置图像
		SPtr(Image) GetImage() const;
		void SetImage(SPtr(Image) image);

	protected:
		Texture2D(SPtr(Image) image = nullptr);
	};
}