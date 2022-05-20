#pragma once

namespace oglElements {

	class TriangleMesh {
	public:
		TriangleMesh();

		void addVertex(const glm::vec3& v, const glm::vec3& n, const glm::vec2& t);
		void addIndex(GLuint i1, GLuint i2, GLuint i3);

		//Requires Vertices
		void computeTangents();
		void create(gl_vertexObject* vertexObject, GLenum drawmode = GL_TRIANGLES);

		std::vector<Vertex> vertices;
		std::vector<GLuint> indexes;
		int32 indexCount;
		VertexIndexBuffer vertexBuffer;
	};

}
