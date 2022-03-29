#pragma once
#include "gltypes.h"
#include "vertex.h"

namespace oglElements {

	class VertexIndexBuffer
	{
    public:
        VertexIndexBuffer() = default;

        void create_buffers(gl_vertexObject* pVertexObject, GLenum drawmode,const std::vector<Vertex>& vertices);
        void create_buffers(gl_vertexObject* pVertexObject, GLenum drawmode, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

        void delete_buffers(gl_vertexObject* pVertexObject);

    protected:
        gl_vertexObject *pVertexObject;
	};

}

