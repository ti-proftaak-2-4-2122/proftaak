/**
 * @file
 * @brief Header file for the GameObject class
 * @author Daan van Donk
 * @date 11-05-2022
 */

#pragma once

#include "vector"
#include "TagEnum.h"
#include <typeinfo>
#include <iostream>

class Component;
class Transform;
class Collider;

class GameObject
{
private:
    std::vector<Component *> components;
    std::vector<GameObject*> children;

protected:
    TagEnum tagEnum = TagEnum::NONE;

public:
    Transform &transform;
    GameObject();
    explicit GameObject(Transform* transform);

    Component &AddComponent(Component *component);

    template<class T>
    T *FindComponent()
    {
        for (auto component : this->components)
        {
            auto derived = dynamic_cast<T *>(component);

            if (derived)
                return derived;

        }

        return nullptr;
    }

    const std::vector<Component *> &getComponents() const;

    template<class T>
    T& AddComponent()
    {
        auto component = new T();
        this->AddComponent(component);
        return *component;
    }

    void AddChild(GameObject* child);
    void RemoveChild(GameObject*& child);

    virtual void Awake();

    virtual void Update();

    void Draw();

    void UpdateAfterDraw();

    ~GameObject();

    virtual void onTriggerEnter(Collider* other) {
//        std::cout << "On Trigger Enter called" << std::endl;
    };

    virtual void onTriggerExit(Collider* other) {
//        std::cout << "On Trigger Exit called" << std::endl;
    };

    TagEnum getTagEnum() const;

    void setTagEnum(TagEnum newTagEnum);

};

