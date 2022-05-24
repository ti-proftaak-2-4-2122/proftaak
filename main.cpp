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
#include "VirtualCamera.h"
#include "Transform.h"
#include "LerpController.h"
#include "AIPrefab.h"
#include "GameTimer.h"

#include "user-config.h"
#include "ParentTransform.h"

//aspect ratio should always be 4:3 when using realsense camera
#define WINDOW_WIDTH 640
#define WINDOW_HEIGTH 480

#include "CharacterStats.h"

using tigl::Vertex;

GLFWwindow *window;

std::shared_ptr<cv::VideoCapture> capture;
OpenCVVideoCapture *openCvComponent;

void init();
void update();
void draw();
void worldInit();

Scene *scene;

int currentWidth;
int currentHeight;

//VirtualCamera* virtualCamera;
int main()
{
    if (!glfwInit())
        throw "Could not initialize glwf";

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Hello World", nullptr, nullptr);
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
    capture = std::make_shared<cv::VideoCapture>(CONFIG_OPENCV_CAMERA_INDEX);

    openCvComponent = new OpenCVVideoCapture(capture);
    openCvComponent->Awake();

    glfwSetTime(0);

    tigl::shader->setLightCount(2);

    tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));

    tigl::shader->setLightDiffuse(1, glm::vec3(0.8f, 0.8f, 0.8f));
    tigl::shader->setLightDirectional(1, false);
    tigl::shader->setLightPosition(1, glm::vec3(2.0f, 0.0f, 2.0f));
}

void worldInit()
{
    std::string str = "../resource/models/suzanne.obj";

    scene = new Scene();

    auto* playfield = new GameObject();
    playfield->AddComponent(new Mesh(ModelManager::getModel("../resource/models/plane.obj")));

    playfield->transform.setPosition(CONFIG_PLAYFIELD_POSITION);
    playfield->transform.setRotation(CONFIG_PLAYFIELD_ROTATION);
    playfield->transform.setScale(CONFIG_PLAYFIELD_SCALE);

    scene->AddGameObject(playfield);

    GameObject* suzanne = new GameObject();

    ObjModel* _objmodel = ModelManager::getModel(str);
    Mesh* meshComponent = new Mesh(_objmodel);

    auto lerpController = new LerpController();
    lerpController->Move(glm::vec3(0, 0, 0), glm::vec3(5, 0, 0), 0.1f);

    auto parentTransform = new ParentTransform(playfield);
    suzanne->transform.setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    suzanne->transform.setScale(glm::vec3(0.2f, 0.2f, 0.2f));

    suzanne->AddComponent(meshComponent);
    suzanne->AddComponent(lerpController);

    //scene->AddGameObject(suzanne);

    playfield->AddChild(suzanne);

    //auto testFind = levelGO->FindComponent<Mesh>();
//    GameObject *suzanne = new GameObject();
//    ObjModel *_objmodel = ModelManager::getModel(str);
//    Mesh *meshComponent = new Mesh(_objmodel);
//    auto lerpController = new LerpController();
//    suzanne->AddComponent(meshComponent);
//    suzanne->AddComponent(lerpController);
//    scene->AddGameObject(suzanne);

//
//    //GameObject* cameraGameobject = new GameObject();
//    //    virtualCamera = new VirtualCamera({70.0f, (float)windowWidth / (float) windowHeight , 0.1f,
//    //                                       200.0f});
//    //cameraGameobject->AddComponent(virtualCamera);
//    //scene->AddGameObject(cameraGameobject);
//
//
//    lerpController->Move(glm::vec3(0, 0, 0), glm::vec3(5, 0, 0), 0.01f);
//    int viewport[4];
//    glGetIntegerv(GL_VIEWPORT, viewport);

    auto aiPrefab = new AIPrefab();
    aiPrefab->onTriggerEnter();

    //GameObject* cameraGameobject = new GameObject();
    //    virtualCamera = new VirtualCamera({70.0f, (float)windowWidth / (float) windowHeight , 0.1f,
    //                                       200.0f});
    //cameraGameobject->AddComponent(virtualCamera);
    //scene->AddGameObject(cameraGameobject);
}

void update()
{
    openCvComponent->Update();
    scene->update();
    GameTimer::update(glfwGetTime());
}

void draw()
{
    // Resize viewport, when needed
    int newWidth = currentWidth;
    int newHeight = currentHeight;

    glfwGetFramebufferSize(window, &newWidth, &newHeight);
    if (newWidth != currentWidth || newHeight != currentHeight)
        glViewport(0, 0, currentWidth = newWidth, currentHeight = newHeight);


    // Clear view
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Prepare for background
    glDisable(GL_DEPTH_TEST);

    tigl::shader->enableLighting(false);

    // Draw Background
    openCvComponent->Draw();

    // Prepare for 3D Scene
    glEnable(GL_DEPTH_TEST);

    tigl::shader->enableTexture(false);
    tigl::shader->enableLighting(true);

    tigl::shader->setProjectionMatrix(
            glm::perspective(glm::radians(90.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGTH, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(
            glm::lookAt(glm::vec3(0, 0.5f, 2.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

    // Draw 3D Scene
    SceneManager::UpdatePoll(*scene);
}