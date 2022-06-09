#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <tigl.h>
#include <opencv2/highgui.hpp>
#include <memory>

#include "Mesh.h"
#include "ModelManager.h"
#include "OpenCVVideoCapture.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "GameTimer.h"
#include "Collider.h"
#include "CharacterStats.h"

#include "user-config.h"
#include "AIPrefab.h"
#include "TowerPrefab.h"
#include "UnitTypeEnum.h"

//aspect ratio should always be 4:3 when using realsense camera
#define WINDOW_WIDTH 1440
#define WINDOW_HEIGTH 1080

using tigl::Vertex;

GLFWwindow *window;

std::shared_ptr<cv::VideoCapture> capture;
OpenCVVideoCapture *openCvComponent;

void init();

void update();

void draw();

void worldInit();

void createMapObject(const std::string &filePath, glm::vec3 diffuseColor);

int currentWidth;
int currentHeight;

//VirtualCamera* virtualCamera;
int main()
{
    //Init GLFW
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

    if (capture->isOpened())
    {
        openCvComponent = new OpenCVVideoCapture(capture);
        openCvComponent->Awake();
    }

    glfwSetTime(0);


    //setting up lights and render stuff
    tigl::shader->enableColor(false);
    tigl::shader->enableTexture(true);
    tigl::shader->enableLighting(true);
    tigl::shader->setLightCount(2);

    tigl::shader->setLightDirectional(0, false);
    tigl::shader->setLightPosition(0, glm::vec3(10, 10, 10));

    tigl::shader->setLightAmbient(1, glm::vec3(0.1f, 0.1f, 0.15f));
    tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
    tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
    tigl::shader->setShinyness(32.0f);
    tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
    tigl::shader->setLightDiffuse(1, glm::vec3(0.8f, 0.8f, 0.8f));
    tigl::shader->setLightDirectional(1, false);
    tigl::shader->setLightPosition(1, glm::vec3(2.0f, 0.0f, 2.0f));
}

void worldInit()
{
    AIPrefab* aiPrefab = new AIPrefab(new Transform(glm::vec3(-15.0f, 0.0f, -8.0f), glm::vec3(0, 0, 0),
                                         glm::vec3(1.0f,1.0f,1.0f)), FAST);

    TowerPrefab* towerPrefab = new TowerPrefab(new Transform(glm::vec3(30.0f, 0.0f, -12.0f),glm::vec3(0,0,0),glm::vec3(1.0f, 1.0f, 1.0f)));
    TowerPrefab* towerPrefab1 = new TowerPrefab(new Transform(glm::vec3(50.0f, 0.0f, 0.0f),glm::vec3(0,0,0),glm::vec3(1.0f, 1.0f, 1.0f)));




    GameObject* field = new GameObject(new Transform(glm::vec3(0, 0, 0),
                                                          glm::vec3(0,0,0),
                                                          glm::vec3(1, 1, 1)));

    Mesh* fieldMesh = new Mesh(ModelManager::getModel("../resource/models/map_ground.obj"));
    field->AddComponent(fieldMesh);

    GameObject* bridge = new GameObject(new Transform(glm::vec3(0, 0, 0),
                                                     glm::vec3(0,0,0),
                                                     glm::vec3(1, 1, 1)));

    Mesh* bridgeRender = new Mesh(ModelManager::getModel("../resource/models/map_bridges.obj"));
    bridge->AddComponent(bridgeRender);

//    //Setting colour
    fieldMesh->SetDiffuseColor({0.474, 0.643, 0.376});
    bridgeRender->SetDiffuseColor({1.0f, 0.392f, 0.3137f});
//    //building map
//    createMapObject("../resource/models/map_ground.obj", {0.0f, 0, 0});
//    createMapObject("../resource/models/map_river.obj", {0.0f, 0, 1});
//    createMapObject("../resource/models/map_bridges.obj", {1.0f, 0.392f, 0.3137f});
//    createMapObject("../resource/models/map_towers.obj", {1.0f, 0.392f, 0.3137f});
//
    Scene::getSingleton().AddGameObject(aiPrefab);
    Scene::getSingleton().AddGameObject(towerPrefab);
    Scene::getSingleton().AddGameObject(towerPrefab1);
    Scene::getSingleton().AddGameObject(field);
    Scene::getSingleton().AddGameObject(bridge);
//    Scene::getSingleton().AddGameObject(towerPrefab1);
//    Scene::getSingleton().AddGameObject(field);
//    Scene::getSingleton().AddGameObject(bridge);

    SceneManager::LoadScene(Scene::getSingleton());
}

void update()
{
    if (capture->isOpened())
        openCvComponent->Update();

    Scene::getSingleton().update();
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

    if (capture->isOpened())
    {
        // Prepare for background
        glDisable(GL_DEPTH_TEST);

        tigl::shader->enableLighting(false);
        tigl::shader->enableTexture(true);

        // Draw Background
        openCvComponent->Draw();
    }

    // Prepare for 3D Scene
    glEnable(GL_DEPTH_TEST);
    tigl::shader->enableLighting(true);
    tigl::shader->enableTexture(CONFIG_LIGHT_ENABLE_RTX);

    tigl::shader->setProjectionMatrix(
            glm::perspective(glm::radians(90.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGTH,
                             0.1f, 200.0f));
    tigl::shader->setViewMatrix(
            glm::lookAt(glm::vec3(0, 60, 0.01f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

    glad_glEnable(GL_DEPTH_TEST);


    // Draw 3D Scene
    SceneManager::UpdatePoll(Scene::getSingleton());
}


void createMapObject(const std::string &filePath, glm::vec3 diffuseColor)
{
    auto* map_object = new GameObject(new Transform());

    map_object->AddComponent(new Mesh(ModelManager::getModel(filePath)));
    map_object->transform.setPosition(CONFIG_PLAYFIELD_POSITION);
    map_object->transform.setRotation(CONFIG_PLAYFIELD_ROTATION);
    map_object->transform.setScale(CONFIG_PLAYFIELD_SCALE);
    auto mesh_map_object = map_object->FindComponent<Mesh>();
    if (mesh_map_object)
    {
        //mesh_map_ground->SetColor({200,200,200,255});
        mesh_map_object->SetDiffuseColor(diffuseColor);
    }
    Scene::getSingleton().AddGameObject(map_object);
}
