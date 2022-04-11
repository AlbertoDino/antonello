#include <rdecommon.h>
#include "vertex.h"
#include "gltypes.h"
#include "vertexindexbuffer.h"


namespace oglElements
{

    void VertexIndexBuffer::create_buffers(gl_vertexObject* pVertexObject, GLenum drawmode, const std::vector<Vertex>& vertices)
    {
        pVertexObject->count = vertices.size();
        pVertexObject->drawMode = drawmode;
        glGenVertexArrays(1, &pVertexObject->VAO);

        glGenBuffers(1, &pVertexObject->VBO);

        glBindVertexArray(pVertexObject->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, pVertexObject->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

        glBindVertexArray(0);
    }

    void VertexIndexBuffer::create_buffers(gl_vertexObject* pVertexObject, GLenum drawmode, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
        pVertexObject->drawMode = drawmode;
        pVertexObject->count = indices.size();
        glGenVertexArrays(1, &pVertexObject->VAO);

        glGenBuffers(1, &pVertexObject->IBO);
        glGenBuffers(1, &pVertexObject->VBO);

        glBindVertexArray(pVertexObject->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, pVertexObject->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pVertexObject->IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

        glBindVertexArray(0);
	}

    void VertexIndexBuffer::delete_buffers(gl_vertexObject* pVertexObject)
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &pVertexObject->IBO);
        glDeleteBuffers(1, &pVertexObject->VBO);
        glDeleteVertexArrays(1, &pVertexObject->VAO);
    }

}