#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <tigl.h>
#include <opencv2/highgui.hpp>
#include <memory>

#include "ObjModel.h"
#include "Mesh.h"
#include "ModelManager.h"
#include "OpenCVVideoCapture.h"
#include "Scene.h"
#include "SceneManager.h"
//#include "VirtualCamera.h"
#include "Transform.h"
#include "LerpController.h"

// set camera id of camera you want to use
#define CAMERA_ID 1

using tigl::Vertex;

GLFWwindow *window;

std::shared_ptr<cv::VideoCapture> capture;
OpenCVVideoCapture *openCvComponent;

void init();

void update();

void draw();

void worldInit();

Scene *scene;

//aspect ratio should always be 4:3 when using realsense camera
const int windowWidth = 1440;
const int windowHeight = 1080;

//VirtualCamera* virtualCamera;
int main()
{
    if (!glfwInit())
        throw "Could not initialize glwf";

    window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    //test

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    tigl::init();
    init();
    worldInit();


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

    // Init OpenCV
    capture = std::make_shared<cv::VideoCapture>(CAMERA_ID);

    openCvComponent = new OpenCVVideoCapture(capture);
    openCvComponent->Awake();
}

void worldInit()
{
    std::string str = "../resource/models/grids.obj";
    scene = new Scene();
    auto levelGO = new GameObject();
    auto levelMesh = new Mesh(ModelManager::getModel(str));
    levelGO->AddComponent(levelMesh);
    scene->AddGameObject(levelGO);
    LerpController *test1;

    if (levelGO->TryFindComponent<LerpController>(test1))
    {
        auto test2 = *test1;
    }

    //auto testFind = levelGO->FindComponent<Mesh>();
//    GameObject *suzanne = new GameObject();
//    ObjModel *_objmodel = ModelManager::getModel(str);
//    Mesh *meshComponent = new Mesh(_objmodel);
//    LerpController* lerpController = new LerpController();
//    suzanne->AddComponent(meshComponent);
//    suzanne->AddComponent(lerpController);
//    scene->AddGameObject(suzanne);

    //GameObject* cameraGameobject = new GameObject();
    //    virtualCamera = new VirtualCamera({70.0f, (float)windowWidth / (float) windowHeight , 0.1f,
    //                                       200.0f});
    //cameraGameobject->AddComponent(virtualCamera);
    //scene->AddGameObject(cameraGameobject);


    //lerpController->Move(glm::vec3(0, 0, 0), glm::vec3(5, 0, 0), 0.01f);
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);


}

void update()
{
    openCvComponent->Update();
}

int width;
int height;

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw Background
    openCvComponent->Draw();

    int testWidth = width;
    int testHeight = height;

    glfwGetFramebufferSize(window, &width, &height);

    if (testWidth != width || testHeight != height)
    {
        glViewport(0, 0, width, height);
    }

    tigl::shader->setProjectionMatrix(
            glm::perspective(glm::radians(95.0f), (float) width / (float) height, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(
            glm::lookAt(glm::vec3(0, 6.6f, 0.01f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

    tigl::shader->enableTexture(false);
    tigl::shader->enableLighting(false);
    tigl::shader->setLightCount(1);

    tigl::shader->setLightDirectional(0, false);
    tigl::shader->setLightAmbient(0, glm::vec3(0, 0, 10.0f));
//    tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
//    tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
//    tigl::shader->setShinyness(32.0f);

    SceneManager::UpdatePoll(*scene);
}