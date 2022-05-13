#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "Scene.h"
#include "LerpController.h"
#include "SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GameObject.h>
#include <Mesh.h>

#include "ObjModel.h"

// #pragma comment(lib, "glfw3.lib")
// #pragma comment(lib, "glew32s.lib")
// #pragma comment(lib, "opengl32.lib")

GLFWwindow *window;

void init();

void update();

void draw();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, NULL);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    tigl::init();

    Scene scene;
    GameObject gameObject;
    Mesh* mesh = new Mesh("D:\\proftaak\\resources\\box.obj");
    gameObject.AddComponent(mesh);
    while (!glfwWindowShouldClose(window))
    {
        // render
        mesh->DrawMesh();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}
