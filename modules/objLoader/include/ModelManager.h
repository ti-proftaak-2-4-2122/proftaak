/**
 * @file
 * @brief Header file for the ModelManager class
 * @author Ewout
 * @date 17-05-2022
 */

#pragma once

#include <map>
#include <string>
#include "ObjModel.h"

class ModelManager
{

private:
    static std::map<std::string, ObjModel *> modelCache;

public:
    static ObjModel *getModel(const std::string &fileName);

};


