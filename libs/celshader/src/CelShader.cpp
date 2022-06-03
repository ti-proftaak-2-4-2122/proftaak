// Copyright (c) 2012, ME Chamberlain
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
// 	- Redistributions of source code must retain the above copyright notice, this
// 	  list of conditions and the following disclaimer.
// 	- Redistributions in binary form must reproduce the above copyright notice,
// 	  this list of conditions and the following disclaimer in the documentation 
// 	  and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
// WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include "CelShader.h"

namespace cs {
    namespace internal {

        CelShader::CelShader() {
            this->loadShader();
        }

        void CelShader::loadShader() {
            GLuint vertexShader;
            GLuint fragmentShader;
            GLint vertCompiled;
            GLint fragCompiled;
            GLint linked;
            GLchar* vertexShaderSource;
            GLchar* fragmentShaderSource;

            // Create shader objects
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

            // Associate the shaders with their source files
            glShaderSource(vertexShader, 1, const_cast<const GLchar**>(&vertexShaderSource), nullptr);
            glShaderSource(fragmentShader, 1, const_cast<const GLchar**>(&fragmentShaderSource), nullptr);

            //Compile the vertex shader
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertCompiled);

            //Compile the fragment shader
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragCompiled);

            if ((!vertCompiled) || (!fragCompiled)) {
                std::cout << "compile error " << vertCompiled << " " << fragCompiled << std::endl;
                return;
            }

            // Create a program object to attach the shaders too
            this->celShaderProgram = glCreateProgram();
            glAttachShader(this->celShaderProgram, vertexShader);
            glAttachShader(this->celShaderProgram, fragmentShader);

            // Link the program
            glLinkProgram(this->celShaderProgram);
            glGetProgramiv(this->celShaderProgram, GL_LINK_STATUS, &linked);

            if (!linked) {
                std::cout << "Linking vertex and fragment shader failed" << std::endl;
                return;
            }

            glUseProgram(this->celShaderProgram);
        }

    }

    std::unique_ptr<internal::CelShader> shader;

    void init()
    {
        shader.reset(new internal::CelShader());

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
    }

    std::vector<Vertex> vertices;
    GLenum shape = 0;

    void begin(GLenum shape)
    {
        assert(cs::shape == 0);
        cs::shape = shape;
        cs::vertices.clear();
    }
    void addVertex(const Vertex& vertex)
    {
        vertices.push_back(vertex);
    }
    void end()
    {
        assert(shape != 0);
        cs::drawVertices(shape, vertices);
        shape = 0;
    }

    void drawVertices(GLenum shape, const std::vector<Vertex>& vertices)
    {
        if (!vertices.empty())
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), &vertices[0].position);
            glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), &vertices[0].color);
            glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), &vertices[0].texcoord);
            glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), &vertices[0].normal);
            glDrawArrays(shape, 0, (GLsizei)vertices.size());
        }
    }
}

// Copyright (c) 2012, ME Chamberlain
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
// 	- Redistributions of source code must retain the above copyright notice, this
// 	  list of conditions and the following disclaimer.
// 	- Redistributions in binary form must reproduce the above copyright notice,
// 	  this list of conditions and the following disclaimer in the documentation 
// 	  and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
// WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
