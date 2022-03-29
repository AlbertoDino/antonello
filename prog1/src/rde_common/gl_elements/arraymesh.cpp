#include <rdecommon.h>
#include "vertexindexbuffer.h"
#include "vertex.h"
#include "shader.h"
#include "renderingelement.h"
#include "gltypes.h"
#include "drawobjects.h"
#include "arraymesh.h"


namespace oglElements {

	ArrayMesh::ArrayMesh()
	{

	}

	ArrayMesh::~ArrayMesh()
	{
	}

	void ArrayMesh::vertex3f(const float32 x, const float32 y, const float32 z)
	{
		Vertex v;
		v.Pos = { x, y, z };
		v.Normal = { 1, 1, 1 };
		Vertices.push_back(v);
	}

	void ArrayMesh::create(DrawArrayObject* pElement)
	{
		vertexBuffer.create_buffers(&pElement->vertexObject, GL_LINES, Vertices);
	}


}
