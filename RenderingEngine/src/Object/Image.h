#pragma once

#include "Core/Interviewee.h"


namespace OGE
{
	class Image :public Interviewee
	{
	public:
		//创建实例
		static SPtr(Image) Create(const std::string& path, bool reverse_yaxis = true)
		{
			return SPtr(Image)(new Image(path, reverse_yaxis));
		}

		~Image();

		SPtr(Image) Copy() const { return SPtr(Image)(new Image(path_, reverse_yaxis_)); }

		//重新加载图片（覆盖先前的）
		void Reload(const std::string& path, bool reverse_yaxis = true);

		const unsigned char* Data() const { return data_; }
		std::string Path() const { return path_; }
		int Width() const { return width_; }
		int Height() const { return height_; }
		int NrChannels() const { return nr_channels_; }

	protected:
		Image(const std::string& path, bool reverse_yaxis = true);

		//加载图像
		void Load();

		//卸载图像
		void Uninst();

	protected:
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
		//y轴反转
		bool			reverse_yaxis_;
	};
}