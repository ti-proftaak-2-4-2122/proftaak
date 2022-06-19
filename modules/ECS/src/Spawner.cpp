//
// Created by tjtle on 01/06/2022.
//

#include "Spawner.h"
#include "glm/gtc/type_ptr.hpp"
#include "AIPrefab.h"
#include "InputHandler.h"
#include "TeamHelper.h"
#include "../../../user-config.h"
#include "../../../colours.h"

bool Spawner::HasCard(unsigned int color)
{
    for (auto& card : receivedCards){
        if (card.color == color)
            return true;
    }
    return false;
}

void Spawner::UpdateAfterDraw()
{
    this->greenPoolIndex = 0;
    this->redPoolIndex = 0;
    this->yellowPoolIndex = 0;

    receivedCards = detector->GetDetectedCards();
    for(auto& card : receivedCards)
    {
        GameObject* spawnPreviewObj = this->getPreviewGameObjectForCard(card);
        glm::vec3 glPos = ConvertCords(card);
        spawnPreviewObj->transform.setPosition(glPos);
    }
}

void Spawner::Spawn()
{
    for(auto& currentCard : receivedCards)
    {
        CurrencyManager& currencyManager = Scene::getSingleton().getCurrencyManager();
        float requiredMoney = 0.0f;

        //std::cout << "YO IMMA SPAWN EM";
        glm::vec3 glPos = ConvertCords(currentCard);
        std::cout << "Pos: " << glPos.x << "," << glPos.y << "," << glPos.z << ".\n";
        UnitTypeEnum type;
        //std::cout << "color = " << card.color << std::endl;
        if(currentCard.color == 0) {
            type = FAST;
            //std::cout << "type = fast\n";
            requiredMoney = 2.0f;
        }
        if(currentCard.color == 1) {
            type = SLOW;
            //std::cout << "type = slow\n";
            requiredMoney = 4.0f;
        }
        if(currentCard.color == 2) {
            type = LAND;
            //std::cout << "type = land\n";
            requiredMoney = 3.0f;
        }
        //std::cout << ToString(type) << std::endl;
        short currentTeam = TeamHelper::getTeamByPosition(glPos);
        if(currencyManager.requirePlayerCurrency(currentTeam, requiredMoney))
        {
            currencyManager.updatePlayerCurrency(currentTeam, -requiredMoney);

            glm::mat4 model = CONFIG_MATRIX_VIEW;
            glm::mat4 projection = CONFIG_MATRIX_PROJECTION;
            glm::ivec4 viewport;
            glGetIntegerv(GL_VIEWPORT, glm::value_ptr(viewport));
            glm::vec3 Projected = glm::project(glPos, model, projection,viewport);
            auto *AIcharacter = new AIPrefab(new Transform(glPos), type);
            Scene::getSingleton().AddGameObject(AIcharacter);
        }
        else
        {
            std::cout << "Currency " << currencyManager.getPlayerCurrency(currentTeam) << " is to low for spawning" << std::endl;
        }
    }
}

void Spawner::Awake()
{
    Component::Awake();

    std::function<void()> functionPointer = [this](){
        this->Spawn();
    };


    InputHandler::getSingleton().AddCallback(GLFW_KEY_SPACE, GLFW_PRESS, functionPointer);

}

void Spawner::Update()
{
    Component::Update();

    this->updatePreviewList(this->greenPreviewPool, greenPoolIndex);
    this->updatePreviewList(this->redPreviewPool, redPoolIndex);
    this->updatePreviewList(this->yellowPreviewPool, yellowPoolIndex);
}

void Spawner::Draw()
{
    Component::Draw();

    this->drawPreviewList(this->greenPreviewPool, greenPoolIndex);
    this->drawPreviewList(this->redPreviewPool, redPoolIndex);
    this->drawPreviewList(this->yellowPreviewPool, yellowPoolIndex);
}

glm::vec3 Spawner::ConvertCords(CardDetector::Card& card)
{
    glm::mat4 model = CONFIG_MATRIX_VIEW;
    glm::mat4 projection = CONFIG_MATRIX_PROJECTION;
    glm::ivec4 viewport;
    glGetIntegerv(GL_VIEWPORT, glm::value_ptr(viewport));
    glm::vec3 cvPos = {card.x * viewport[2], viewport[3] - card.y * viewport[3], 0.991f};

    glReadPixels(cvPos.x, cvPos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &cvPos.z);

    glm::vec3 glPos = glm::unProject(cvPos, model, projection, viewport);

    glPos = {glPos.x*1.0f, 0.0f, glPos.z*1.0f};

    return glPos;
}

GameObject* Spawner::getPreviewGameObjectForCard(const CardDetector::Card& card)
{
    GameObject* result = nullptr;

    switch(card.color) {
        case 0 /* green */:
            if(this->greenPoolIndex == this->greenPreviewPool.size()) {
                // Create new
                auto* charGameObject = new GameObject();
                auto* mesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));

                mesh->SetColor(GREEN_ANDROID);
                mesh->SetAlpha(0.7f);

                charGameObject->AddComponent(mesh);

                this->greenPreviewPool.push_back(charGameObject);
            }

            // Get the last item out of pool
            result = this->greenPreviewPool[this->greenPoolIndex++];
            break;
        case 1 /* red */:
            if(this->redPoolIndex == this->redPreviewPool.size()) {
                // Create new
                auto* charGameObject = new GameObject();
                auto* mesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));

                mesh->SetColor(RED_BERRY);
                mesh->SetAlpha(0.7f);

                charGameObject->AddComponent(mesh);

                this->redPreviewPool.push_back(charGameObject);
            }

            // Get the last item out of pool
            result = this->redPreviewPool[this->redPoolIndex++];
            break;
        case 2 /* yellow */:
            if(this->yellowPoolIndex == this->yellowPreviewPool.size()) {
                // Create new
                auto* charGameObject = new GameObject();
                auto* mesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));

                mesh->SetColor(YELLOW_SUNFLOWER);
                mesh->SetAlpha(0.7f);

                charGameObject->AddComponent(mesh);

                this->yellowPreviewPool.push_back(charGameObject);
            }

            // Get the last item out of pool
            result = this->yellowPreviewPool[this->yellowPoolIndex++];
            break;
    }

    return result;
}

void Spawner::drawPreviewList(const std::vector<GameObject*>& previewPool, const int& usedCount)
{
    for(int i = 0; i < usedCount && i < previewPool.size(); i++)
        previewPool[i]->Draw();
}

void Spawner::updatePreviewList(const std::vector<GameObject*>& previewPool, const int& usedCount)
{
    for(int i = 0; i < usedCount && i < previewPool.size(); i++)
        previewPool[i]->Update();
}
