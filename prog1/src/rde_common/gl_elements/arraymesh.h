#pragma once

namespace oglElements {


	class ArrayMesh {
	public:
		ArrayMesh();
		~ArrayMesh();

		void vertex3f(const float32 x, const float32 y, const float32 z);

		void vertex(const func::CVector3f& v, const func::CVector3f& n,const func::CVector2f& t);

		void create(DrawArrayObject* pElement, GLenum drawmode = GL_LINES);

	private:
		VertexIndexBuffer vertexBuffer;
		std::vector<Vertex> Vertices;

	};

}