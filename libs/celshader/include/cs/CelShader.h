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

#pragma once

#include <string>
#include <vector>

#include "tigl.h"

#include "func.h"

using tigl::Vertex;

/**
 * @brief namespace for the cel-shader/toon-shader
 */
namespace cs {

    /**
     * @brief private namespace for cel-shader/toon-shader
     */
    namespace internal {
        class CelShader {
        private:
            GLuint celShaderProgram = 0;

            enum Uniform
            {
                //matrices
                projectionMatrix,
                viewMatrix,
                modelMatrix,
                normalMatrix,

                // params
                lightPosition,
                useColor,
                useColorMult,
                colorMult,
                useAlphaTest,

                UniformMax
            };

            int uniforms[UniformMax];

        public:
            CelShader();

            void use();

            void setProjectionMatrix(const glm::mat4& matrix);
            void setViewMatrix(const glm::mat4& matrix);
            void setModelMatrix(const glm::mat4& matrix);

            void setLightPosition(const glm::vec3& pos);

            void enableColor(bool enable);
            void enableColorMult(bool enable);
            void setColorMult(const glm::vec4& color);

            void enableAlphaTest(bool enable);

        private:
            void loadShader();
            void initShaderVars();

            void setUniform(Uniform uniform, const glm::mat4& value);
            void setUniform(Uniform uniform, const glm::vec4& value);
            void setUniform(Uniform uniform, const glm::vec3& value);
            void setUniform(Uniform uniform, bool value);

            void printShaderCompileError(GLuint shaderId);
            void printProgramCompileError();

        };
    }

    extern std::unique_ptr<internal::CelShader> shader;

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
