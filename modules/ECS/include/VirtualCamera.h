/**
 * @file
 * @brief Header file for the VCamRenderSettings struct and VirtualCamera class
 * @author Daan van Donk
 * @date 18-05-2022
 */

#pragma once

#include "Component.h"
#include "glm/glm.hpp"

struct VCamRenderSettings
{
    float fov;
    float aspectRatio;
    float nearClipping;
    float farClipping;
};

class VirtualCamera : public Component
{
public:
    VCamRenderSettings vCamRenderSettings{};

    explicit VirtualCamera(VCamRenderSettings _vCamRenderSettings);

    void LookAt(glm::vec3 lookAt);
};
