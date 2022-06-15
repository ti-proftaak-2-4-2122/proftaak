//
// Created by Ewout on 1-6-2022.
//

#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint textureLoader::getTexture(const std::string &texturePath)
{
    auto texture = textureCache.find(texturePath);

    if (texture != textureCache.end()) return texture->second;

    auto textureGluint = loadTexture(texturePath);

    textureCache.insert({texturePath, textureGluint});

    return textureGluint;
}

GLuint textureLoader::loadTexture(const std::string &texturePath)
{
    int width, height, bpp;
    auto *imgData = stbi_load(texturePath.c_str(), &width, &height, &bpp, 4);

    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    stbi_image_free(imgData);

    return textureId;
}


