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

int main()
{
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }

    //tigl::init();

    std::string str = "D:\\proftaak\\resources\\box.obj";

    ObjModel objModel = ObjModel(str);

    for(auto face : objModel.faces) {
        std::cout << face.toString();
    }
//    Scene scene;
//    GameObject gameObject;
//
//    std::vector<Vertex> vertices;

//    for(auto position : objModel.positions){
//        for(auto normal : objModel.normals)
//        {
//            Vertex vertex;
//            vertex.Normal = normal;
//            vertex.Position = position;
//
//            vertices.push_back(vertex);
//        }
//    }

//    auto* mesh = new Mesh(vertices, objModel.faces)
//            gameObject.AddComponent();
//    scene.AddGameObject(gameObject);

    while (!glfwWindowShouldClose(window))
    {

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}
