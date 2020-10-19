#pragma once

#include "Core/Renderer.h"

#include <GLFW/glfw3.h>


class Window
{
public:
	static Window GetInstance()
	{
		static Window window;
		return window;
	}

	~Window() { glfwTerminate(); }

	//绑定渲染器
	void BindRenderer(SPtr(OGE::Renderer) renderer) { renderer_ = renderer; }

	void Run();

protected:
	Window();

	void Init();

	//返回true表示窗口可用
	bool IsActive() const { return window_ != nullptr; }

	//窗口大小变化回调
	static void SizeChangeCallback(GLFWwindow* window, int width, int height);

	//鼠标回调
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	//滚轮回调
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	//输入处理
	static void ProcessInput(GLFWwindow* window);

protected:
	//窗口资源对象
	GLFWwindow*					window_;

	//宽
	static	int					width_;

	//高
	static	int					height_;

	//渲染器
	static	SPtr(OGE::Renderer)	renderer_;
};