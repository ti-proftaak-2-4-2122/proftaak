/**
 * @file
 * @brief Source file for the OpenCVVideoCapture class
 * @author twanh
 * @date 13-05-2022
 */

#include <memory>
#include <thread>

#include "glad/glad.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <utility>
#include "tigl.h"

#include "../../../user-config.h"

#include "ImageProvider.h"
#include "CardDetector.h"

using tigl::Vertex;

ImageProvider::ImageProvider(std::shared_ptr<cv::VideoCapture> capture)
{
    this->capture = std::move(capture);
    this->captureTextureId = -1;
}

void ImageProvider::Awake()
{
    glGenTextures(1, &captureTextureId);
    glBindTexture(GL_TEXTURE_2D, captureTextureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // First time: Update camera blocking!
    this->ReadImage();
    this->useImageBuffer2 = this->imageHasUpdated = true;

    // Create and start update thread
    if(CONFIG_FPS_GO_BRRR)
        this->imageUpdateThread = std::thread(&ImageProvider::ImageUpdateTask, this);
}

void ImageProvider::Update()
{
    if(!CONFIG_FPS_GO_BRRR)
    {
        this->ReadImage();

        this->useImageBuffer2 = !this->useImageBuffer2;
        this->imageHasUpdated = true;
    }

    // Lock, because we don't want the buffers to swap when updating
    this->imageUpdateLock.lock();
    if(this->imageHasUpdated) {

        // Provide image to graphics
        glBindTexture(GL_TEXTURE_2D, this->captureTextureId);

        cv::Mat currentImage = this->useImageBuffer2 ? this->imageBuffer2 : this->imageBuffer1;

        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGB,
                currentImage.cols,
                currentImage.rows,
                0,
                GL_BGR,
                GL_UNSIGNED_BYTE,
                currentImage.data
        );

        this->imageHasUpdated = false;
    }
    this->imageUpdateLock.unlock();
}

void ImageProvider::Draw() const
{
    tigl::shader->setProjectionMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(glm::lookAt(
            glm::vec3(0.0f, 0, 5),
            glm::vec3(0.0f, 0, 0),
            glm::vec3(0.0f, 1, 0)
    ));

    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    float rectangleSize = 1;

    tigl::shader->enableTexture(true);
    glBindTexture(GL_TEXTURE_2D, this->captureTextureId);
    tigl::begin(GL_QUADS);

    tigl::addVertex(Vertex::PT(glm::vec3(-rectangleSize, -rectangleSize, 0), glm::vec2(0, 1)));
    tigl::addVertex(Vertex::PT(glm::vec3(rectangleSize, -rectangleSize, 0), glm::vec2(1, 1)));
    tigl::addVertex(Vertex::PT(glm::vec3(rectangleSize, rectangleSize, 0), glm::vec2(1, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(-rectangleSize, rectangleSize, 0), glm::vec2(0, 0)));

    tigl::end();
}

void ImageProvider::ImageUpdateTask()
{
    // Loop while instance is not destructing
    this->imageUpdateLock.lock();
    while(!this->isDestructing)
    {
        this->imageUpdateLock.unlock();

        // Read the new image
        this->ReadImage();

        // Swap buffers and update hasUpdated flag
        this->imageUpdateLock.lock();
        this->useImageBuffer2 = !this->useImageBuffer2;
        this->imageHasUpdated = true;
        this->imageUpdateLock.unlock();

        this->imageUpdateLock.lock();
    }
}

void ImageProvider::ReadImage()
{
    static cv::Mat internalBuffer;

    if(!this->capture->isOpened())
        return;

    // Read the new image (blocking)
    this->capture->read(internalBuffer);

    // Process the image to the image buffer that is not used at the moment
    if(this->useImageBuffer2)
        this->imageBuffer1 = detector->UpdateCards(internalBuffer);
    else
        this->imageBuffer2 = detector->UpdateCards(internalBuffer);
}

ImageProvider::~ImageProvider()
{
    this->imageUpdateLock.lock();
    this->isDestructing = true;
    this->imageUpdateLock.unlock();

    if(this->imageUpdateThread.joinable())
        this->imageUpdateThread.join();

    delete this->detector;
}

