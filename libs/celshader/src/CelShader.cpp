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

#include <cmath>
#include <iostream>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include "celShaderFrag.h"
#include "celShaderVS.h"

#include "CelShader.h"

namespace cs {
    namespace internal {

        CelShader::CelShader() {
            this->loadShader();
        }

        void CelShader::use() {
            glUseProgram(this->celShaderProgram);
        }

        void CelShader::loadShader() {
            GLuint vertexShaderId;
            GLuint fragmentShaderId;
            GLint vertCompiled;
            GLint fragCompiled;
            GLint linkedProgram;

            // Create shader objects
            vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
            fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

            // Associate the shaders with their source files
            glShaderSource(vertexShaderId, 1, &CEL_SHADER_VERTEX_SRC, nullptr);
            glShaderSource(fragmentShaderId, 1, &CEL_SHADER_FRAG_SRC, nullptr);

            //Compile the vertex shader
            glCompileShader(vertexShaderId);
            glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &vertCompiled);

            if(vertexShaderId == GL_FALSE) {
                this->printShaderCompileError(vertexShaderId);
                return;
            }

            //Compile the fragment shader
            glCompileShader(fragmentShaderId);
            glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &fragCompiled);

            if(fragmentShaderId == GL_FALSE) {
                this->printShaderCompileError(fragmentShaderId);
                return;
            }

            // Create a program object to attach the shaders too
            this->celShaderProgram = glCreateProgram();
            glAttachShader(this->celShaderProgram, vertexShaderId);
            glAttachShader(this->celShaderProgram, fragmentShaderId);

            // Link the program
            glLinkProgram(this->celShaderProgram);
            glGetProgramiv(this->celShaderProgram, GL_LINK_STATUS, &linkedProgram);

            if (linkedProgram == GL_FALSE) {
                printProgramCompileError();
                return;
            }

            use();
        }

        void CelShader::printShaderCompileError(const GLuint shaderId) {
            int length, charsWritten;

            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

            char* infolog = new char[length + 1];
            memset(infolog, 0, length + 1);

            glGetShaderInfoLog(shaderId, length, &charsWritten, infolog);
            std::cout << "Error compiling shader "  << shaderId << ":\n" << infolog << std::endl;

            delete[] infolog;
        }

        void CelShader::printProgramCompileError() {
            int length, charsWritten;

            glGetProgramiv(this->celShaderProgram, GL_INFO_LOG_LENGTH, &length);

            char* infolog = new char[length + 1];
            memset(infolog, 0, length + 1);

            glGetProgramInfoLog(this->celShaderProgram, length, &charsWritten, infolog);
            std::cout << "Error compiling cel-shader program:\n" << infolog << std::endl;

            delete[] infolog;
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
