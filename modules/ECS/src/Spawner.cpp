//
// Created by tjtle on 01/06/2022.
//

#include "Spawner.h"
#include "Mesh.h"
#include "ModelManager.h"


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
            //add new card to spawnedcards
            auto *charGameObject = new GameObject();
            charGameObject->AddComponent(new Mesh(ModelManager::getModel("../resource/models/tower.obj")));

            charGameObject->transform.setPosition({card.x / 100.0f, 0.0f, card.y / 100.0f});

            Scene::getSingleton().AddGameObject(charGameObject);
            std::cout << "Trying to spawn on color: "<< card.color << " on X:" << card.x / 100.0f
            << ", Y:" << card.y /100.0f << "\n";
//            spawnedObjects.insert(std::pair<unsigned int, GameObject>(card.color,
//             *charGameObject));

            spawnedObjects.insert({card.color,charGameObject});

            continue;
        }

        auto foundModel = spawnedObjects.find(card.color);
        if (foundModel != spawnedObjects.end())
        {
            foundModel->second->transform.setPosition({card.x / 100.0f, 0.0f, card.y / 100.0f});
//            Scene::getSingleton().AddGameObject(foundModel->second);
        }

        // Set position of existing object to card position
        //spawnedObjects.find(card.color)->second->transform.setPosition({card.x, card.y, 0});
        //TODO project to 3d map
    }

    for (auto spawnedObject = spawnedObjects.begin();spawnedObject != spawnedObjects.end(); ++spawnedObject) {
        if(!HasCard(spawnedObject->first))
        {
            Scene::getSingleton().RemoveGameObject(spawnedObject->second);
            spawnedObjects.erase(spawnedObject);

        }
    }

}

void Spawner::Awake()
{
    Component::Awake();
    spawnedObjects = std::map<unsigned int, GameObject*>();
}
