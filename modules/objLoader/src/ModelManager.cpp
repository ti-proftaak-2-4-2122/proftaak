//
// Created by Ewout on 17-5-2022.
//

#include "ModelManager.h"

ObjModel *ModelManager::getModel(const std::string &fileName)
{
    auto foundModel = modelCache.find(fileName);

    if (foundModel != modelCache.end()) return foundModel->second;

    auto model = new ObjModel(fileName);
    modelCache.insert({fileName, model});

    return model;

}

std::map<std::string, ObjModel *> ModelManager::modelCache = std::map<std::string, ObjModel *>();