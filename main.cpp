#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "tigl.h"
#include "ImageFilter.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <memory>

#include "ObjModel.h"
#include "Mesh.h"
#include "ModelManager.h"
#include "OpenCVVideoCapture.h"
#include "Scene.h"
#include "SceneManager.h"
#include "PlaneMesh.h"

#include "user-config.h"
#include "Transform.h"

using tigl::Vertex;

GLFWwindow *window;

std::shared_ptr<cv::VideoCapture> capture;
OpenCVVideoCapture *openCvComponent;

void init();

void update();

void draw();

void worldInit();

Scene *scene;


int main()
{
    ImageFilter *filter = new ImageFilter();
//    filter->filter_image(); //blocking call

    if (!glfwInit())
        throw "Could not initialize glwf";

    window = glfwCreateWindow(1400, 800, "Hello World", nullptr, nullptr);
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
    capture = std::make_shared<cv::VideoCapture>(CONFIG_OPENCV_CAMERA_INDEX);

    openCvComponent = new OpenCVVideoCapture(capture);
    openCvComponent->Awake();
}

void worldInit()
{
    std::string str = "../resource/models/suzanne.obj";

    scene = new Scene();

    GameObject* suzanne = new GameObject();

    ObjModel* _objmodel = ModelManager::getModel(str);
    Mesh* meshComponent = new Mesh(_objmodel);
    suzanne->AddComponent(meshComponent);

    scene->AddGameObject(suzanne);

    auto* playfield = new GameObject();
    playfield->AddComponent<PlaneMesh>();

    auto* playfieldTransform = (Transform*) playfield->getTransform();
    playfieldTransform->position = CONFIG_PLAYFIELD_POSITION;
    playfieldTransform->rotation = CONFIG_PLAYFIELD_ROTATION;
    playfieldTransform->scale = CONFIG_PLAYFIELD_SCALE;

    scene->AddGameObject(playfield);
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
            glm::perspective(glm::radians(70.0f), (float) width / (float) height, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(
            glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

    tigl::shader->enableTexture(false);


    SceneManager::UpdatePoll(*scene);

}