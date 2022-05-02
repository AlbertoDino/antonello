#include <rdecommon.h>
#include "vertexindexbuffer.h"
#include "vertex.h"
#include "shader.h"
#include "renderingelement.h"
#include "gltypes.h"
#include "drawobjects.h"
#include "..\math\vector.h"
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

	void ArrayMesh::vertex(const func::CVector3f& v, const func::CVector3f& n,const func::CVector2f& t)
	{
		Vertex vv;
		vv.Pos = { v[0], v[1], v[2] };
		vv.Normal = { n[0], n[1], n[2]};
		vv.UV = { t[0], t[1] };
		Vertices.push_back(vv);
	}

	void ArrayMesh::create(gl_vertexObject* pElement, GLenum drawmode)
	{
		vertexBuffer.create_buffers(pElement, drawmode, Vertices);
	}


}
