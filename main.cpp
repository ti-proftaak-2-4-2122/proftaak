#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <tigl.h>
#include <cs/CelShader.h>
#include <opencv2/highgui.hpp>
#include <memory>
#include <vector>

#include "Mesh.h"
#include "ModelManager.h"
#include "ImageProvider.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "GameTimer.h"
#include "Collider.h"
#include "ImageProvider.h"
#include "CharacterStats.h"

#include "user-config.h"
#include "Spawner.h"
#include "AIPrefab.h"
#include "TowerPrefab.h"
#include "UnitTypeEnum.h"
#include "InputHandler.h"
#include "Animator.h"
#include "colours.h"


using tigl::Vertex;

GLFWwindow *window;

std::shared_ptr<cv::VideoCapture> capture;
ImageProvider *imageProvider;
Scene *scene;

void init();

void update();

void draw();

void worldInit();

void createMapObject(const std::string &filePath, glm::vec4 color);

int currentWidth;
int currentHeight;

//VirtualCamera* virtualCamera;
int main()
{
    //Init GLFW
    if (!glfwInit())
        throw "Could not initialize glwf";

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(CONFIG_WINDOW_WIDTH, CONFIG_WINDOW_HEIGTH, "NOT CLASH ROYALE", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    if(!CONFIG_FPS_VSYNC)
        glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    tigl::init();
    cs::init();

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

void key_callback(GLFWwindow *nWindow, int key, int scancode, int action, int mods)
{
    InputHandler::getSingleton().check_keys(key, action);
}


void init()
{

    glfwSetKeyCallback(window, key_callback);

    // Init OpenCV
    capture = std::make_shared<cv::VideoCapture>(CONFIG_OPENCV_CAMERA_INDEX);

    if (capture->isOpened())
    {
        imageProvider = new ImageProvider(capture);
        imageProvider->Awake();
    }

    glfwSetTime(0);


    // Init tigl shader
    tigl::shader->use();

    tigl::shader->enableColor(false);
    tigl::shader->enableTexture(true);
    tigl::shader->enableLighting(true);

    tigl::shader->setLightCount(2);
    tigl::shader->setShinyness(32.0f);

    tigl::shader->setLightDirectional(0, false);
    tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
    tigl::shader->setLightPosition(0, glm::vec3(10, 10, 10));
    tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
    tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));

    tigl::shader->setLightDirectional(1, false);
    tigl::shader->setLightAmbient(1, glm::vec3(0.1f, 0.1f, 0.15f));
    tigl::shader->setLightDiffuse(1, glm::vec3(0.8f, 0.8f, 0.8f));
    tigl::shader->setLightPosition(1, glm::vec3(2.0f, 0.0f, 2.0f));

    // Init Cel Shader
    cs::shader->use();

    cs::shader->enableColor(false);
    cs::shader->enableColorMult(true);
    cs::shader->enableAlphaTest(true);

    cs::shader->setLightPosition(CONFIG_LIGHT_POSITION);
}

void closeWindow()
{
    std::cout << "Closing window" << std::endl;
    glfwSetWindowShouldClose(window, true);
}

