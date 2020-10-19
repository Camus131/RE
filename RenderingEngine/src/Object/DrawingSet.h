#pragma once

#include "Core/Interviewee.h"


namespace OGE
{
	class DrawingSet :public Interviewee
	{
	public:
		//绘制图元模式
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

		//获得/设置图元类型
		Mode GetMode() const { return mode_; }
		void SetMode(Mode mode) { mode_ = mode; }

		//获得/设置实例化数量
		int GetInstancedNum() const { return instanced_num_; }
		void SetInstancedNum(int instanced_num) { instanced_num_ = instanced_num; }

	protected:
		DrawingSet(Mode mode = TRIANGLES, int instanced_num = 1) :
			Interviewee(),
			mode_(mode),
			instanced_num_(instanced_num) {}

	protected:
		//图元类型
		Mode	mode_;

		//实例化数量
		int		instanced_num_;
	};
}