//
// Created by tjtle on 01/06/2022.
//

#include "Spawner.h"
#include "glm/gtc/type_ptr.hpp"
#include "AIPrefab.h"

bool Spawner::HasCard(unsigned int color)
{
    for (auto card : receivedCards){
        if (card.color == color)
            return true;
    }
    return false;
}

void Spawner::UpdateAfterDraw()
{
    receivedCards = detector->GetDetectedCards();
    for(auto card : receivedCards)
    {
        if(spawnedObjects.empty() || !spawnedObjects.contains(card.color))
        {
           // std::cout << "Drawing new card" << std::endl;
            //add new card to spawnedcards
            auto *charGameObject = new GameObject();
            charGameObject->AddComponent(new Mesh(ModelManager::getModel("../resource/models/tower.obj")));

            glm::vec3 glPos = ConvertCords(card);

            charGameObject->transform.setPosition(glPos);

            Scene::getSingleton().AddGameObject(charGameObject);
            //std::cout << "Trying to spawn on color: "<< card.color << " on X:" << glPos.x
            //<< ", Y:" << glPos.y << "\n";
//            spawnedObjects.insert(std::pair<unsigned int, GameObject>(card.color,
//             *charGameObject));

            spawnedObjects.insert({card.color,charGameObject});
            continue;
        }

        auto foundModel = spawnedObjects.find(card.color);
        if (foundModel != spawnedObjects.end())
        {
           // std::cout << "Drawing known card" << std::endl;

            glm::vec3 glPos = ConvertCords(card);

            //std::cout << "Trying to spawn on color: "<< card.color << " on X:" << glPos.x
            //          << ", Y:" << glPos.y << ", Z:" << glPos.z << "\n";

            foundModel->second->transform.setPosition(glPos);
//            Scene::getSingleton().AddGameObject(foundModel->second);
        }

        if(GetKeyState(VK_SPACE) & 0x8000){
            std::cout << "YO IMMA SPAWN EM";
            glm::vec3 glPos = ConvertCords(card);
            std::cout << "Pos: " << glPos.x << "," << glPos.y << "," << glPos.z << ".\n";
            auto *transform = new Transform(glPos);
            auto *AIcharacter = new AIPrefab(*transform, new CharacterStats{5.0f, 100.0f, 10.0f, 2.0f, 3.0f, GROUND});

            Scene::getSingleton().AddGameObject(AIcharacter);
        }
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

void Spawner::Awake()
{
    Component::Awake();
    spawnedObjects = std::map<unsigned int, GameObject*>();
}

glm::vec3 Spawner::ConvertCords(CardDetector::Card card)
{
    glm::mat4 model = glm::lookAt(glm::vec3(0, 15.0f, 5.0f), glm::vec3(0, 0, 0), glm::vec3(0,1,0)); //viewmatrix
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float) 1440 /
                                                                 (float) 1080, 0.1f, 200.0f);
    glm::ivec4 viewport;
    glGetIntegerv(GL_VIEWPORT, glm::value_ptr(viewport));
    glm::vec3 cvPos = {card.x * viewport[2], viewport[3] - card.y * viewport[3], 0.991f};

    glReadPixels(cvPos.x, cvPos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &cvPos.z);

    glm::vec3 glPos = glm::unProject(cvPos, model, projection, viewport);

    glPos = {glPos.x*1.0f, glPos.y*0.0f + 1.0f, glPos.z*1.0f};

    return glPos;
}
