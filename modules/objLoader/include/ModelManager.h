//
// Created by Ewout on 17-5-2022.
//

#pragma once
#include <map>
#include <string>
#include "ObjModel.h"

class ModelManager
{

private:
    static std::map<std::string, ObjModel*>  modelCache;

public:
    static ObjModel* getModel(const std::string &fileName);

};


