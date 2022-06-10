/**
 * @file
 * @brief Source file for the VirtualCamera class
 * @author Daan van Donk
 * @date 18-05-2022
 */
 
#include "VirtualCamera.h"
#include "Transform.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

VirtualCamera::VirtualCamera(VCamRenderSettings _vCamRenderSettings)
{
    vCamRenderSettings = _vCamRenderSettings;
}

void VirtualCamera::LookAt(glm::vec3 lookAtVec3)
{
    tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(vCamRenderSettings.fov),
                                                       vCamRenderSettings.aspectRatio,
                                                       vCamRenderSettings.nearClipping,
                                                       vCamRenderSettings.farClipping));
    tigl::shader->setViewMatrix(
            glm::lookAt(lookAtVec3, gameObject->transform.getPosition(), glm::vec3(0, 1, 0)));
}