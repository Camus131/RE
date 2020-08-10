#pragma once

#include <string>

#include "Header.h"


namespace OGE
{
	class Image :public Object
	{
	public:
		//����ʵ��
		static SPtr(Image) Create(const std::string& path, bool reverse_yaxis = true)
		{
			return SPtr(Image)(new Image(path));
		}

		~Image();

		//���¼���ͼƬ��������ǰ�ģ�
		void Reload(const std::string& path, bool reverse_yaxis = true);

		//����true��ʾ��ͼ������
		bool IsActive() const { return data_ ? true : false; }

		const unsigned char* Data() const { return data_; }
		std::string Path() const { return path_; }
		int Width() const { return width_; }
		int Height() const { return height_; }
		int NrChannels() const { return nr_channels_; }

	private:
		Image(const std::string& path, bool reverse_yaxis = true);

		//ж��ͼ��
		void Delete();

	private:
		//����
		unsigned char*	data_;

		//·��
		std::string		path_;

		//��
		int				width_;

		//��
		int				height_;

		//��ɫͨ������
		int				nr_channels_;
	};
}