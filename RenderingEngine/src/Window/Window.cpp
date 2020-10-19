#include "Window.h"

#include <iostream>


float lastX = 960.0f;
float lastY = 540.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool firstMouse = true;


int Window::width_ = 1920;
int Window::height_ = 1080;
SPtr(OGE::Renderer)	Window::renderer_ = nullptr;


Window::Window()
{
    Init();
}


void Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(width_, height_, "Window", nullptr, nullptr);

    if (window_ == nullptr)
    {
        std::cout << "´´½¨´°¿ÚÊ§°Ü£¡" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, SizeChangeCallback);
    glfwSetCursorPosCallback(window_, MouseCallback);
    glfwSetScrollCallback(window_, ScrollCallback);

    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout << "Failed to initialize GLAD" << std::endl;
}


void Window::Run()
{
    while (!glfwWindowShouldClose(window_))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(window_);

        if (renderer_ != nullptr)
            renderer_->Frame();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}


void Window::SizeChangeCallback(GLFWwindow* window, int width, int height)
{
    width_ = width;
    height_ = height;

    if (renderer_ == nullptr)
        return;

    renderer_->GetViewport()->SetWidth(width_);
    renderer_->GetViewport()->SetHeight(height_);
    renderer_->UpdateViewport();
}


void Window::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = lastX - xpos;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (renderer_ == nullptr)
        return;

    renderer_->GetCamera()->Turn(xoffset, yoffset);
}


void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (renderer_ == nullptr)
        return;

    renderer_->GetCamera()->SetFov(renderer_->GetCamera()->GetFov() + yoffset);
}


void Window::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (renderer_ == nullptr)
        return;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        renderer_->GetCamera()->Reset();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderer_->GetCamera()->Move(OGE::PerspectiveCamera::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderer_->GetCamera()->Move(OGE::PerspectiveCamera::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderer_->GetCamera()->Move(OGE::PerspectiveCamera::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderer_->GetCamera()->Move(OGE::PerspectiveCamera::RIGHT, deltaTime);
}