//
// Created by tjtle on 01/06/2022.
//

#include "Spawner.h"
#include "glm/gtc/type_ptr.hpp"
#include "AIPrefab.h"
#include "InputHandler.h"
#include "../../../user-config.h"

bool Spawner::HasCard(unsigned int color)
{
    for (auto card : receivedCards){
        if (card->color == color)
            return true;
    }
    return false;
}

void Spawner::UpdateAfterDraw()
{
    receivedCards = detector->GetDetectedCards();
    for(auto card : receivedCards)
    {
        if(spawnedObjects.empty() || !spawnedObjects.contains(card->color))
        {
           // std::cout << "Drawing new card" << std::endl;
            //add new card to spawnedcards
            glm::vec3 glPos = ConvertCords(card);
            auto *charGameObject = new GameObject(new Transform(glPos));
            charGameObject->AddComponent(new Mesh(ModelManager::getModel("../resource/models/tower.obj")));

            Scene::getSingleton().AddGameObject(charGameObject);
            //std::cout << "Trying to spawn on color: "<< card.color << " on X:" << glPos.x
            //<< ", Y:" << glPos.y << "\n";
//            spawnedObjects.insert(std::pair<unsigned int, GameObject>(card.color,
//             *charGameObject));

            spawnedObjects.insert({card->color,charGameObject});
            continue;
        }

        auto foundModel = spawnedObjects.find(card->color);
        if (foundModel != spawnedObjects.end())
        {
           // std::cout << "Drawing known card" << std::endl;

            glm::vec3 glPos = ConvertCords(card);

            //std::cout << "Trying to spawn on color: "<< card.color << " on X:" << glPos.x
            //          << ", Y:" << glPos.y << ", Z:" << glPos.z << "\n";

            foundModel->second->transform.setPosition(glPos);
//            Scene::getSingleton().AddGameObject(foundModel->second);
        }
        //spawning
        this->currentCard = card;
    }

    for (auto spawnedObject = spawnedObjects.begin();spawnedObject != spawnedObjects.end(); ++spawnedObject) {
        if(!HasCard(spawnedObject->first))
        {
            //std::cout << "Card no longer found destoying: "<< spawnedObject->first
            //<<"\n size of array: " << spawnedObjects.size() << std::endl;
            Scene::getSingleton().RemoveGameObject(spawnedObject->second);
            spawnedObjects.erase(spawnedObject);
            //std::cout << "Size after deletion: "<< spawnedObjects.size() << std::endl;
        }
    }
}

void Spawner::Spawn()
{
    if(!currentCard)
    {
        std::cout << "currentcard is null";
        return;
    }
    //std::cout << "YO IMMA SPAWN EM";
    glm::vec3 glPos = ConvertCords(currentCard);
    std::cout << "Pos: " << glPos.x << "," << glPos.y << "," << glPos.z << ".\n";
    UnitTypeEnum type;
    //std::cout << "color = " << card.color << std::endl;
    if(currentCard->color == 0) {
        type = FAST;
        //std::cout << "type = fast\n";
    }
    if(currentCard->color == 1) {
        type = SLOW;
        //std::cout << "type = slow\n";
    }
    if(currentCard->color == 2) {
        type = LAND;
        //std::cout << "type = land\n";
    }
    //std::cout << ToString(type) << std::endl;
    glm::mat4 model = glm::lookAt(glm::vec3(0, 60, 0.01f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); //viewmatrix
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float) 1440 /
    (float) 1080, 0.1f, 200.0f);
    glm::ivec4 viewport;
    glGetIntegerv(GL_VIEWPORT, glm::value_ptr(viewport));
    glm::vec3 Projected = glm::project(glPos, model, projection,viewport);
    auto *AIcharacter = new AIPrefab(new Transform(glPos), type);
    Scene::getSingleton().AddGameObject(AIcharacter);
    currentCard = nullptr;
}

void Spawner::Awake()
{
    Component::Awake();
    spawnedObjects = std::map<unsigned int, GameObject*>();

    std::function<void()> functionPointer = [this](){
        this->Spawn();
    };


    InputHandler::getSingleton().AddCallback(GLFW_KEY_SPACE, GLFW_PRESS, functionPointer);

}

glm::vec3 Spawner::ConvertCords(CardDetector::Card* card)
{
    glm::mat4 model = MATRIX_VIEW;
    glm::mat4 projection = MATRIX_PROJECTION;
    glm::ivec4 viewport;
    glGetIntegerv(GL_VIEWPORT, glm::value_ptr(viewport));
    glm::vec3 cvPos = {card->x * viewport[2], viewport[3] - card->y * viewport[3], 0.991f};

    glReadPixels(cvPos.x, cvPos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &cvPos.z);

    glm::vec3 glPos = glm::unProject(cvPos, model, projection, viewport);

    glPos = {glPos.x*1.0f, 0.0f, glPos.z*1.0f};

    return glPos;
}
