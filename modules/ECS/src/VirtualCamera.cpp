//
// Created by Daan van Donk on 18/05/2022.
//
//
//#include "VirtualCamera.h"
//#include "tigl.h"
//#include <glm/gtc/matrix_transform.hpp>
//
//VirtualCamera::VirtualCamera(VCamRenderSettings _vCamRenderSettings, glm::vec3 lookAt)
//{
//    vCamRenderSettings = _vCamRenderSettings;
//
//    tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(vCamRenderSettings.fov),
//                                                       vCamRenderSettings.aspectRatio,
//                                                       vCamRenderSettings.nearClipping,
//                                                       vCamRenderSettings.farClipping));
//    tigl::shader->setViewMatrix(glm::lookAt(gameObject->transform.position, lookAt, glm::vec3(0, 1, 0)));
//}
//
//void VirtualCamera::LookAt(glm::vec3 lookAt) {
//    tigl::shader->setViewMatrix(glm::lookAt(gameObject->transform.position, lookAt, glm::vec3(0,
//                                                                                             1, 0)));
//}