#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "Scene.h"
#include "LerpController.h"
#include "SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GameObject.h>

#include "ObjModel.h"

using tigl::Vertex;

// #pragma comment(lib, "glfw3.lib")
// #pragma comment(lib, "glew32s.lib")
// #pragma comment(lib, "opengl32.lib")

GLFWwindow *window;

void init();

void update();

void draw();

int main()
{
    glm::vec3 test;
    Scene scene;
    GameObject gameObject;
    auto *lerpController = new LerpController;
    gameObject.AddComponent(lerpController);
    scene.AddGameObject(gameObject);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    tigl::init();
    init();

    std::string str = "../resource/models/suzanne.obj";

    ObjModel henk = ObjModel(str);

    for (int i = 0; i < henk.faces.size(); ++i)
    {
        std::cout << henk.faces[i].toString()  << std::endl;
    }




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
