#pragma once

#include <string>

#include "Header.h"


namespace OGE
{
	class Image :public Object
	{
	public:
		//创建实例
		static SPtr(Image) Create(const std::string& path, bool reverse_yaxis = true)
		{
			return SPtr(Image)(new Image(path));
		}

		~Image();

		//重新加载图片（覆盖先前的）
		void Reload(const std::string& path, bool reverse_yaxis = true);

		//返回true表示有图像数据
		bool IsActive() const { return data_ ? true : false; }

		const unsigned char* Data() const { return data_; }
		std::string Path() const { return path_; }
		int Width() const { return width_; }
		int Height() const { return height_; }
		int NrChannels() const { return nr_channels_; }

	private:
		Image(const std::string& path, bool reverse_yaxis = true);

		//卸载图像
		void Delete();

	private:
		//数据
		unsigned char*	data_;

		//路径
		std::string		path_;

		//宽
		int				width_;

		//高
		int				height_;

		//颜色通道个数
		int				nr_channels_;
	};
}