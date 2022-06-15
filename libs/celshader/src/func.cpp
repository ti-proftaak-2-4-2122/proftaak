//
// Created by twanh on 9-6-2022.
//

#include "cs/CelShader.h"

#include "tigl.h"

#include "cs/func.h"

using tigl::Vertex;
using tigl::VBO;

namespace cs
{

    std::vector<Vertex> vertices;
    GLenum shape = 0;

    void init()
    {
        shader.reset(new internal::CelShader());

        glEnableVertexAttribArray(0); // Position
        glEnableVertexAttribArray(1); // Color
        glEnableVertexAttribArray(2); // TexCoord (unused)
        glEnableVertexAttribArray(3); // Normal
    }

    void begin(GLenum shape)
    {
        assert(cs::shape == 0);
        cs::shape = shape;
        cs::vertices.clear();
    }

    void addVertex(const Vertex& vertex)
    {
        cs::vertices.push_back(vertex);
    }
    void end()
    {
        assert(cs::shape != 0);
        cs::drawVertices(cs::shape, cs::vertices);
        cs::shape = 0;
    }

    void drawVertices(GLenum shape, const std::vector<Vertex>& vertices)
    {
        if (vertices.size() > 0)
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), &vertices[0].position);
            glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), &vertices[0].color);
            glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), &vertices[0].texcoord);
            glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), &vertices[0].normal);
            glDrawArrays(shape, 0, (GLsizei)vertices.size());
        }
    }

    VBO* createVbo(const std::vector<Vertex>& vertices)
    {
        VBO* vbo = new VBO();
        glGenBuffers(1, &vbo->id);
        glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        vbo->size = (unsigned int)vertices.size();
        return vbo;
    }

    void drawVertices(GLenum shape, VBO* vbo)
    {
        static Vertex tmpVertex;
        if (vbo->size > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo->id);

            glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex),	(void*) ((char*)&tmpVertex.position - (char*)&tmpVertex));
            glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex),		(void*) ((char*)&tmpVertex.color - (char*)&tmpVertex));
            glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex),	(void*) ((char*)&tmpVertex.texcoord - (char*)&tmpVertex));
            glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex),	(void*) ((char*)&tmpVertex.normal - (char*)&tmpVertex));
            glDrawArrays(shape, 0, (GLsizei)vbo->size);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}