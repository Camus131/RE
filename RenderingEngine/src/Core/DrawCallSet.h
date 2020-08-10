#pragma once

#include "glad/glad.h"

#include "Header.h"


namespace OGE
{
	class DrawCallSet :public Object
	{
	public:
		//����ͼԪģʽ
		enum Mode
		{
			POINTS = GL_POINTS,
			LINES = GL_LINES,
			LINE_LOOP = GL_LINE_LOOP,
			LINE_STRIP = GL_LINE_STRIP,
			TRIANGLES = GL_TRIANGLES,
			TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
			TRIANGLE_FAN = GL_TRIANGLE_FAN,
			QUADS = GL_QUADS,
		};

		//���/����ͼԪ����
		Mode GetMode() const { return mode_; }
		void SetMode(Mode mode) { mode_ = mode; }

		//���/����ʵ��������
		int GetInstancedNum() const { return instanced_num_; }
		void SetInstancedNum(int instanced_num) { instanced_num_ = instanced_num; }

		//����API����
		virtual void Draw() const = 0;

	protected:
		//��ֹ�ⲿ��������
		DrawCallSet(Mode mode, int instanced_num = 1) :
			Object(),
			mode_(mode),
			instanced_num_(instanced_num) {}

	protected:
		//ͼԪ����
		Mode	mode_;

		//ʵ��������
		int		instanced_num_;
	};
}