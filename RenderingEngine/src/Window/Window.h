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

	//����Ⱦ��
	void BindRenderer(SPtr(OGE::Renderer) renderer) { renderer_ = renderer; }

	void Run();

protected:
	Window();

	void Init();

	//����true��ʾ���ڿ���
	bool IsActive() const { return window_ != nullptr; }

	//���ڴ�С�仯�ص�
	static void SizeChangeCallback(GLFWwindow* window, int width, int height);

	//���ص�
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	//���ֻص�
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	//���봦��
	static void ProcessInput(GLFWwindow* window);

protected:
	//������Դ����
	GLFWwindow*					window_;

	//��
	static	int					width_;

	//��
	static	int					height_;

	//��Ⱦ��
	static	SPtr(OGE::Renderer)	renderer_;
};