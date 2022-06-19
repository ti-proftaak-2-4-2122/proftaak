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

/**
 * @brief GameObject for showing the necessary behaviour within the scene
 * Based on ECS needs @components to enact it's behaviour.
 * Also has a list of children (for e.g. a plane where other GO's need to be attached to).
 * Every GameObject wants to be able to move, or be placed so for that a GO always needs a @transform
 */
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

    /**
     * @brief Adds component to @components
     * @param component is the component that needs to be added
     * @return Reference to the component that was added.
     */
    Component &AddComponent(Component *component);

    /**
     * @brief Template to find components within this Game Object
     * @tparam T is the generic and gets cast to the necessary Component for e.g. T can be a Mesh,
     * because a Mesh is considered a component
     * @return The derived a.k.a. the component that needs to be used,
     * if the component you're searching for does not exist then return a nullptr.
     */
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

    [[nodiscard]] const std::vector<Component *> &getComponents() const;

    /**
     * @brief Adds a Component to it's list of @components
     * @tparam T Generic to find the necessary component that wants to be added.
     * @return Reference to component
     */
    template<class T>
    T& AddComponent()
    {
        auto component = new T();
        this->AddComponent(component);
        return *component;
    }

    void AddChild(GameObject* child);
    void RemoveChild(GameObject*& child);


    /**
     * @brief Awakes Game Object to initialize behaviour
     */
    virtual void Awake();

    /**
     * @brief Updates any necessary data that the behaviour needs.
     */
    virtual void Update();

    /**
     * @brief Calls Component->Draw() to draw the mesh associated with the Game Object
     */
    void Draw();

    /**
     * @brief Updates values after they have been drawn,
     * for e.g. changing the mesh of an object or characterStats to attack faster.
     */
    void UpdateAfterDraw();

    virtual ~GameObject();

    /**
     * @brief If the @Collider detects that someone collided with this Game Object this function gets called,
     * based on the Game Object a certain behaviour gets activated when it collides.
     * @param other is the other collider that this Game Object collides with
     */
    virtual void onTriggerEnter(Collider* other) {
//        std::cout << "On Trigger Enter called" << std::endl;
    };

    /**
     * @brief If the @Collider no longer detects collision then it calls this function.
     * So it Exits the behaviour to continue it's primary behaviour.
     * @param other
     */
    virtual void onTriggerExit(Collider* other) {
//        std::cout << "On Trigger Exit called" << std::endl;
    };

    [[nodiscard]] TagEnum getTagEnum() const;

    void setTagEnum(TagEnum newTagEnum);
};

