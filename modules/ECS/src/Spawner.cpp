//
// Created by tjtle on 01/06/2022.
//

#include "Spawner.h"

bool Spawner::HasCard(unsigned int color)
{
    for (auto card : receivedCards){
        if (card.color == color)
            return true;
    }
    return false;
}

void Spawner::Update()
{
    receivedCards = detector->GetDetectedCards();
    for(auto card : receivedCards)
    {
        if(spawnedObjects.empty() || !spawnedObjects.contains(card.color))
        {
            std::cout << "Drawing new card" << std::endl;
            //add new card to spawnedcards
            auto *charGameObject = new GameObject();
            charGameObject->AddComponent(new Mesh(ModelManager::getModel("../resource/models/tower.obj")));

            glm::vec3 glPos = convertCords(card);

            charGameObject->transform.setPosition(glPos);

            Scene::getSingleton().AddGameObject(charGameObject);
            std::cout << "Trying to spawn on color: "<< card.color << " on X:" << glPos.x
            << ", Y:" << glPos.y << "\n";
//            spawnedObjects.insert(std::pair<unsigned int, GameObject>(card.color,
//             *charGameObject));

            spawnedObjects.insert({card.color,charGameObject});
            continue;
        }

        auto foundModel = spawnedObjects.find(card.color);
        if (foundModel != spawnedObjects.end())
        {
            std::cout << "Drawing known card" << std::endl;

            glm::vec3 glPos = convertCords(card);

            std::cout << "Trying to spawn on color: "<< card.color << " on X:" << glPos.x
                      << ", Y:" << glPos.y << "\n";

            foundModel->second->transform.setPosition(glPos);
//            Scene::getSingleton().AddGameObject(foundModel->second);
        }

        if(GetKeyState(VK_RETURN) & 0x8000){

        }

        // Set position of existing object to card position
        //spawnedObjects.find(card.color)->second->transform.setPosition({card.x, card.y, 0});
        //TODO project to 3d map
    }

    for (auto spawnedObject = spawnedObjects.begin();spawnedObject != spawnedObjects.end(); ++spawnedObject) {
        if(!HasCard(spawnedObject->first))
        {
            std::cout << "Card no longer found destoying: "<< spawnedObject->first
            <<"\n size of array: " << spawnedObjects.size() << std::endl;
            Scene::getSingleton().RemoveGameObject(spawnedObject->second);
            spawnedObjects.erase(spawnedObject);
            std::cout << "Size after deletion: "<< spawnedObjects.size() << std::endl;
        }
    }

}

void Spawner::Awake()
{
    Component::Awake();
    spawnedObjects = std::map<unsigned int, GameObject*>();
}

glm::vec3 Spawner::convertCords(CardDetector::Card card)
{
    glm::vec3 cvPos = {card.y, 1.0f, card.x};
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float) 1440 /
                                                                 (float) 1080, 0.1f, 200.0f);
    glm::vec4 viewport(0.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 glPos = glm::unProject(cvPos, model, projection, viewport);

    glPos = {glPos.x*1.0f, glPos.y*1.0f, glPos.z*1.0f};

    return glPos;
}