void worldInit()
{
    InputHandler::getSingleton().AddCallback(GLFW_KEY_ESCAPE, GLFW_PRESS, closeWindow);

//    AIPrefab* aiPrefab = new AIPrefab(new Transform({-9.0f, 0.0f, -12.0f}, {0,0,0}, {1.0f,1.0f,1.0f}), UnitTypeEnum::FAST);

//    AIPrefab* aiPrefab2 = new AIPrefab(new Transform({-9.0f, 0.0f, -12.0f}, {0,0,0}, {1.0f,1.0f,1.0f}), UnitTypeEnum::SLOW);


    TowerPrefab *towerPrefab = new TowerPrefab(new Transform(glm::vec3(30.0f, 0.0f, -12.0f), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f)),
                                               "RechtsBoven");
    TowerPrefab *towerPrefab1 = new TowerPrefab(new Transform(glm::vec3(-30.0f, 0.0f, 12.0f), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f)),
                                                "LinksOnder");
    TowerPrefab *towerPrefab2 = new TowerPrefab(new Transform(glm::vec3(30.0f, 0.0f, 12.0f), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f)),
                                                "RechtsOnder");
    TowerPrefab *towerPrefab3 = new TowerPrefab(new Transform(glm::vec3(-30.0f, 0.0f, -12.0f), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f)),
                                                "LinksBoven");

    GameObject *field = new GameObject(new Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
    Mesh *mesh = new Mesh(ModelManager::getModel("../resource/models/map_ground.obj"));
    mesh->SetColor(GREEN_GRASS);
    field->AddComponent(mesh);

    GameObject *bridge = new GameObject(new Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
    Mesh *mesh1 = new Mesh(ModelManager::getModel("../resource/models/map_bridges.obj"));
    mesh1->SetColor(YELLOW_SUNFLOWER);
    bridge->AddComponent(mesh1);


    float mapAlpha = CONFIG_PLAYFIELD_ALPHA;

//    Scene::getSingleton().AddGameObject(aiPrefab);
//    Scene::getSingleton().AddGameObject(aiPrefab2);
    Scene::getSingleton().AddGameObject(towerPrefab);
    Scene::getSingleton().AddGameObject(towerPrefab1);
    Scene::getSingleton().AddGameObject(towerPrefab2);
    Scene::getSingleton().AddGameObject(towerPrefab3);
    Scene::getSingleton().AddGameObject(field);
    Scene::getSingleton().AddGameObject(bridge);

    auto *spawnManager = new GameObject(new Transform());
    auto *spawner = new Spawner();

    spawnManager->AddComponent(spawner);
    Scene::getSingleton().AddGameObject(spawnManager);

//    GameObject* gangGangStyleGang = new GameObject(new Transform());
//    Mesh* mesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));
//    mesh->SetColor(TEAL_TURKISH);
//    Animator* animator = new Animator("../resource/models/animation", *mesh, 30);
//    gangGangStyleGang->AddComponent(mesh);
//    gangGangStyleGang->AddComponent(animator);
//    animator->StartAnimation();
//    Scene::getSingleton().AddGameObject(gangGangStyleGang);

    SceneManager::LoadScene(Scene::getSingleton());
}

int frameCount = 0;
double lastFramePrint = -1;

void update()
{
    imageProvider->Update();

    Scene::getSingleton().update();
    GameTimer::update(glfwGetTime());

    if(CONFIG_FPS_COUNTER) {
        frameCount++;

        if(lastFramePrint > 0)
        {
            double deltaTime = GameTimer::getCurrentTime() - lastFramePrint;
            if(deltaTime >= CONFIG_FPS_COUNTER_ACCURACY) {
                std::cout << "Avg Frametime: " << (deltaTime / (double)frameCount) * 1000.0 << "ms;"
                      "\tAvg FPS: " << frameCount / deltaTime << std::endl;

                frameCount = 0;
                lastFramePrint = GameTimer::getCurrentTime();
            }
        }
        else
        {
            lastFramePrint = GameTimer::getCurrentTime();
        }
    }

    if(Scene::getSingleton().checkPlayerWinCondition())
    {
        closeWindow();
    }
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
        glDisable(GL_BLEND);

        tigl::shader->use();

        tigl::shader->enableLighting(false);
        tigl::shader->enableTexture(true);
        tigl::shader->enableColor(false);
        tigl::shader->enableColorMult(false);

        // Draw Background
        imageProvider->Draw();
    }

    // Prepare for 3D Scene
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    cs::shader->use();

    cs::shader->setProjectionMatrix(CONFIG_MATRIX_PROJECTION);

    cs::shader->setViewMatrix(CONFIG_MATRIX_VIEW);

    // Draw 3D Scene
    SceneManager::UpdatePoll(Scene::getSingleton());
}

void createMapObject(const std::string &filePath, glm::vec4 color)
{
    auto *map_object = new GameObject(new Transform);

    map_object->AddComponent(new Mesh(ModelManager::getModel(filePath)));

    map_object->transform.setPosition(CONFIG_PLAYFIELD_POSITION);
    map_object->transform.setRotation(CONFIG_PLAYFIELD_ROTATION);
    map_object->transform.setScale(CONFIG_PLAYFIELD_SCALE);

    auto mesh_map_object = map_object->FindComponent<Mesh>();
    if (mesh_map_object)
    {
        mesh_map_object->SetColor(color);
    }

    scene->getSingleton().AddGameObject(map_object);
}
