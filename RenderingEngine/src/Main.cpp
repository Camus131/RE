#pragma comment(lib,"glad/glad64.lib")
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Math/Vec3d.h"
#include "Math/Matrixd.h"
#include "Math/EulerAngles.h"
#include "Core/VertexBuffer.h"
#include "Core/Shader.h"
#include "Core/DrawArrays.h"
#include "Core/DrawElements.h"
#include "Core/VertexArray.h"
#include "Core/Texture2D.h"
#include "Scene/FPSCamera.h"


#include <iostream>

using namespace OGE;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;


//Па»ъ
FPSCamera camera(Vec3(0.0f, 0.5f, 4.0f), Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float deltaTime = 0.0f;	
float lastFrame = 0.0f;
bool firstMouse = true;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rendering Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    //verterx data
    float vertices[] =
    {
        //positions           //normals            //texcoords
        -0.5f,  0.0f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f,  0.0f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  1.0f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  1.0f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

        -0.5f,  0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  1.0f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  1.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

        -0.5f,  1.0f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  1.0f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f,  0.0f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.0f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

         0.5f,  1.0f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  1.0f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.0f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.0f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

        -0.5f,  0.0f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.0f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.0f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.0f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

        -0.5f,  1.0f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  1.0f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  1.0f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  1.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    };

    unsigned char indices[] =
    {
        0,1,2,
        2,3,0,
        4,5,6,
        6,7,4,
        8,9,10,
        10,11,8,
        12,13,14,
        14,15,12,
        16,17,18,
        18,19,16,
        20,21,22,
        22,23,20
    };

    SPtr(VBO) vbo_0 = VBO::Create(vertices, 192, sizeof(vertices));

    SPtr(EBO_UByte) ebo_0 = EBO_UByte::Create(indices, 36, sizeof(indices));

    SPtr(VAO) vao_0 = VAO::Create();
    vao_0->Bind();
    vao_0->BindEBO(ebo_0);
    vao_0->BindVBO(vbo_0);
    vao_0->EnableSetAttrib(0, 3, 8, 0);
    vao_0->EnableSetAttrib(1, 3, 8, 3);
    vao_0->EnableSetAttrib(2, 2, 8, 6);
    vao_0->UnBind();

    SPtr(VAO) vao_2 = VAO::Create();
    vao_2->Bind();
    vao_2->BindEBO(ebo_0);
    vao_2->BindVBO(vbo_0);
    vao_2->EnableSetAttrib(0, 3, 8, 0);
    vao_2->UnBind();

    float vertices_ground[] =
    {
        //positions           //texcoords
         0.5f,  0.0f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.0f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.0f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.0f, -0.5f,  0.0f, 1.0f,
    };

    SPtr(VBO) vbo_1 = VBO::Create(vertices_ground, 20, sizeof(vertices_ground));

    SPtr(VAO) vao_1 = VAO::Create();
    vao_1->Bind();
    vao_1->BindVBO(vbo_1);
    vao_1->EnableSetAttrib(0, 3, 5, 0);
    vao_1->EnableSetAttrib(1, 2, 5, 3);
    vao_1->UnBind();

    //shaders
    SPtr(Shader) shader_0 = Shader::Create("res/shaders/vs_light.vs", "res/shaders/fs_light.fs");
    shader_0->Bind();
    shader_0->SetUniform("light.position", Vec3(-3.0f, 3.0f, 0.0f));
    shader_0->SetUniform("light.ambient", Vec3(0.2f, 0.2f, 0.2f));
    shader_0->SetUniform("light.diffuse", Vec3(0.8f, 0.8f, 0.8f));
    shader_0->SetUniform("light.specular", Vec3(1.0f, 1.0f, 1.0f));
    shader_0->SetUniform("material.shininess", 64.0f);
    shader_0->SetUniform("material.diffuse", 0);
    shader_0->SetUniform("material.specular", 2);
    shader_0->UnBind();

    SPtr(Shader) shader_1 = Shader::Create("res/shaders/vs_0.vs", "res/shaders/fs_0.fs");
    shader_1->Bind();
    shader_1->SetUniform("texture0", 1);
    shader_1->UnBind();

    SPtr(Shader) shader_2 = Shader::Create("res/shaders/vs_1.vs", "res/shaders/fs_1.fs");

    //textures
    SPtr(Image) image_0 = Image::Create("res/textures/container2.png");
    SPtr(Texture2D) texture_0 = Texture2D::Create();
    texture_0->SetFilterMode(Texture::FilterChance::MIN_FILTER, Texture::FilterMode::LINEAR);
    texture_0->SetFilterMode(Texture::FilterChance::MAG_FILTER, Texture::FilterMode::LINEAR);
    texture_0->SetMipMapEnable(true);
    texture_0->SetInternalFormat(Texture2D::Format::RGBA);
    texture_0->Update(image_0);

    SPtr(Image) image_1 = Image::Create("res/textures/timg.jpg");
    SPtr(Texture2D) texture_1 = Texture2D::Create();
    texture_1->SetFilterMode(Texture::FilterChance::MIN_FILTER, Texture::FilterMode::LINEAR);
    texture_1->SetFilterMode(Texture::FilterChance::MAG_FILTER, Texture::FilterMode::LINEAR);
    texture_1->SetMipMapEnable(true);
    texture_1->SetInternalFormat(Texture2D::Format::RGB);
    texture_1->Update(image_1);

    SPtr(Image) image_2 = Image::Create("res/textures/container2_specular.png");
    SPtr(Texture2D) texture_2 = Texture2D::Create();
    texture_2->SetFilterMode(Texture::FilterChance::MIN_FILTER, Texture::FilterMode::LINEAR);
    texture_2->SetFilterMode(Texture::FilterChance::MAG_FILTER, Texture::FilterMode::LINEAR);
    texture_2->SetMipMapEnable(true);
    texture_2->SetInternalFormat(Texture2D::Format::RGBA);
    texture_2->Update(image_2);

    //drawcalls
    SPtr(DrawElementsUByte) drawcall_0 = DrawElementsUByte::Create(DrawCallSet::Mode::TRIANGLES, 0, 36);
    SPtr(DrawArrays) drawcall_1 = DrawArrays::Create(DrawCallSet::Mode::TRIANGLE_STRIP, 0, 4);



    texture_0->Bind();
    texture_1->Bind(1);
    texture_2->Bind(2);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.8f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_0->Bind();
        shader_0->SetUniform("projection", Matrix::Perspective(camera.GetFov(), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));
        shader_0->SetUniform("view", camera.ViewMatrix());
        shader_0->SetUniform("viewPos", camera.GetPosition());


        vao_0->Bind();
        Matrix model_0;
        shader_0->SetUniform("model", model_0);
        shader_0->SetUniform("normal_model", model_0);
        drawcall_0->Draw();
        Matrix model_1 = Matrix::Translate(3.0f, 0.0f, 0.0f);
        shader_0->SetUniform("model", model_1);
        model_1.MakeInverse();
        shader_0->SetUniform("normal_model", Matrix::Transpose(model_1));
        drawcall_0->Draw();
        Matrix model_2 = Matrix::Translate(0.0f, 0.0f, 2.0f);
        shader_0->SetUniform("model", model_2);
        model_2.MakeInverse();
        shader_0->SetUniform("normal_model", Matrix::Transpose(model_2));
        drawcall_0->Draw();

        shader_1->Bind();
        shader_1->SetUniform("projection", Matrix::Perspective(camera.GetFov(), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));
        shader_1->SetUniform("view", camera.ViewMatrix());

        vao_1->Bind();

        for (int i = -5; i < 5; ++i)
        {
            for (int j = -5; j < 5; ++j)
            {
                shader_1->SetUniform("model", Matrix::Translate(i, -0.01f, j));
                drawcall_1->Draw();
            }
        }


        shader_2->Bind();
        shader_2->SetUniform("projection", Matrix::Perspective(camera.GetFov(), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));
        shader_2->SetUniform("view", camera.ViewMatrix());
        shader_2->SetUniform("model", Matrix::Translate(-3.0f, 3.0f, 0.0f) * Matrix::Scale(0.05f, 0.05f, 0.05f));
        vao_2->Bind();
        drawcall_0->Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::cout << "fps::" << 1.0f / deltaTime << std::endl;
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.Reset();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.Move(FPSCamera::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Move(FPSCamera::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Move(FPSCamera::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Move(FPSCamera::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

    camera.Turn(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.SetFov(camera.GetFov() + yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}