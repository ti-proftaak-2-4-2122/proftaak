//
// Created by Ewout on 1-6-2022.
//

#ifndef PROFTAAK24_TEXTURELOADER_H
#define PROFTAAK24_TEXTURELOADER_H


#include <string>
#include <map>
#include "glad/glad.h"

class textureLoader
{
private:
    inline static std::map<std::string, GLuint> textureCache;
    static GLuint loadTexture(const std::string& texturePath);

public:
    static GLuint getTexture(const std::string& texturePath);
};


#endif //PROFTAAK24_TEXTURELOADER_H
