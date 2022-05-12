#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "Scene.h"
#include "LerpController.h"
#include "SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GameObject.h>

void init();

void update();

void draw();

int main()
{
    glm::vec3 test;
    Scene scene;
    GameObject gameObject;
    auto *lerpController = new LerpController;
    gameObject.AddComponent(lerpController);
    scene.AddGameObject(gameObject);

    SceneManager::LoadScene(scene);
}
