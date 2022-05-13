#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "vision/include/ImageFilter.h"

#include "ObjModel.h"
#include "Mesh.h"

using tigl::Vertex;

// #pragma comment(lib, "glfw3.lib")
// #pragma comment(lib, "glew32s.lib")
// #pragma comment(lib, "opengl32.lib")

GLFWwindow *window;

void init();

void update();

void draw();

std::string str =  "../resource/models/suzanne.obj";

ObjModel objModel = ObjModel(str);
Mesh* mesh = new Mesh(&objModel);

int main()
{
    ImageFilter* filter = new ImageFilter();
    filter->filter_image();

    if (!glfwInit())
        throw "Could not initialize glwf";
    //window = glfwCreateWindow(1400, 800, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    tigl::init();
    init();

    std::cout << objModel.toString();

    while (!glfwWindowShouldClose(window))
    {
        update();
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}


void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });
}


void update()
{
}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float width = 1400;
    float height = 800;

    tigl::shader->setProjectionMatrix(
            glm::perspective(glm::radians(70.0f), width / height, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(
            glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

    mesh->DrawMesh();

    tigl::end();
}