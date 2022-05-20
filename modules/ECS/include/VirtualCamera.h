//
// Created by Daan van Donk on 18/05/2022.
//

#ifndef PROFTAAK24_VIRTUALCAMERA_H
#define PROFTAAK24_VIRTUALCAMERA_H


#include "Component.h"
#include "glm/glm.hpp"
struct VCamRenderSettings {
    float fov;
    float aspectRatio;
    float nearClipping;
    float farClipping;
};

class VirtualCamera : public Component
{
public:
    VCamRenderSettings vCamRenderSettings;
    VirtualCamera(VCamRenderSettings _vCamRenderSettings);
    void LookAt(glm::vec3 lookAt);
};


#endif //PROFTAAK24_VIRTUALCAMERA_H
