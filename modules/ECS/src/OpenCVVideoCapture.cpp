//
// Created by twanh on 13-5-2022.
//

#include <memory>

#include <glad/glad.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tigl.h>

#include "OpenCVVideoCapture.h"
#include "CardDetector.h"

using tigl::Vertex;

OpenCVVideoCapture::OpenCVVideoCapture(std::shared_ptr<cv::VideoCapture> capture) {
    this->capture = capture;
    this->captureTextureId = -1;
}

void OpenCVVideoCapture::Awake() {
    glGenTextures(1, &captureTextureId);
    glBindTexture(GL_TEXTURE_2D, captureTextureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void OpenCVVideoCapture::Update() {
    cv::Mat captureImage, cvImage;
    auto *detector = new CardDetector();

    // Todo: Replace with image provider
    this->capture->read(captureImage);

    cvImage = detector->UpdateCards(captureImage);
    detector->PrintCards();


    glBindTexture(GL_TEXTURE_2D, this->captureTextureId);

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            cvImage.cols,
            cvImage.rows,
            0,
            GL_BGR,
            GL_UNSIGNED_BYTE,
            cvImage.data
    );
}

void OpenCVVideoCapture::Draw() {

    tigl::shader->setProjectionMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(glm::lookAt(
            glm::vec3(0.0f, 0, 5),
            glm::vec3(0.0f, 0, 0),
            glm::vec3(0.0f,1,0)
    ));

    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    float rectangleSize = 1;

    tigl::shader->enableTexture(true);
    glBindTexture(GL_TEXTURE_2D, this->captureTextureId);
    tigl::begin(GL_QUADS);

    tigl::addVertex(Vertex::PT(glm::vec3(-rectangleSize, -rectangleSize, 0), glm::vec2(1, 1)));
    tigl::addVertex(Vertex::PT(glm::vec3(rectangleSize, -rectangleSize, 0), glm::vec2(0, 1)));
    tigl::addVertex(Vertex::PT(glm::vec3(rectangleSize, rectangleSize, 0), glm::vec2(0, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(-rectangleSize, rectangleSize, 0), glm::vec2(1, 0)));

    tigl::end();
}