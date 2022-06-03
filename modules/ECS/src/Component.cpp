//
// Created by Ewout on 17-5-2022.
//
#include "Component.h"

GameObject &Component::getGameObject()
{
    return gameObject;
}

Component::Component(GameObject& _gameObject) : gameObject(_gameObject)
{

}
