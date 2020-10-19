#pragma once

#include "Core/Interviewee.h"


namespace OGE
{
	class Image :public Interviewee
	{
	public:
		//����ʵ��
		static SPtr(Image) Create(const std::string& path, bool reverse_yaxis = true)
		{
			return SPtr(Image)(new Image(path, reverse_yaxis));
		}

		~Image();

		SPtr(Image) Copy() const { return SPtr(Image)(new Image(path_, reverse_yaxis_)); }

		//���¼���ͼƬ��������ǰ�ģ�
		void Reload(const std::string& path, bool reverse_yaxis = true);

		const unsigned char* Data() const { return data_; }
		std::string Path() const { return path_; }
		int Width() const { return width_; }
		int Height() const { return height_; }
		int NrChannels() const { return nr_channels_; }

	protected:
		Image(const std::string& path, bool reverse_yaxis = true);

		//����ͼ��
		void Load();

		//ж��ͼ��
		void Uninst();

	protected:
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
		//y�ᷴת
		bool			reverse_yaxis_;
	};
}