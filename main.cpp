#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "tigl.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "ObjModel.h"
#include "Mesh.h"

using tigl::Vertex;

// #pragma comment(lib, "glfw3.lib")
// #pragma comment(lib, "glew32s.lib")
// #pragma comment(lib, "opengl32.lib")

GLFWwindow *window;

cv::VideoCapture* capture;
cv::Mat* captureImage;
uint captureTextureId;

void init();

void update();

void draw();

std::string str =  "../resource/models/suzanne.obj";

ObjModel objModel = ObjModel(str);
Mesh* mesh = new Mesh(&objModel);

int main()
{
    if (!glfwInit())
        throw "Could not initialize glwf";

    window = glfwCreateWindow(1400, 800, "Hello World", nullptr, nullptr);
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

    // Init OpenCV
    capture = new cv::VideoCapture(2);
    captureImage = new cv::Mat();

    glGenTextures(1, &captureTextureId);
    glBindTexture(GL_TEXTURE_2D, captureTextureId);
}


void update()
{
    capture->read(*captureImage);
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

    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    float rectangleSize = 3;

    glBindTexture(GL_TEXTURE_2D, captureTextureId);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        captureImage->cols,
        captureImage->rows,
        0,
        GL_BGR,
        GL_UNSIGNED_BYTE,
        captureImage->data
    );

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    tigl::shader->enableTexture(true);
    tigl::begin(GL_QUADS);
    tigl::addVertex(Vertex::PT(glm::vec3(-rectangleSize, -rectangleSize, 0), glm::vec2(1, 1)));
    tigl::addVertex(Vertex::PT(glm::vec3(rectangleSize, -rectangleSize, 0), glm::vec2(0, 1)));
    tigl::addVertex(Vertex::PT(glm::vec3(rectangleSize, rectangleSize, 0), glm::vec2(0, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(-rectangleSize, rectangleSize, 0), glm::vec2(1, 0)));
    tigl::end();

    tigl::shader->enableTexture(false);
    mesh->DrawMesh();
}